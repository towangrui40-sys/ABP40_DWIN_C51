//############################################################
// FILE:  Task_manager_H
// Created on: 2019��7��8��
// Author: XY
// summary: Header file  and definition
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//STM32F4������ƿ�����
//˶�������  
//��ַ: https://shuolidianzi.taobao.com
//Author-QQ: 616264123
//�������QQȺ��314306105
//############################################################


#ifndef _Task_manager_H_
#define _Task_manager_H_
#include "sys.h"

#define ON		1
#define OFF		0

typedef  void ( * FTimer_P) ( void );

typedef struct {
	    u16	 Task_Period;  			//time out for calling function
	    u16  Task_Count;
	    FTimer_P Task_Function;		//Send function defines in application
	   }TaskTime;

void Timer_Task_Count(void);
void Execute_Task_List_RUN(void);
void Task_Manage_List_Init(void);
void Task_LED(void);
void HFPeriod_2msTask(void);
void Pack_TestPare(void);
void task_send_Rece(void);
void LCD12864KEY_RUN(void);
u16 Boost_service_prog(void);
void win_fresh_roller(u16 roller);
#endif  //Task_manager_H
