/**
 * @file VT13.h
 * @brief RoboMaster 裁判系统相机图传模块 VT13 协议解析头文件
 * @version 1.0
 * @date 2026-03-21
 * @author CaoKangqi
 * * @copyright Copyright (c) 2026
 */

#ifndef G4_FRAMEWORK_VT13_H
#define G4_FRAMEWORK_VT13_H


#include "MY_Define.h"

/**
 * @brief 解析入口函数
 * @param Data 21字节原始数据输入缓冲区指针
 * @param VT13 解析结果目标结构体指针
 */
void VT13_Resolved(uint8_t* Data, VT13_Typedef* VT13);


#endif //G4_FRAMEWORK_VT13_H