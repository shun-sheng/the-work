//
// Created by lenovo on 2026/6/29.
//
#include "Board_to_Board.h"

board_Data_t boardTxData = {0};

void Board_to_Board_Receive(board_Data_t *receive_data,uint16_t stdid,uint8_t *rx_data)
{

    switch (stdid)
    {
        case 0x227:
            receive_data->Receive_Data.DBUS.Remote.S2=rx_data[0];
            receive_data->Receive_Data.DBUS.Remote.S1=rx_data[1];
            memcpy(&receive_data->Receive_Data.Gimabal_Yaw_degree,rx_data+2,4);
            break;
        case 0x226:
            memcpy(&receive_data->Receive_Data.DBUS.Remote.CH0, rx_data, 2);
            memcpy(&receive_data->Receive_Data.DBUS.Remote.CH1, rx_data + 2, 2);
            memcpy(&receive_data->Receive_Data.Chassis_Vw, rx_data + 4, 4);
            break;
        case 0x228:
            memcpy(&receive_data->Receive_Data.IMU_Data.gyro[0],rx_data,4);
            memcpy(&receive_data->Receive_Data.IMU_Data.gyro[1],rx_data+4,4);
            break;
        case 0x225:
            memcpy(&receive_data->Receive_Data.IMU_Data.gyro[2],rx_data,4);
            memcpy(&receive_data->Receive_Data.Gimbal_Yaw_rad,rx_data+4,4);
            break;

        default:
            break;
    }

}

void Board_to_Board_Send(DBUS_Typedef *DBUS,board_Data_t *send_data,IMU_Data_t IMU,float vw,float Yaw_rad,float Yaw_degree)
{
    uint16_t ch0=(uint16_t)DBUS->Remote.CH0;
    uint16_t ch1=(uint16_t)DBUS->Remote.CH1;
    uint16_t s1=(uint16_t)DBUS->Remote.S1;
    uint16_t s2=(uint16_t)DBUS->Remote.S2;

    send_data->Send_Data.remote_ch[0]=ch0&0xff;
    send_data->Send_Data.remote_ch[1]=(ch0>>8)&0xff;
    send_data->Send_Data.remote_ch[2]=ch1&0xff;
    send_data->Send_Data.remote_ch[3]=(ch1>>8)&0xff;
    memcpy(send_data->Send_Data.remote_ch+4,&vw,4);

    memcpy(send_data->Send_Data.Y_w,&IMU.gyro[0],4);
    memcpy(send_data->Send_Data.Y_w+4,&IMU.gyro[1],4);

    memcpy(send_data->Send_Data.Z_w,&IMU.gyro[2],4);
    memcpy(send_data->Send_Data.Z_w+4,&Yaw_rad,4);

    send_data->Send_Data.remote_s[0]=s1&0xff;
    send_data->Send_Data.remote_s[1]=(s1>>8)&0xff;
    memcpy(send_data->Send_Data.remote_s+2,&Yaw_degree,4);

    canx_send_data(&hcan1,0x226,send_data->Send_Data.remote_ch);
    canx_send_data(&hcan1,0x227,send_data->Send_Data.remote_s);
    canx_send_data(&hcan1,0x228,send_data->Send_Data.Y_w);
    canx_send_data(&hcan1,0x225,send_data->Send_Data.Z_w);

}