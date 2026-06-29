/**
 * @file VT13.c
 * @brief RoboMaster 裁判系统相机图传模块 VT13 协议解析源文件
 * @version 1.0
 * @date 2026-03-21
 * @author CaoKangqi
 */

#include "VT13.h"
#include "RUI_MATH.h"

static uint16_t get_crc16_check_sum(uint8_t *p_msg, uint16_t len, uint16_t crc16);
static bool verify_crc16_check_sum(uint8_t *p_msg, uint16_t len);
static float VT_OneFilter(float last, float now, float thresholdValue);
static float VT_deadband(float Value, float minValue, float maxValue);
static uint8_t VT_UpdateKeyStatus(uint8_t is_pressed, uint8_t *press_time);
static void VT_HandleKeyToggle(uint8_t is_pressed, uint8_t *lock_flag, uint8_t *toggle_number);

/**
 * @brief VT13 协议解析函数
 */
void VT13_Resolved(uint8_t* Data, VT13_Typedef* VT13)
{
    VT13_FrameTypeDef* frame = (VT13_FrameTypeDef*)Data;
    // 校验帧头 0xA9, 0x53 及整个数据帧的 CRC16
    if (frame->header1 == 0XA9 && frame->header2 == 0X53 && verify_crc16_check_sum(Data, 21))
    {
        VT13->CRC_flag = true;

        VT13->Remote.Channel[0] = (int16_t)frame->channel0 - 1024;
        VT13->Remote.Channel[1] = (int16_t)frame->channel1 - 1024;
        VT13->Remote.Channel[2] = (int16_t)frame->channel2 - 1024;
        VT13->Remote.Channel[3] = (int16_t)frame->channel3 - 1024;
        VT13->Remote.wheel      = (int16_t)frame->wheel - 1024;

        VT13->Remote.mode_sw    = frame->mode_sw;
        VT13->Remote.pause      = frame->pause;
        VT13->Remote.fn_1       = frame->fn_1;
        VT13->Remote.fn_2       = frame->fn_2;
        VT13->Remote.trigger    = frame->trigger;

        VT13->Mouse.X_Flt = VT_deadband(VT_OneFilter(VT13->Mouse.X_Flt, (float)frame->mouse_x, 500), -3.0e-3f, 3.0e-3f);
        VT13->Mouse.Y_Flt = VT_deadband(VT_OneFilter(VT13->Mouse.Y_Flt, (float)frame->mouse_y, 500), -3.0e-3f, 3.0e-3f);
        VT13->Mouse.Z_Flt = VT_deadband(VT_OneFilter(VT13->Mouse.Z_Flt, (float)frame->mouse_z, 500), -3.0e-3f, 3.0e-3f);

        VT13->Mouse.L_State = VT_UpdateKeyStatus(frame->mouse_l & 0x01, (uint8_t*)&VT13->Mouse.L_PressTime);
        VT13->Mouse.R_State = VT_UpdateKeyStatus(frame->mouse_r & 0x01, (uint8_t*)&VT13->Mouse.R_PressTime);
        VT13->Mouse.M_State = VT_UpdateKeyStatus(frame->mouse_m & 0x01, (uint8_t*)&VT13->Mouse.M_PressTime);

        VT13->KeyBoard.W = VT_UpdateKeyStatus(frame->key_w, &VT13->KeyBoard.W_PressTime);
        VT13->KeyBoard.S = VT_UpdateKeyStatus(frame->key_s, &VT13->KeyBoard.S_PressTime);
        VT13->KeyBoard.A = VT_UpdateKeyStatus(frame->key_a, &VT13->KeyBoard.A_PressTime);
        VT13->KeyBoard.D = VT_UpdateKeyStatus(frame->key_d, &VT13->KeyBoard.D_PressTime);

        VT13->KeyBoard.Shift = frame->key_shift;
        VT13->KeyBoard.Ctrl  = frame->key_ctrl;
        VT13->KeyBoard.Q     = frame->key_q;
        VT13->KeyBoard.E     = frame->key_e;
        VT13->KeyBoard.R     = frame->key_r;
        VT13->KeyBoard.F     = frame->key_f;
        VT13->KeyBoard.G     = frame->key_g;
        VT13->KeyBoard.Z     = frame->key_z;
        VT13->KeyBoard.X     = frame->key_x;
        VT13->KeyBoard.C     = frame->key_c;
        VT13->KeyBoard.V     = frame->key_v;
        VT13->KeyBoard.B     = frame->key_b;

        // 键盘锁存
        static uint8_t KeyLocks[12] = {0};
        VT_HandleKeyToggle(VT13->KeyBoard.Shift, &KeyLocks[0],  &VT13->KeyBoard.Shift_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.Ctrl,  &KeyLocks[1],  &VT13->KeyBoard.Ctrl_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.Q,     &KeyLocks[2],  &VT13->KeyBoard.Q_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.E,     &KeyLocks[3],  &VT13->KeyBoard.E_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.R,     &KeyLocks[4],  &VT13->KeyBoard.R_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.F,     &KeyLocks[5],  &VT13->KeyBoard.F_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.G,     &KeyLocks[6],  &VT13->KeyBoard.G_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.Z,     &KeyLocks[7],  &VT13->KeyBoard.Z_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.X,     &KeyLocks[8],  &VT13->KeyBoard.X_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.C,     &KeyLocks[9],  &VT13->KeyBoard.C_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.V,     &KeyLocks[10], &VT13->KeyBoard.V_PreeNumber);
        VT_HandleKeyToggle(VT13->KeyBoard.B,     &KeyLocks[11], &VT13->KeyBoard.B_PreeNumber);
        if (memcmp(&frame->mouse_x, (const uint8_t[9]){0}, 9) != 0) {
            VT13->Ctrl_Mode = 1;  // 键鼠有动作 -> 键鼠模式
        } else {
            VT13->Ctrl_Mode = 0;  // 键鼠全为0 -> 遥控模式
        }
    }
    else
    {
        VT13->CRC_flag = false;
    }
}

/**
 * @brief 更新按键按压时间，并判断当前复合状态（释放/点按/长按）
 * @param is_pressed 当前物理是否按下
 * @param press_time 持续按下时间计数缓存
 * @return 复合状态编码 (KEY_UP, KEY_CLICK, KEY_PRESS)
 */
static uint8_t VT_UpdateKeyStatus(uint8_t is_pressed, uint8_t *press_time)
{
    if (is_pressed)
    {
        if (*press_time < 250) (*press_time)++;
        return (*press_time <= 20) ? VT13_KEY_CLICK : VT13_KEY_PRESS;
    }
    else
    {
        *press_time = 0;
        return VT13_KEY_UP;
    }
}

/**
 * @brief 处理按键切换锁定逻辑（按下瞬时改变一次状态）
 * @param is_pressed 物理按下检测
 * @param lock_flag 触发边沿锁标志位
 * @param toggle_number 状态转换标志寄存器（目标取反状态位）
 */
static void VT_HandleKeyToggle(uint8_t is_pressed, uint8_t *lock_flag, uint8_t *toggle_number)
{
    if (is_pressed && !(*lock_flag))
    {
        *toggle_number = !(*toggle_number);
        *lock_flag = 1;
    }
    else if (!is_pressed)
    {
        *lock_flag = 0;
    }
}

/**
 * @brief 鼠标数据一阶低通滤波
 */
static float VT_OneFilter(float last, float now, float thresholdValue)
{
    const float sensitivlFilter = 0.8f;
    const float numbFilter = 0.2f;
    if (RUI_F_MATH_ABS_float(last - now) >= thresholdValue)
        return (now * sensitivlFilter + last * (1.0f - sensitivlFilter));
    else
        return (now * numbFilter + last * (1.0f - numbFilter));
}

/**
 * @brief 浮点死区滤除
 */
static float VT_deadband(float Value, float minValue, float maxValue)
{
    if (Value < maxValue && Value > minValue) return 0.0f;
    return Value;
}

/**
 * @brief CRC16 查表（多项式 0x1021, CCITT）
 */
static const uint16_t crc16_tab[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

/**
 * @brief 计算 CRC16 校验和
 */
static uint16_t get_crc16_check_sum(uint8_t *p_msg, uint16_t len, uint16_t crc16)
{
    while(len--)
    {
        crc16 = (crc16 >> 8) ^ crc16_tab[(crc16 ^ *p_msg++) & 0x00ff];
    }
    return crc16;
}

/**
 * @brief 验证数据帧 CRC16 完整性与正确性
 */
static bool verify_crc16_check_sum(uint8_t *p_msg, uint16_t len)
{
    if (p_msg == NULL || len <= 2) return false;
    uint16_t w_expected = get_crc16_check_sum(p_msg, len - 2, 0xFFFF);
    return ((w_expected & 0xFF) == p_msg[len - 2] && (w_expected >> 8) == p_msg[len - 1]);
}