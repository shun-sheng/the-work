/*
 * ============================================================
 * MY_Define.h — 项目统一定义中心
 *
 * 本文件是项目的单一信息中心，包含：
 *   1. 所有系统头文件包含
 *   2. X-Macro 数据表（电机注册表、CAN ID表、全局变量表）
 *   3. 所有 #define 常量（按功能分区）
 *   4. 所有 enum / struct / union 类型定义
 *   5. 所有 extern 全局变量声明
 *
 * 其他所有 .h 文件只需 #include "MY_Define.h"，不再重复定义。
 * .c 文件只需包含对应的 .h。
 *
 * 使用方法：
 *   - 普通包含：生成 extern 声明
 *   - 定义全局变量：在包含前 #define GLOBAL_VAR_IMPL
 * ============================================================
 */
#ifndef __MY_DEFINE
#define __MY_DEFINE

/* ============================================================
 * 跨编译器适配
 * ============================================================ */
/* __packed: ARMCC 原生关键字，GCC/clang 需要 attribute */
#ifndef __packed
#if defined(__GNUC__) || defined(__clang__)
#define __packed __attribute__((packed))
#endif
#endif

/* ============================================================
 * 系统头文件包含
 * ============================================================ */
#include "main.h"                  /* → stm32f4xx_hal.h → 所有 HAL 类型 */
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "arm_math.h"
#include "cmsis_os.h"
#include "dsp/matrix_functions.h"
#include "dsp/fast_math_functions.h"

/* ============================================================
 * X-MACRO 数据表
 *
 * 这些表定义了项目中可枚举的数据。
 * 使用时 #define X(...) 展开宏，然后引用表名，最后 #undef X。
 * ============================================================ */

/* ---------- 2.1 CAN ID 表 ----------
 * X(macro_name, can_id_value)
 */
#define CANID_X_TABLE \
    X(CAN_D_1,            0    ) \
    X(CAN_D_2,            1    ) \
    X(CAN_D_CHASSIS_1,    0x201) \
    X(CAN_D_CHASSIS_2,    0x202) \
    X(CAN_D_CHASSIS_3,    0x203) \
    X(CAN_D_CHASSIS_4,    0x204) \
    X(CAN_D_CAP,          0x206) \
    X(CAN_D_TOP,          0x101) \
    X(CAN_D_GIMBAL_YAW,   0x206) \
    X(CAN_D_GIMBAL_PIT,   0x208) \
    X(CAN_D_ATTACK_L,     0x201) \
    X(CAN_D_ATTACK_R,     0x202) \
    X(CAN_D_ATTACK_G,     0x203) \
    X(CHASSIC_kong,       0x232) \
    X(GIMBAL_kong,        0x231)

/* ---------- 2.2 电机注册表 ----------
 * X(name_suffix, motor_type, can_id, bus_id)
 */
#define MOTOR_X_TABLE \
    X(CHASSIS_1, MOTOR_TYPE_3508, CAN_D_CHASSIS_1, CAN_D_1) \
    X(CHASSIS_2, MOTOR_TYPE_3508, CAN_D_CHASSIS_2, CAN_D_1) \
    X(CHASSIS_3, MOTOR_TYPE_3508, CAN_D_CHASSIS_3, CAN_D_1) \
    X(CHASSIS_4, MOTOR_TYPE_3508, CAN_D_CHASSIS_4, CAN_D_1) \
    X(GIMBAL_YAW, MOTOR_TYPE_6020, CAN_D_GIMBAL_YAW, CAN_D_2) \
    X(GIMBAL_PIT, MOTOR_TYPE_6020, CAN_D_GIMBAL_PIT, CAN_D_2) \
    X(SHOOT_L, MOTOR_TYPE_3508, CAN_D_ATTACK_L, CAN_D_2) \
    X(SHOOT_R, MOTOR_TYPE_3508, CAN_D_ATTACK_R, CAN_D_2) \
    X(SHOOT_G, MOTOR_TYPE_2006, CAN_D_ATTACK_G, CAN_D_2)

/* ---------- 2.3 全局变量表 ----------
 * 在 MY_Define.h 中展开 → extern 声明
 * 在 .c 文件中 #define GLOBAL_VAR_IMPL 后展开 → 实际定义
 * 注意：数组类型不在此表，在底部手动声明。
 */
#define GLOBAL_VAR_TABLE \
    X(DBUS_Typedef,             DBUS)             \
    X(VT13_Typedef,             VT13)             \
    X(CONTAL_Typedef,           RUI_V_CONTAL)     \
    X(MOTOR_Typedef,            ALL_MOTOR)        \
    X(IMU_Data_t,               IMU_Data)         \
    X(RUI_ROOT_STATUS_Typedef,  RUI_ROOT_STATUS)  \
    X(CAPDATE_TYPDEF,           CAPDATE)          \
    X(model_t,                  model)            \
    X(DBUS_UNION_TypeDef,       RUI_V_DBUS_UNION) \
    X(VT13_UNION_Typdef,        VT13_UNION)       \
    X(TYPEDEF_VISION,           VISION_V_DATA)    \
    X(TD_t,                     TDDDD)            \
    X(ALL_RX_Data_T,            ALL_RX)           \
    X(User_Data_T,              User_data)        \
    X(float,                    voltage)          \
    X(float,                    vision_state)     \
    X(float,                    heat_state)       \
    X(float,                    huanchongnengliang)\
    X(uint8_t,                  bulltspeed)       \
    X(pid_type_def,             imu_temp)

/* ============================================================
 * #DEFINE 常量
 * ============================================================ */

/* ---------- 状态/错误 ---------- */
#define RUI_DF_READY               1
#define RUI_DF_ERROR               0
#define RUI_DF_NOW                 1
#define RUI_DF_LAST                0
#define ROOT_READY                 1
#define ROOT_ERROR                 0

/* ---------- PID 环数 ---------- */
#define RUI_DF_PID_DOUBLE          1
#define RUI_DF_PID_SINGLE          0

/* ---------- 主控位置 ---------- */
#define RUI_DF_MASTER_LOCATION_JUDGEING  0
#define RUI_DF_MASTER_LOCATION_HEAD      1
#define RUI_DF_MASTER_LOCATION_BOTTOM    2

/* ---------- LED 颜色 ---------- */
#define RUI_DF_LED_RED             0
#define RUI_DF_LED_GREEN           1
#define RUI_DF_LED_BLUE            2
#define RUI_DF_LED_YELLOW          3
#define RUI_DF_LED_PURPLE          4
#define RUI_DF_LED_CYAN            5
#define RUI_DF_LED_WRITE           6

/* ---------- 初始化常量 ---------- */
#define INIT_ANGLE                 6998
#define WIPE_MAX_SPEED             7200
/* ---------- CANSPI ---------- */
#define dSTANDARD_CAN_MSG_ID_2_0B 1
#define dEXTENDED_CAN_MSG_ID_2_0B 2
/* ---------- NIMING(匿名数据) ---------- */
#define df_AnonymityLong 70
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

/* ---------- 离线检测 ---------- */
#define RUI_DF_OFFLINE             0
#define RUI_DF_ONLINE              1
#define DBUS_OFFLINE_TIME          15
#define RUI_DF_MOTOR_OFFLINE_TIME  30
#define RUI_DF_CAP_OFFLINE_TIME    30
#define MONITOR_OFFLINE            false
#define MONITOR_ONLINE             true

/* ---------- PID 参数 ---------- */
#define TEMPERATURE_PID            { 1600.0f, 0.02f, 5.0f }
#define TEMPERATURE_PID_MAX_OUT    4500.0f
#define TEMPERATURE_PID_MAX_IOUT   600.0f
#define CHASSIS_PID_S              { 23.0f, 0.0f, 0.0f }
/* ----------FUZZY PID  ---------- */
#define NB -3
#define NM -2
#define NS -1
#define ZE 0
#define PS 1
#define PM 2
#define PB 3


/* ---------- 电机类型 ID ---------- */
#define MOTOR_TYPE_3508            1
#define MOTOR_TYPE_3510            2
#define MOTOR_TYPE_6020            3
#define MOTOR_TYPE_2006            4

/* ---------- 电机索引 ---------- */
#define MOTOR_D_CHASSIS_1          0
#define MOTOR_D_CHASSIS_2          1
#define MOTOR_D_CHASSIS_3          2
#define MOTOR_D_CHASSIS_4          3
#define MOTOR_D_GIMBAL_YAW         0
#define MOTOR_D_GIMBAL_PIT         1
#define MOTOR_D_ATTACK_L           0
#define MOTOR_D_ATTACK_R           1
#define MOTOR_D_ATTACK_G           2

/* ---------- PID 控制索引 ---------- */
#define PID_D_CHASSIS              0
#define PID_D_GIMBAL               1
#define PID_D_ATTACK               2
#define PID_D_SPEED                0
#define PID_D_ANGLE                1
#define PID_D_CURRENT              2

/* ---------- 运行模式 ---------- */
#define CHASSIS_NORMAL_MODE        0
#define CHASSIS_SPIN_MODE          1
#define DBUS_D_MOD_SINGLE          2
#define DBUS_D_MOD_CONSIST         1
#define DBUS_D_MOD_SHUT            3

/* ---------- 拨杆/开关 ---------- */
#define NOW                        1
#define LAST                       0

/* ---------- 云台限位 ---------- */
#define GIMBAL_PIT_MAX             35
#define GIMBAL_PIT_MIN            -17
#define OMNI_PIT_MAX               5200
#define OMNI_PIT_MIN               4270

/* ---------- 云台 Yaw 限位 ---------- */
#define GIMBAL_YAW_MAX             180.0f       /* 最大偏航角度 */
#define GIMBAL_YAW_MIN            -180.0f       /* 最小偏航角度 */
#define GIMBAL_YAW_TOTAL_MAX       720.0f       /* 累计最大圈数角度（防绕线） */

/* ---------- 底盘参数 ---------- */
#define CHASSIS_SPIN_SPEED_DEFAULT 180.0f
#define CHASSIS_SPIN_DEADBAND      15
#define CHASSIS_SPEED_SCALE_MAX    660.0f
#define radian_angle               57.3f

/* ---------- 达妙电机模式 ID ---------- */
#define MIT_MODE                   0x000
#define POS_MODE                   0x100
#define SPD_MODE                   0x200
#define PSI_MODE                   0x300

/* ---------- 达妙电机限幅 ---------- */
#define P_MIN                     -12.5f
#define P_MAX                      12.5f
#define V_MIN                     -30.0f
#define V_MAX                      30.0f
#define KP_MIN                      0.0f
#define KP_MAX                    500.0f
#define KD_MIN                      0.0f
#define KD_MAX                      5.0f
#define T_MIN                     -10.0f
#define T_MAX                      10.0f

/* ---------- 裁判系统帧长度 ---------- */
#define REFEREE_RXFRAME_LENGTH     256
#define REFEREE_MAX_PACKET_SIZE    136
#define FrameHeader_Length          5U
#define CMDID_Length                2U
#define CRC16_Length                2U

/* ---------- CANSPI ---------- */
#define dSTANDARD_CAN_MSG_ID_2_0B  1
#define dEXTENDED_CAN_MSG_ID_2_0B  2

/* ---------- 数学常量 ---------- */
#ifndef PI
#define PI                         3.14159265354f
#endif
#ifndef RADIAN_COEF
#define RADIAN_COEF                57.295779513f
#endif

/* ---------- 布尔定义 ---------- */
#ifndef TRUE
#define TRUE                       1
#endif
#ifndef FALSE
#define FALSE                      0
#endif

/* ---------- 数值运算宏 ---------- */
#ifndef abs
#define abs(x)                     ((x > 0) ? x : -x)
#endif

#define VAL_LIMIT(val, min, max)   \
    do {                           \
        if ((val) <= (min))        \
            (val) = (min);         \
        else if ((val) >= (max))   \
            (val) = (max);         \
    } while (0)

#define ANGLE_LIMIT_360(val, angle)    \
    do {                               \
        (val) = (angle) - (int)(angle);\
        (val) += (int)(angle) % 360;   \
    } while (0)

#define ANGLE_LIMIT_360_TO_180(val) \
    do {                            \
        if ((val) > 180)            \
            (val) -= 360;           \
    } while (0)

#define VAL_MIN(a, b)              ((a) < (b) ? (a) : (b))
#define VAL_MAX(a, b)              ((a) > (b) ? (a) : (b))
#define LimitMax(input, max)       \
    {                              \
        if (input > max)           \
            input = max;           \
        else if (input < -max)     \
            input = -max;          \
    }
#define rad_format(Ang)            loop_float_constrain((Ang), -PI, PI)

/* ---------- 内存分配宏 ---------- */
#ifndef user_malloc
#ifdef _CMSIS_OS_H
#define user_malloc                pvPortMalloc
#else
#define user_malloc                malloc
#endif
#endif

/* ---------- 编译调试命令 ---------- */
#define OLDHEAD                    1
#define LIFTED_DEBUG               0

/* ---------- CMSIS-DSP 矩阵宏 ---------- */
#define mat                        arm_matrix_instance_f32
#define Matrix_Init                arm_mat_init_f32
#define Matrix_Add                 arm_mat_add_f32
#define Matrix_Subtract            arm_mat_sub_f32
#define Matrix_Multiply            arm_mat_mult_f32
#define Matrix_Transpose           arm_mat_trans_f32
#define Matrix_Inverse             arm_mat_inverse_f32

/* ============================================================
 * 枚举类型
 * ============================================================ */

/* ---------- DBUS 按键状态 ---------- */
typedef enum {
    DBUS_KEY_UP    = 0,
    DBUS_KEY_CLICK = 1,
    DBUS_KEY_PRESS = 2
} KeyState_Env;

/* ---------- VT13 按键状态 ---------- */
typedef enum {
    VT13_KEY_UP    = 0,
    VT13_KEY_CLICK = 1,
    VT13_KEY_PRESS = 2
} VT13_KeyState_Env;

/* ---------- PID 改进模式 ---------- */
typedef enum pid_Improvement_e {
    NONE                        = 0X00,
    Integral_Limit              = 0x01,
    Derivative_On_Measurement   = 0x02,
    Trapezoid_Intergral         = 0x04,
    Proportional_On_Measurement = 0x08,
    OutputFilter                = 0x10,
    ChangingIntegrationRate     = 0x20,
    DerivativeFilter            = 0x40,
    ErrorHandle                 = 0x80,
} PID_Improvement_e;

/* ---------- PID 错误类型 ---------- */
typedef enum errorType_e {
    PID_ERROR_NONE  = 0x00U,
    Motor_Blocked   = 0x01U
} ErrorType_e;

/* ---------- DJI 经典 PID 模式 ---------- */
enum PID_MODE {
    PID_POSITION = 0,
    PID_DELTA
};

/* ---------- 达妙电机指令 ---------- */
typedef enum {
    DM_CMD_MOTOR_MODE       = 0xfc,
    DM_CMD_RESET_MODE       = 0xfd,
    DM_CMD_ZERO_POSITION    = 0xfe,
    DM_CMD_CLEAR_ERROR      = 0xfb
} DMMotor_Mode_e;

/* ---------- IMU 状态机 ---------- */
typedef enum {
    TEMP_INIT     = 0,
    TEMP_PID_CTRL,
    TEMP_STABLE,
    GYRO_CALIB,
    FUSION_RUN,
    ERROR_STATE
} IMU_CTRL_STATE_e;

/* ---------- 调试模式 ---------- */
enum {
    CHASSIS_DEBUG    = 1,
    GIMBAL_DEBUG,
    INS_DEBUG,
    RC_DEBUG,
    IMU_HEAT_DEBUG,
    SHOOT_DEBUG,
    AIMASSIST_DEBUG,
};

/* ---------- 裁判系统 CMD ID ---------- */
enum Read_Cmd_ID_Typdef {
    game_state                  = 0x0001,
    Match_results               = 0x0002,
    Robot_HP                    = 0x0003,
    Venue_Events                = 0x0101,
    Referee_warning             = 0x0104,
    Dart_fire                   = 0x0105,
    Robot_performan             = 0x0201,
    time_power                  = 0x0202,
    Robot_location              = 0x0203,
    Robot_buff                  = 0x0204,
    Damage_status               = 0x0206,
    time_shooting               = 0x0207,
    Allowable_ammo              = 0x0208,
    RFID_status                 = 0x0209,
    Dart_directives             = 0x020A,
    Ground_location             = 0x020B,
    Radar_Marking               = 0x020C,
    Route_Informat              = 0x020D,
    Radar_Informat              = 0x020E,
    Robot_Interaction           = 0x0301,
    Custom_controller_to_robot  = 0x0302,
    Minimap                     = 0x0303,
    Map_receive_radar           = 0x0305,
    Custom_controller_to_map    = 0x0306,
    Map_receive_path            = 0x0307,
    Map_receive_robot_info      = 0x0308,
    Robot_to_custom_controller  = 0x0309,
    Robot_to_custom_client      = 0x0310,
    Custom_client_to_robot      = 0x0311
};

/* ============================================================
 * 简单数据结构（不依赖其他项目类型）
 * ============================================================ */

/* ---------- DWT 时间 ---------- */
typedef struct {
    uint32_t s;
    uint16_t ms;
    uint16_t us;
} DWT_Time_t;

/* ---------- 斜坡函数 ---------- */
typedef struct {
    float input;
    float out;
    float min_value;
    float max_value;
    float frame_period;
} ramp_function_source_t;

/* ---------- 最小二乘 ---------- */
typedef struct __packed {
    uint16_t Order;
    uint32_t Count;
    float *x;
    float *y;
    float k;
    float b;
    float StandardDeviation;
    float t[4];
} Ordinary_Least_Squares_t;

/* ---------- 三维向量 ---------- */
typedef struct {
    float x;
    float y;
    float z;
} Axis3f;

/* ---------- 电压输入 ---------- */
typedef struct {
    uint16_t adc_val[2];
    float vbus;
} V_Input_t;

/* ---------- PID 错误处理 ---------- */
typedef struct __packed {
    uint64_t ERRORCount;
    ErrorType_e ERRORType;
} PID_ErrorHandler_t;

/* ---------- 底盘初始化参数（麦轮） ---------- */
typedef struct {
    float wheel_perimeter;
    float wheeltrack;
    float wheelbase;
    float rotate_x_offset;
    float rotate_y_offset;
    float deceleration_ratio;
    int max_vx_speed;
    int max_vy_speed;
    int max_vw_speed;
    int max_wheel_ramp;
    float raid_fr;
    float raid_fl;
    float raid_bl;
    float raid_br;
    float wheel_rpm_ratio;
} mecanumInit_typdef;

/* ---------- 底盘初始化参数（全向） ---------- */
typedef struct {
    float wheel_perimeter;
    float CHASSIS_DECELE_RATIO;
    float LENGTH_A;
    float LENGTH_B;
} OmniInit_typdef;

/* ---------- IMU 状态标志 ---------- */
typedef struct {
    uint8_t temp_reached;
    uint8_t temp_stable;
    uint8_t gyro_calib_done;
    uint8_t fusion_enabled;
} IMU_CTRL_FLAG_t;

/* ---------- IMU 数据 ---------- */
typedef struct {
    float gyro_correct[3];
    float gyro[3];
    float accel[3];
    float temp;
    float q[4];
    float pitch;
    float roll;
    float yaw;
    float YawTotalAngle;
    float guolingjiesuan_yaw;
    uint32_t correct_times;
} IMU_Data_t;

/* ---------- DJI 经典 PID ---------- */
typedef struct {
    uint8_t mode;
    float Kp;
    float Ki;
    float Kd;
    float max_out;
    float max_iout;
    float set;
    float fdb;
    float out;
    float Pout;
    float Iout;
    float Dout;
    float Dbuf[3];
    float error[3];
} pid_type_def;

/* ---------- 电容接收数据 ---------- */
typedef struct {
    float BUFFER;
    float CAP_VOLT;
    float NOW_POWER;
    int16_t OUT_BOLL;
    int8_t ONLINE_JUDGE_TIME;
} CAP_RXDATA;

/* ---------- 电容发送联合体 ---------- */
typedef union {
    struct __packed {
        uint8_t BUFFER_NOW;
        uint8_t MAX_POWER;
        uint8_t VOLT;
        uint8_t OUT_POWER;
        uint8_t OUT_SWITCH;
        uint8_t POWER_KEY;
    } CHANNAL;
    uint8_t SEND_DATA[8];
} CAP_SETDATA;

/* ---------- 电容数据聚合 ---------- */
typedef struct {
    CAP_SETDATA SET;
    CAP_RXDATA GET;
} CAPDATE_TYPDEF;

/* ---------- 功率 PID 缓冲 ---------- */
typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float ILt;
    float AlLt;
    float Error[2];
    float P_out;
    float I_out;
    float D_out;
    float All_out;
} PID_buffer_t;

/* ---------- 功率模型 ---------- */
typedef struct {
    PID_buffer_t PID_Buffer;
    float scaled_give_power[4];
    float toque_coefficient;
    float a;
    float k2;
    float constant;
} model_t;

/* ============================================================
 * 控制器结构体
 * ============================================================ */

/* ---------- 模糊规则 ---------- */
typedef struct __packed {
    float KpFuzzy;
    float KiFuzzy;
    float KdFuzzy;
    float (*FuzzyRuleKp)[7];
    float (*FuzzyRuleKi)[7];
    float (*FuzzyRuleKd)[7];
    float KpRatio;
    float KiRatio;
    float KdRatio;
    float eStep;
    float ecStep;
    float e;
    float ec;
    float eLast;
    uint32_t DWT_CNT;
    float dt;
} FuzzyRule_t;

/* ---------- PID ---------- */
typedef struct pid_t {
    float Ref;
    float Kp;
    float Ki;
    float Kd;
    float Measure;
    float Last_Measure;
    float Err;
    float Last_Err;
    float Last_ITerm;
    float Pout;
    float Iout;
    float Dout;
    float ITerm;
    float Output;
    float Last_Output;
    float Last_Dout;
    float MaxOut;
    float IntegralLimit;
    float DeadBand;
    float ControlPeriod;
    float CoefA;
    float CoefB;
    float Output_LPF_RC;
    float Derivative_LPF_RC;
    uint16_t OLS_Order;
    Ordinary_Least_Squares_t OLS;
    uint32_t DWT_CNT;
    float dt;
    FuzzyRule_t *FuzzyRule;
    uint8_t Improve;
    PID_ErrorHandler_t ERRORHandler;
    void (*User_Func1_f)(struct pid_t *pid);
    void (*User_Func2_f)(struct pid_t *pid);
} PID_t;

/* ---------- 前馈 ---------- */
typedef struct __packed {
    float c[3];
    float Ref;
    float Last_Ref;
    float DeadBand;
    uint32_t DWT_CNT;
    float dt;
    float LPF_RC;
    float Ref_dot;
    float Ref_ddot;
    float Last_Ref_dot;
    uint16_t Ref_dot_OLS_Order;
    Ordinary_Least_Squares_t Ref_dot_OLS;
    uint16_t Ref_ddot_OLS_Order;
    Ordinary_Least_Squares_t Ref_ddot_OLS;
    float Output;
    float MaxOut;
} Feedforward_t;

/* ---------- 线性干扰观测器 ---------- */
typedef struct __packed {
    float c[3];
    float Measure;
    float Last_Measure;
    float u;
    float DeadBand;
    uint32_t DWT_CNT;
    float dt;
    float LPF_RC;
    float Measure_dot;
    float Measure_ddot;
    float Last_Measure_dot;
    uint16_t Measure_dot_OLS_Order;
    Ordinary_Least_Squares_t Measure_dot_OLS;
    uint16_t Measure_ddot_OLS_Order;
    Ordinary_Least_Squares_t Measure_ddot_OLS;
    float Disturbance;
    float Output;
    float Last_Disturbance;
    float Max_Disturbance;
} LDOB_t;

/* ---------- 跟踪微分器 ---------- */
typedef struct __packed {
    float Input;
    float h0;
    float r;
    float x;
    float dx;
    float ddx;
    float last_dx;
    float last_ddx;
    uint32_t DWT_CNT;
    float dt;
} TD_t;

/* ============================================================
 * 电机数据结构
 * ============================================================ */

/* ---------- DJI 电机数据 ---------- */
typedef struct {
    int8_t  ONLINE_JUDGE_TIME;
    int16_t Angle_last;
    int16_t Angle_now;
    int16_t Speed_last;
    int16_t Speed_now;
    int16_t acceleration;
    int16_t conEncode;
    int16_t current;
    int8_t  temperature;
    int32_t Angle_Infinite;
    int64_t Stuck_Time;
    uint16_t Stuck_Flag[2];
    int16_t Laps;
    float Error;
    float Aim;
    float Aim_last;
    float dt;
} DJI_MOTOR_DATA_Typedef;

/* ---------- 电机控制模式 ---------- */
typedef struct {
    uint8_t mode;
    float pos_set;
    float vel_set;
    float tor_set;
    float cur_set;
    float kp_set;
    float kd_set;
} motor_ctrl_t;

/* ---------- DM 电机 PV 数据 ---------- */
typedef struct {
    float POS;
    float SPE;
} DM_MOTOR_PV_Typdef;

/* ---------- 达妙电机数据 ---------- */
typedef struct {
    int id;
    int state;
    int p_int;
    int v_int;
    int t_int;
    int kp_int;
    int kd_int;
    float pos;
    float vel;
    float tor;
    float Kp;
    float Kd;
    float Tmos;
    float Tcoil;
    int16_t Angle_last;
    int16_t Angle_now;
    int16_t Speed_last;
    int16_t Speed_now;
    int16_t acceleration;
    float current;
    int8_t temperature;
    int32_t Angle_Infinite;
    int64_t Stuck_Time;
    uint16_t Stuck_Flag[2];
    int16_t Laps;
    float Error;
    float Aim;
    float Aim_last;
    float dt;
    int8_t ONLINE_JUDGE_TIME;
    uint16_t initialAngle;
    float ralativeAngle;
    int16_t round;
    int32_t reality;
} DM_MOTOR_DATA_Typdef;

/* ---------- 达妙反馈参数 ---------- */
typedef struct {
    uint16_t id;
    uint16_t state;
    int p_int;
    int v_int;
    int t_int;
    int kp_int;
    int kd_int;
    float tor;
    float Kp;
    float Kd;
    float Tmos;
    float Tcoil;
    float aim;
    float cur;
    int16_t pos[2];
    int16_t vel[2];
    int16_t round;
    int32_t reality;
    uint16_t initialAngle;
    float ralativeAngle;
} motor_fbpara_t;

/* ---------- 达妙附加 PID ---------- */
typedef struct {
    float kp;
    float ki;
    float kd;
    float epsilon;
    int32_t iLt;
    int32_t alLt;
    float error[2];
    float p_out;
    float i_out;
    int32_t d_out;
    float all_out;
} PID_typedef;

/* ---------- 达妙前馈 ---------- */
typedef struct {
    float A;
    float B;
    float rin;
    float lastRin;
    float perrRin;
} FFC_typedef;

/* ---------- DJI 电机聚合 ---------- */
typedef struct {
    uint8_t PID_INIT;
    DJI_MOTOR_DATA_Typedef DATA;
    Feedforward_t PID_F;
    PID_t PID_P;
    PID_t PID_S;
    DM_MOTOR_PV_Typdef PV;
    motor_ctrl_t motor_ctrl;
} DJI_MOTOR_Typedef;

/* ---------- 达妙电机聚合 ---------- */
typedef struct {
    uint8_t PID_INIT;
    DM_MOTOR_DATA_Typdef DATA;
    Feedforward_t PID_F;
    PID_t PID_P;
    PID_t PID_S;
} DM_MOTOR_Typdef;

/* ---------- 关节电机 ---------- */
typedef struct {
    uint16_t mode[2];
    motor_fbpara_t para;
    FFC_typedef FFC;
    PID_typedef PID_P;
    PID_typedef PID_S;
} Joint_Motor_t;

/* ============================================================
 * 通讯协议结构体
 * ============================================================ */

/* ---------- DBUS 解析结果 ---------- */
typedef struct {
    int8_t ONLINE_JUDGE_TIME;
    int8_t Ctrl_Mode;
    struct {
        int16_t CH0;
        int16_t CH1;
        int16_t CH2;
        int16_t CH3;
        int16_t Dial;
        uint8_t S1;
        uint8_t S2;
        int8_t Error;
    } Remote;
    struct {
        float X_Flt;
        float Y_Flt;
        float Z_Flt;
        uint8_t L_State;
        uint8_t R_State;
        uint8_t L_PressTime;
        uint8_t R_PressTime;
    } Mouse;
    struct {
        uint8_t W;
        uint8_t S;
        uint8_t A;
        uint8_t D;
        uint8_t Shift;
        uint8_t Ctrl;
        uint8_t Q;
        uint8_t E;
        uint8_t R;
        uint8_t F;
        uint8_t G;
        uint8_t Z;
        uint8_t X;
        uint8_t C;
        uint8_t V;
        uint8_t B;
        uint8_t W_PressTime;
        uint8_t S_PressTime;
        uint8_t A_PressTime;
        uint8_t D_PressTime;
        uint8_t Shift_PreeNumber;
        uint8_t Ctrl_PreeNumber;
        uint8_t Q_PreeNumber;
        uint8_t E_PreeNumber;
        uint8_t R_PreeNumber;
        uint8_t F_PreeNumber;
        uint8_t G_PreeNumber;
        uint8_t Z_PreeNumber;
        uint8_t X_PreeNumber;
        uint8_t C_PreeNumber;
        uint8_t V_PreeNumber;
        uint8_t B_PreeNumber;
    } KeyBoard;
} DBUS_Typedef;

/* ---------- DBUS 原始帧 ---------- */
#pragma pack(push, 1)
typedef struct {
    uint64_t channel0        : 11;
    uint64_t channel1        : 11;
    uint64_t channel2        : 11;
    uint64_t channel3        : 11;
    uint64_t switch_right    : 2;
    uint64_t switch_left     : 2;
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    uint8_t mouse_press_l;
    uint8_t mouse_press_r;
    uint16_t key_w           : 1;
    uint16_t key_s           : 1;
    uint16_t key_a           : 1;
    uint16_t key_d           : 1;
    uint16_t key_shift       : 1;
    uint16_t key_ctrl        : 1;
    uint16_t key_q           : 1;
    uint16_t key_e           : 1;
    uint16_t key_r           : 1;
    uint16_t key_f           : 1;
    uint16_t key_g           : 1;
    uint16_t key_z           : 1;
    uint16_t key_x           : 1;
    uint16_t key_c           : 1;
    uint16_t key_v           : 1;
    uint16_t key_b           : 1;
    uint16_t dial            : 11;
    uint16_t reserved        : 5;
} DBUS_FrameTypeDef;
#pragma pack(pop)

/* ---------- DBUS 联合体 ---------- */
typedef union {
    uint8_t GetData[18];
    DBUS_FrameTypeDef Frame;
} DBUS_UNION_TypeDef;

/* ---------- VT13 解析结果 ---------- */
typedef struct {
    int8_t ONLINE_JUDGE_TIME;
    int8_t Ctrl_Mode;
    bool CRC_flag;
    struct {
        int16_t Channel[4];
        uint8_t mode_sw;
        uint8_t pause;
        uint8_t fn_1;
        uint8_t fn_2;
        int16_t wheel;
        uint8_t trigger;
    } Remote;
    struct {
        float X_Flt;
        float Y_Flt;
        float Z_Flt;
        uint8_t R_State;
        uint8_t L_State;
        uint8_t M_State;
        uint8_t R_PressTime;
        uint8_t L_PressTime;
        uint8_t M_PressTime;
    } Mouse;
    struct {
        uint8_t W;
        uint8_t S;
        uint8_t A;
        uint8_t D;
        uint8_t Shift;
        uint8_t Ctrl;
        uint8_t Q;
        uint8_t E;
        uint8_t R;
        uint8_t F;
        uint8_t G;
        uint8_t Z;
        uint8_t X;
        uint8_t C;
        uint8_t V;
        uint8_t B;
        uint8_t W_PressTime;
        uint8_t S_PressTime;
        uint8_t A_PressTime;
        uint8_t D_PressTime;
        uint8_t Shift_PreeNumber;
        uint8_t Ctrl_PreeNumber;
        uint8_t Q_PreeNumber;
        uint8_t E_PreeNumber;
        uint8_t R_PreeNumber;
        uint8_t F_PreeNumber;
        uint8_t G_PreeNumber;
        uint8_t Z_PreeNumber;
        uint8_t X_PreeNumber;
        uint8_t C_PreeNumber;
        uint8_t V_PreeNumber;
        uint8_t B_PreeNumber;
    } KeyBoard;
} VT13_Typedef;

/* ---------- VT13 原始帧 ---------- */
#pragma pack(push, 1)
typedef struct {
    uint8_t header1;
    uint8_t header2;
    uint16_t channel0    : 11;
    uint16_t channel1    : 11;
    uint16_t channel2    : 11;
    uint16_t channel3    : 11;
    uint16_t mode_sw     : 2;
    uint16_t pause       : 1;
    uint16_t fn_1        : 1;
    uint16_t fn_2        : 1;
    uint16_t wheel       : 11;
    uint16_t trigger     : 1;
    uint16_t reserved1   : 3;
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    uint8_t mouse_l      : 2;
    uint8_t mouse_r      : 2;
    uint8_t mouse_m      : 2;
    uint8_t reserved2    : 2;
    uint16_t key_w       : 1;
    uint16_t key_s       : 1;
    uint16_t key_a       : 1;
    uint16_t key_d       : 1;
    uint16_t key_shift   : 1;
    uint16_t key_ctrl    : 1;
    uint16_t key_q       : 1;
    uint16_t key_e       : 1;
    uint16_t key_r       : 1;
    uint16_t key_f       : 1;
    uint16_t key_g       : 1;
    uint16_t key_z       : 1;
    uint16_t key_x       : 1;
    uint16_t key_c       : 1;
    uint16_t key_v       : 1;
    uint16_t key_b       : 1;
    uint16_t crc16;
} VT13_FrameTypeDef;
#pragma pack(pop)

/* ---------- VT13 联合体 ---------- */
typedef union {
    uint8_t GetData[21];
    VT13_FrameTypeDef Frame;
} VT13_UNION_Typdef;

/* ============================================================
 * 裁判系统协议结构体（全部 __packed）
 * ============================================================ */

/* ---------- 帧头 ---------- */
typedef struct __packed {
    uint8_t  SOF;
    uint16_t DataLenth;
    uint8_t  Seq;
    uint8_t  CRC8;
} frame_header_R_Typdef;

/* ---------- 比赛状态 ---------- */
typedef struct __packed {
    uint8_t game_type : 4;
    uint8_t game_progress : 4;
    uint16_t stage_remain_time;
    uint64_t SyncTimeStamp;
} game_status_t;

/* ---------- 比赛结果 ---------- */
typedef struct __packed {
    uint8_t winner;
} game_result_t;

/* ---------- 血量 ---------- */
typedef struct __packed {
    uint16_t ally_1_robot_HP;
    uint16_t ally_2_robot_HP;
    uint16_t ally_3_robot_HP;
    uint16_t ally_4_robot_HP;
    uint16_t reserved;
    uint16_t ally_7_robot_HP;
    uint16_t ally_outpost_HP;
    uint16_t ally_base_HP;
} game_robot_HP_t;

/* ---------- 场地事件 ---------- */
typedef struct __packed {
    uint32_t supply_zone_status : 1;
    uint32_t reserved_1 : 1;
    uint32_t supply_zone_status_rmul : 1;
    uint32_t small_energy_mechanism_status : 2;
    uint32_t big_energy_mechanism_status : 2;
    uint32_t central_highland_status : 2;
    uint32_t trapezoidal_highland_status : 2;
    uint32_t dart_hit_time : 9;
    uint32_t dart_hit_target : 3;
    uint32_t center_buff_status : 2;
    uint32_t fortress_buff_status : 2;
    uint32_t outpost_buff_status : 2;
    uint32_t base_buff_status : 1;
    uint32_t reserved_2 : 2;
} event_data_t;

/* ---------- 裁判警告 ---------- */
typedef struct __packed {
    uint8_t level;
    uint8_t offending_robot_id;
    uint8_t count;
} referee_warning_t;

/* ---------- 飞镖 ---------- */
typedef struct __packed {
    uint8_t dart_remaining_time;
    uint16_t dart_hit_target : 3;
    uint16_t dart_hit_count : 3;
    uint16_t dart_selected_target : 3;
    uint16_t reserved : 7;
} dart_info_t;

/* ---------- 机器人状态 ---------- */
typedef struct __packed {
    uint8_t robot_id;
    uint8_t robot_level;
    uint16_t current_HP;
    uint16_t maximum_HP;
    uint16_t shooter_barrel_cooling_value;
    uint16_t shooter_barrel_heat_limit;
    uint16_t chassis_power_limit;
    uint8_t power_management_gimbal_output : 1;
    uint8_t power_management_chassis_output : 1;
    uint8_t power_management_shooter_output : 1;
    uint8_t reserved_power_management : 5;
} robot_status_t;

/* ---------- 功率热量 ---------- */
typedef struct __packed {
    uint16_t reserved_1;
    uint16_t reserved_2;
    float reserved_3;
    uint16_t buffer_energy;
    uint16_t shooter_17mm_barrel_heat;
    uint16_t shooter_42mm_barrel_heat;
} power_heat_data_t;

/* ---------- 机器人位置 ---------- */
typedef struct __packed {
    float x;
    float y;
    float angle;
} robot_pos_t;

/* ---------- 增益 buff ---------- */
typedef struct __packed {
    uint8_t recovery_buff;
    uint16_t cooling_buff;
    uint8_t defence_buff;
    uint8_t vulnerability_buff;
    uint16_t attack_buff;
    uint8_t energy_125 : 1;
    uint8_t energy_100 : 1;
    uint8_t energy_50 : 1;
    uint8_t energy_30 : 1;
    uint8_t energy_15 : 1;
    uint8_t energy_5 : 1;
    uint8_t energy_1 : 1;
    uint8_t energy_reserved : 1;
} buff_t;

/* ---------- 伤害 ---------- */
typedef struct __packed {
    uint8_t armor_id : 4;
    uint8_t HP_deduction_reason : 4;
} hurt_data_t;

/* ---------- 射击 ---------- */
typedef struct __packed {
    uint8_t reserved_1 : 1;
    uint8_t bullet_type_17mm : 1;
    uint8_t bullet_type_42mm : 1;
    uint8_t reserved_2 : 5;
    uint8_t shooter_number;
    uint8_t launching_frequency;
    float initial_speed;
} shoot_data_t;

/* ---------- 弹量 ---------- */
typedef struct __packed {
    uint16_t projectile_allowance_17mm;
    uint16_t projectile_allowance_42mm;
    uint16_t remaining_gold_coin;
    uint16_t projectile_allowance_fortress;
} projectile_allowance_t;

/* ---------- RFID ---------- */
typedef struct __packed {
    uint32_t ally_base : 1;
    uint32_t ally_central_highland : 1;
    uint32_t enemy_central_highland : 1;
    uint32_t ally_trapezoidal_highland : 1;
    uint32_t enemy_trapezoidal_highland : 1;
    uint32_t ally_fly_ramp_front : 1;
    uint32_t ally_fly_ramp_back : 1;
    uint32_t enemy_fly_ramp_front : 1;
    uint32_t enemy_fly_ramp_back : 1;
    uint32_t ally_central_highland_lower : 1;
    uint32_t ally_central_highland_upper : 1;
    uint32_t enemy_central_highland_lower : 1;
    uint32_t enemy_central_highland_upper : 1;
    uint32_t ally_highway_lower : 1;
    uint32_t ally_highway_upper : 1;
    uint32_t enemy_highway_lower : 1;
    uint32_t enemy_highway_upper : 1;
    uint32_t ally_fortress : 1;
    uint32_t ally_outpost : 1;
    uint32_t ally_supply_zone_not_overlapping : 1;
    uint32_t ally_supply_zone_overlapping : 1;
    uint32_t ally_assembly_zone : 1;
    uint32_t enemy_assembly_zone : 1;
    uint32_t center_buff_zone : 1;
    uint32_t enemy_fortress : 1;
    uint32_t enemy_outpost : 1;
    uint32_t ally_tunnel_highway_lower : 1;
    uint32_t ally_tunnel_highway_middle : 1;
    uint32_t ally_tunnel_highway_upper : 1;
    uint32_t ally_tunnel_trapezoidal_lower : 1;
    uint32_t ally_tunnel_trapezoidal_middle : 1;
    uint32_t ally_tunnel_trapezoidal_upper : 1;
    uint8_t enemy_tunnel_highway_lower : 1;
    uint8_t enemy_tunnel_highway_middle : 1;
    uint8_t enemy_tunnel_highway_upper : 1;
    uint8_t enemy_tunnel_trapezoidal_lower : 1;
    uint8_t enemy_tunnel_trapezoidal_middle : 1;
    uint8_t enemy_tunnel_trapezoidal_upper : 1;
    uint8_t reserved_tunnel : 2;
} rfid_status_t;

/* ---------- 飞镖客户端指令 ---------- */
typedef struct __packed {
    uint8_t dart_launch_opening_status;
    uint8_t reserved;
    uint16_t target_change_time;
    uint16_t latest_launch_cmd_time;
} dart_client_cmd_t;

/* ---------- 地面机器人位置 ---------- */
typedef struct __packed {
    float hero_x;
    float hero_y;
    float engineer_x;
    float engineer_y;
    float standard_3_x;
    float standard_3_y;
    float standard_4_x;
    float standard_4_y;
    float reserved_1;
    float reserved_2;
} ground_robot_position_t;

/* ---------- 雷达标记 ---------- */
typedef struct __packed {
    uint16_t enemy_hero_mark : 1;
    uint16_t enemy_engineer_mark : 1;
    uint16_t enemy_infantry_3_mark : 1;
    uint16_t enemy_infantry_4_mark : 1;
    uint16_t enemy_aerial_mark : 1;
    uint16_t enemy_sentry_mark : 1;
    uint16_t ally_hero_mark : 1;
    uint16_t ally_engineer_mark : 1;
    uint16_t ally_infantry_3_mark : 1;
    uint16_t ally_infantry_4_mark : 1;
    uint16_t ally_aerial_mark : 1;
    uint16_t ally_sentry_mark : 1;
    uint16_t reserved : 4;
} radar_mark_data_t;

/* ---------- 哨兵信息 ---------- */
typedef struct __packed {
    uint32_t sentry_redeemed_projectile_allowance : 11;
    uint32_t sentry_remote_redeemed_projectile_times : 4;
    uint32_t sentry_remote_redeemed_HP_times : 4;
    uint32_t can_confirm_free_revive : 1;
    uint32_t can_redeem_immediate_revive : 1;
    uint32_t cost_for_immediate_revive : 10;
    uint32_t reserved_1 : 1;
    uint16_t is_out_of_combat : 1;
    uint16_t remaining_redeemable_projectile_allowance : 11;
    uint16_t sentry_posture : 2;
    uint16_t can_enter_activating_state : 1;
    uint16_t reserved_2 : 1;
} sentry_info_t;

/* ---------- 雷达信息 ---------- */
typedef struct __packed {
    uint8_t radar_double_damage_chance : 2;
    uint8_t enemy_is_double_damaged : 1;
    uint8_t ally_encryption_level : 2;
    uint8_t can_modify_password : 1;
    uint8_t reserved : 2;
} radar_info_t;

/* ---------- 机器人交互 ---------- */
typedef struct __packed {
    uint16_t data_cmd_id;
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t user_data[112];
} robot_interaction_data_t;

/* ---------- 图形交互 ---------- */
typedef struct __packed {
    uint8_t figure_name[3];
    uint32_t operate_tpye : 3;
    uint32_t figure_tpye : 3;
    uint32_t layer : 4;
    uint32_t color : 4;
    uint32_t details_a : 9;
    uint32_t details_b : 9;
    uint32_t width : 10;
    uint32_t start_x : 11;
    uint32_t start_y : 11;
    uint32_t details_c : 10;
    uint32_t details_d : 11;
    uint32_t details_e : 11;
} interaction_figure_t;

/* ---------- UI 字符 ---------- */
typedef struct __packed {
    uint16_t data_id;
    uint16_t tx_id;
    uint16_t rx_id;
    uint8_t Character_configuration[15];
    uint8_t Character[30];
} graphic_data_struct_t;

/* ---------- 小地图指令 ---------- */
typedef struct __packed {
    float target_position_x;
    float target_position_y;
    uint8_t cmd_keyboard;
    uint8_t target_robot_id;
    uint16_t cmd_source;
} map_command_t;

/* ---------- 哨兵指令 ---------- */
typedef struct __packed {
    uint32_t confirm_resurrection : 1;
    uint32_t confirm_immediate_resurrection : 1;
    uint32_t redeem_projectile_allowance : 11;
    uint32_t remote_redeem_projectile_request_times : 4;
    uint32_t remote_redeem_HP_request_times : 4;
    uint32_t sentry_posture_cmd : 2;
    uint32_t confirm_activate_energy_mechanism : 1;
    uint32_t reserved : 8;
} sentry_cmd_t;

/* ---------- 雷达指令 ---------- */
typedef struct __packed {
    uint8_t radar_double_damage_cmd;
    uint8_t password_cmd;
    uint8_t password_1;
    uint8_t password_2;
    uint8_t password_3;
    uint8_t password_4;
    uint8_t password_5;
    uint8_t password_6;
} radar_cmd_t;

/* ---------- 地图机器人数据 ---------- */
typedef struct __packed {
    uint16_t hero_position_x;
    uint16_t hero_position_y;
    uint16_t engineer_position_x;
    uint16_t engineer_position_y;
    uint16_t infantry_3_position_x;
    uint16_t infantry_3_position_y;
    uint16_t infantry_4_position_x;
    uint16_t infantry_4_position_y;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint16_t sentry_position_x;
    uint16_t sentry_position_y;
} map_robot_data_t;

/* ---------- 路径数据 ---------- */
typedef struct __packed {
    uint8_t intention;
    uint16_t start_position_x;
    uint16_t start_position_y;
    int8_t delta_x[49];
    int8_t delta_y[49];
    uint16_t sender_id;
} map_data_t;

/* ---------- 自定义信息 ---------- */
typedef struct __packed {
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t user_data[30];
} custom_info_t;

/* ---------- 键鼠数据 ---------- */
typedef struct __packed {
    uint16_t key_value;
    uint16_t x_position : 12;
    uint16_t mouse_left : 4;
    uint16_t y_position : 12;
    uint16_t mouse_right : 4;
    uint16_t reserved;
} custom_client_data_t;

/* ---------- 用户数据聚合 ---------- */
typedef struct __packed {
    int8_t ONLINE_JUDGE_TIME;
    game_status_t game_status;
    game_result_t game_result;
    game_robot_HP_t game_robot_HP;
    referee_warning_t referee_warning;
    dart_info_t dart_info;
    robot_status_t robot_status;
    power_heat_data_t power_heat_data;
    robot_pos_t robot_pos;
    buff_t buff;
    hurt_data_t hurt_data;
    shoot_data_t shoot_data;
    projectile_allowance_t projectile_allowance;
    rfid_status_t rfid_status;
    dart_client_cmd_t dart_client_cmd;
    ground_robot_position_t ground_robot_position;
    radar_mark_data_t radar_mark_data;
    sentry_info_t sentry_info;
    radar_info_t radar_info;
    map_command_t map_command;
    event_data_t event_data;
    custom_info_t custom_info;
} User_Data_T;

/* ---------- 接收数据联合体 ---------- */
typedef union {
    struct __packed {
        frame_header_R_Typdef frame_header;
        uint16_t read_cmd_id;
    } RX_Data_head;

    struct __packed {
        frame_header_R_Typdef frame_header;
        uint16_t read_cmd_id;
        game_status_t game_status;
        uint16_t frame_tail;
    } RX_Data_game_status;

    struct __packed {
        frame_header_R_Typdef frame_header;
        uint16_t read_cmd_id;
        robot_status_t robot_status;
        uint16_t frame_tail;
    } RX_Data_robot_status;

    uint8_t Data[255];
} ALL_RX_Data_T;
//板间通信发送与接收联合体
typedef union
{
    struct __packed
    {
        uint8_t remote_ch[8];
        uint8_t remote_s[8];
        uint8_t Y_w[8];
        uint8_t Z_w[8];

    } Send_Data;

    struct  __packed
    {
        IMU_Data_t IMU_Data;
        DBUS_Typedef DBUS;
        float Chassis_Vw;
        float Gimbal_Yaw_rad;
        float Gimabal_Yaw_degree;
    }Receive_Data;
}board_Data_t;

typedef union
{
    struct __packed
    {
        float yaw_imu;
    } dataNeaten;
    uint8_t rxData[8];
}boardRxData_t;

/* ============================================================
 * 视觉/陀螺仪结构体
 * ============================================================ */

/* ---------- 视觉接收联合体 ---------- */
union RUI_U_VISION_RECEIVE {
    struct {
        float PIT_DATA;
        float YAW_DATA;
        bool TARGET;
        bool fire;
        bool state;
        float Yaw_plan;
        float Pitch_plan;
    };
    uint8_t DATA[23];
};

/* ---------- 视觉发送联合体 ---------- */
union RUI_U_VISION_SEND {
    struct {
        float PIT_DATA;
        float YAW_DATA;
        float ROLL_DATA;
        float INIT_FIRING_RATE;
        int FLAG;
        bool COLOR;
        uint8_t is_buff;
        uint32_t TIME;
        uint8_t bulletSpeed;
        float YawOmega;
        float PitchOmega;
    };
    uint8_t DATA[24];
};

/* ---------- 视觉数据 ---------- */
typedef struct TYPEDEF_VISION {
    union RUI_U_VISION_RECEIVE RECEIVE;
    union RUI_U_VISION_SEND SEND;
    uint8_t OriginData[19];
    uint8_t RECV_FLAG[2];
    int RECV_OutTime;
    uint32_t block_Time;
} TYPEDEF_VISION;

/* ---------- 视觉浮点转换 ---------- */
typedef union ReceiveDataUnion_typedef {
    uint8_t U[4];
    float F;
    uint32_t I;
} VisionTemp;

/* ---------- 陀螺仪 TOP 数据 ---------- */
typedef struct TYPEDEF_TOP_DATA {
    float REALITY_ANGLE;
    int16_t YAW_ANGLE[2];
    float YAW_ANGLE_F;
    int16_t YAW_SPEED[2];
    int16_t PIT_ANGLE[2];
    float PIT_ANGLE_F;
    int16_t PIT_SPEED[2];
    int16_t ROUND;
} TYPEDEF_TOP_DATA;

/* ---------- 陀螺仪 TOP 联合体 ---------- */
typedef union TYPEDEF_TOP_DATA_UNION {
    struct {
        int16_t YAW_ANGLE;
        int16_t PIT_ANGLE;
        int16_t YAW_SPEED;
        int16_t PIT_SPEED;
    };
    uint8_t GET_DATA[8];
} TYPEDEF_TOP_DATA_UNION;

/* ---------- 陀螺仪 TOP 聚合 ---------- */
typedef struct TYPEDEF_TOP {
    float yaw[6];
    float pitch[6];
    float roll[6];
} TYPEDEF_TOP;

/* ============================================================
 * 卡尔曼滤波 / Mahony / SMC 结构体
 * ============================================================ */

/* ---------- 卡尔曼滤波 ---------- */
typedef struct kf_t {
    float *FilteredValue;
    float *MeasuredVector;
    float *ControlVector;
    uint8_t xhatSize;
    uint8_t uSize;
    uint8_t zSize;
    uint8_t UseAutoAdjustment;
    uint8_t MeasurementValidNum;
    uint8_t *MeasurementMap;
    float *MeasurementDegree;
    float *MatR_DiagonalElements;
    float *StateMinVariance;
    uint8_t *temp;
    uint8_t SkipEq1, SkipEq2, SkipEq3, SkipEq4, SkipEq5;
    mat xhat;
    mat xhatminus;
    mat u;
    mat z;
    mat P;
    mat Pminus;
    mat F, FT;
    mat B;
    mat H, HT;
    mat Q;
    mat R;
    mat K;
    mat S, temp_matrix, temp_matrix1, temp_vector, temp_vector1;
    int8_t MatStatus;
    void (*User_Func0_f)(struct kf_t *kf);
    void (*User_Func1_f)(struct kf_t *kf);
    void (*User_Func2_f)(struct kf_t *kf);
    void (*User_Func3_f)(struct kf_t *kf);
    void (*User_Func4_f)(struct kf_t *kf);
    void (*User_Func5_f)(struct kf_t *kf);
    void (*User_Func6_f)(struct kf_t *kf);
    float *xhat_data, *xhatminus_data;
    float *u_data;
    float *z_data;
    float *P_data, *Pminus_data;
    float *F_data, *FT_data;
    float *B_data;
    float *H_data, *HT_data;
    float *Q_data;
    float *R_data;
    float *K_data;
    float *S_data, *temp_matrix_data, *temp_matrix_data1, *temp_vector_data, *temp_vector_data1;
} KalmanFilter_t;

/* ---------- EKF 姿态 ---------- */
typedef struct {
    uint8_t Initialized;
    KalmanFilter_t IMU_QuaternionEKF;
    uint8_t ConvergeFlag;
    uint8_t StableFlag;
    uint64_t ErrorCount;
    uint64_t UpdateCount;
    float q[4];
    float GyroBias[3];
    float Gyro[3];
    float Accel[3];
    float OrientationCosine[3];
    float accLPFcoef;
    float gyro_norm;
    float accl_norm;
    float AdaptiveGainScale;
    float Roll;
    float Pitch;
    float Yaw;
    float YawTotalAngle;
    float Q1;
    float Q2;
    float R;
    float dt;
    mat ChiSquare;
    float ChiSquare_Data[1];
    float ChiSquareTestThreshold;
    float lambda;
    float YawRoundCount;
    float YawAngleLast;
} QEKF_INS_t;

/* ---------- Mahony 滤波 ---------- */
struct MAHONY_FILTER_t {
    float Kp, Ki;
    float alpha;
    Axis3f acc_lpf;
    float dt;
    Axis3f gyro, acc;
    Axis3f gyro_bias;
    float acc_norm;
    float exInt, eyInt, ezInt;
    float q0, q1, q2, q3;
    float rMat[3][3];
    float pitch, roll, yaw;
    float last_yaw, YawTotalAngle;
};

/* ---------- 滑模控制 ---------- */
typedef struct {
    float C;
    float K;
    float ref;
    float error_eps;
    float u_max;
    float J;
    float epsilon;
    float angle;
    float ang_vel;
    float u;
    float error;
    float error_last;
    float dref;
    float ddref;
    float refl;
    float s;
} SMC;

/* ============================================================
 * 应用层结构体
 * ============================================================ */

/* ---------- 麦轮底盘 ---------- */
typedef struct {
    float Wheel_Perimeter;
    float Wheel_Track;
    float Wheel_Base;
    float Rotate_x_offset;
    float Rotate_y_offset;
    float Deceleration_ratio;
    int Max_vx_speed;
    int Max_vy_speed;
    int Max_vr_speed;
    int Max_wheel_ramp;
    float raid_fr;
    float raid_fl;
    float raid_bl;
    float raid_br;
    float Wheel_rpm_ratio;
    float MecanumOut[4];
    uint8_t Spin_Flag;
    float Spin_Speed;
} Mecanum_typdef;

/* ---------- 均值滤波 ---------- */
typedef struct {
    float history[100];
    float sum;
    int count;
    int index;
    float speed;
} member;

/* ---------- 均值滤波聚合 ---------- */
typedef struct {
    member rxs;
    member rys;
    member ros;
    member rxs1;
    member rys1;
    member ros1;
    member rx_2;
    member ry_2;
    member ro_2;
    member rx_2_;
    member ry_2_;
    member ro_2_;
    member ds1_;
    member ds2_;
    member ds3_;
    member ds4_;
    member DirAngle1_;
    member DirAngle2_;
    member DirAngle3_;
    member DirAngle4_;
    member DirAngle1_1;
    member DirAngle2_1;
    member DirAngle3_1;
    member DirAngle4_1;
} Average;

/* ---------- 所有电机聚合 ---------- */
typedef struct {
    DJI_MOTOR_Typedef DJI_6020_Pitch;
    DJI_MOTOR_Typedef DJI_6020_Yaw;
    DJI_MOTOR_Typedef DJI_3508_Shoot_L;
    DJI_MOTOR_Typedef DJI_3508_Shoot_R;
    DJI_MOTOR_Typedef DJI_3508_Shoot_M;
    DJI_MOTOR_Typedef DJI_3508_Chassis_1;
    DJI_MOTOR_Typedef DJI_3508_Chassis_2;
    DJI_MOTOR_Typedef DJI_3508_Chassis_3;
    DJI_MOTOR_Typedef DJI_3508_Chassis_4;
    DM_MOTOR_Typdef m_dm4310_y_t;
    DM_MOTOR_Typdef m_dm4310_p_t;
} MOTOR_Typedef;

/* ---------- 在线状态 ---------- */
typedef struct {
    uint8_t RM_DBUS;
    uint8_t RM_MOD;
    uint8_t MOTOR_HEAD_Pitch;
    uint8_t MOTOR_HEAD_Yaw;
    uint8_t MOTOR_Shoot_L;
    uint8_t MOTOR_Shoot_R;
    uint8_t MOTOR_Shoot_M;
    uint8_t MOTOR_Chassis_1;
    uint8_t MOTOR_Chassis_2;
    uint8_t MOTOR_Chassis_3;
    uint8_t MOTOR_Chassis_4;
    uint8_t Power;
    uint8_t MASTER_LOCATION;
} RUI_ROOT_STATUS_Typedef;

/* ---------- 总控制参数 ---------- */
typedef struct {
    struct {
        float VX;
        float VY;
        float VW;
        float wheel1;
        float wheel2;
        float wheel3;
        float wheel4;
        uint8_t CAP;
    } BOTTOM;

    struct {
        float Pitch;
        float Pitch_MAX;
        float Pitch_MIN;
        float Yaw;
    } HEAD;

    struct {
        float SHOOT_L;
        float SHOOT_R;
        float SHOOT_M;
        float Shoot_Speed;
        int64_t Single_Angle;
    } SHOOT;

    struct {
        int16_t YAW_INIT_ANGLE;
        int16_t YAW_ANGLE;
        int16_t RELATIVE_ANGLE;
        int16_t YAW_SPEED;
        float TOP_ANGLE;
    } CG;

    struct {
        float Speed_err_L;
        float Speed_err_R;
        int32_t Angle;
        float Speed_Aim_L;
        float Speed_Aim_R;
        uint8_t JAM_Flag;
        uint32_t Shoot_Number;
        uint32_t Shoot_Number_Last;
    } SHOOT_Bask;

    struct {
        float Chassis_dt;
        float Gimbal_dt;
        float Monitor_dt;
        float Shoot_dt;
        float Gimbal_time;
        uint32_t Chassis_Count;
        uint32_t Gimbal_Count;
        uint32_t Monitor_Count;
        uint32_t Shoot_Count;
    } DWT_TIMEEE;

    uint8_t MOD[2];
    uint8_t ORE;
} CONTAL_Typedef;

/* ---------- CANSPI 消息 ---------- */
typedef union {
    struct __attribute__((packed)) {
        uint8_t idType;
        uint32_t id;
        uint8_t dlc;
        uint8_t data0;
        uint8_t data1;
        uint8_t data2;
        uint8_t data3;
        uint8_t data4;
        uint8_t data5;
        uint8_t data6;
        uint8_t data7;
    } frame;
    uint8_t array[14];
} uCAN_MSG;

/* ============================================================
 * 类型别名
 * ============================================================ */
typedef CAN_HandleTypeDef hcan_t;

/* ============================================================
 * EXTERN 全局变量声明
 *
 * 使用方法：
 *   #include "MY_Define.h"               → 生成 extern 声明
 *   #define GLOBAL_VAR_IMPL
 *   #include "MY_Define.h"               → 生成实际定义
 * ============================================================ */

/* ---------- 由 GLOBAL_VAR_TABLE 自动生成的 extern ---------- */
#ifndef GLOBAL_VAR_IMPL
#define X(type, name) extern type name;
GLOBAL_VAR_TABLE
#undef X
#endif

/* ---------- 数组和特殊变量（手动声明） ---------- */
extern uint8_t DBUS_RX_DATA[18];
extern uint8_t VT13_RX_DATA[21];
extern uint8_t VisionRx[30];
extern uint8_t sd_v_buff[24];
extern uint8_t RX[20];
extern uint8_t Referee_Rx_Buf[2][REFEREE_RXFRAME_LENGTH];
extern Mecanum_typdef MecanumData;

/* ---------- 模块级全局变量（在各 .c 中定义，此处仅 extern） ---------- */
extern uint8_t GlobalDebugMode;
extern int16_t cur_int16;
extern QEKF_INS_t QEKF_INS;
extern float chiSquare;
extern float ChiSquareTestThreshold;
extern struct MAHONY_FILTER_t mahony_filter;
extern DWT_Time_t SysTime;
extern IMU_CTRL_STATE_e imu_ctrl_state;
extern IMU_CTRL_FLAG_t imu_ctrl_flag;
extern float yaw, pitch, roll;
extern TYPEDEF_TOP TOP;
extern float currentAngle;
extern uint64_t Self_color;
extern uint8_t v_state;
extern uCAN_MSG rxMessage1;
extern uCAN_MSG rxMessage2;
extern uCAN_MSG txMessage;
extern uint8_t anonymity_au8[70];

/* ---------- 以下类型定义散落在 BSP 驱动中，在当前文件仅为前向声明 ---------- */
extern struct CanCommunit_typedef CanCommunit_t;
extern struct gimbal_typedef gimbal_t;

/* ============================================================
 * BSP/App 头文件（放在末尾：所有类型已定义，BSP 头文件可见）
 * 你写的新函数头文件加在这里，全工程可见。
 * ============================================================ */
#include  "controller.h"
#include  "DJI_Motor.h"
#include "RUI_MATH.h"
#include  "Chassis_Task.h"
#include "Robot.h"
#include "All_Init.h"
#include  "can_bsp.h"
#include  "IMU_Task.h"
#include  "bsp_dwt.h"
#include "BMI088driver.h"
#include  "mahony_filter.h"
#include  "QuaternionEKF.h"
#include "pid_temp.h"
#include "VT13.h"
#include "Referee.h"
#include "usart.h"
#include "can.h"
#include "Gimbal_Task.h"
#include "DBUS.h"
#include "Board_to_Board.h"

#endif /* __MY_DEFINE */
