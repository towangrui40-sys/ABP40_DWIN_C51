//############################################################
// FILE:  Task_manager.c
// Created on: 2022��2��20��
// Author: Jason
// summary: Task_manager
//############################################################
#include "main.h"


#define Task_Num   4   //task +1
#define HFPeriod_COUNT     1   	//1ms
#define RTUPeriod_COUNT    50    //50ms
#define FSMPeriod_COUNT    10  	//5ms
#define TIMERPeriod_COUNT  250   //250ms

TaskTime xdata TasksPare[Task_Num];
extern code const Product_TypeDef product_data[PRODUCT_TOTAL];
void Timer_Task_Count(void)
{
	u8 data Task_Count=0;
 for(Task_Count=0;Task_Count<Task_Num;Task_Count++)    //TASK_NUM=5
 {
  if((TasksPare[Task_Count].Task_Count<TasksPare[Task_Count].Task_Period)&&(TasksPare[Task_Count].Task_Period>0))
  {
	  TasksPare[Task_Count].Task_Count++; 
  }
 }
}

void Execute_Task_List_RUN(void)
{
	u8 data	Task_Count = 0;
 for(Task_Count=0;Task_Count < Task_Num;Task_Count++)
 {
  if((TasksPare[Task_Count].Task_Count>=TasksPare[Task_Count].Task_Period)&&(TasksPare[Task_Count].Task_Period > 0))
  {
		TasksPare[Task_Count].Task_Function();
	  TasksPare[Task_Count].Task_Count=0;
  }
 }
}
#define SPK_TIME_OUT_TIMES 5
void Task_Timer_Sec(void)  //  250ms
{
	static u16 xdata tick = 0;  //1s
	if((win_str_data.state == FSM_RUN) || (win_str_data.state == FSM_END))
	{
		tick++;
		if(tick >= 4)    // 250ms each tick, 4 ticks = 1s
		{
			tick = 0;
			switch(win_str_data.state)
			{
				case FSM_RUN: /**********FSM_RUN***********/
					win_str_data.used_time++;  //运行时间增加
					win_str_data.disp_hold_time_countdown--;
					win_str_data.load_bar_tick++;
					win_str_data.press_load_bar_num = (win_str_data.load_bar * win_str_data.load_bar_tick)/100;
					sys_write_vp(ICON_TABLETTING_LOAD_BAR_ADDR,(u8 *)&win_str_data.press_load_bar_num,1);
					break;

				case FSM_END: //ȡƬ
					win_str_data.pressure_relief_time_minus++;
					win_str_data.press_load_bar_num = (win_str_data.load_bar * win_str_data.pressure_relief_time_minus)/100;
					sys_write_vp(ICON_UP_LOAD_BAR_ADDR,(u8 *)&win_str_data.press_load_bar_num,1);
					sys_write_vp(ARTNUM_RETURN_TIME_TICK_ADDR,(u8 *)&win_str_data.pressure_relief_time_minus,2);
					if(win_str_data.speaker_delay >= 0) win_str_data.speaker_delay --;
					if(win_str_data.speaker_delay == 1)
					{
						RTU_Cmd_Pending(RTU_DC3_STOP,OFF);	//��������
					}
					break;

				default:
					break;
			}
		}
	}
	
	if(win_str_data.sys_delay > 0) win_str_data.sys_delay--;
}
void RTU_send_Rece(void)  // 100ms�������ڣ��������޸����ڣ����1ms
{
	RTU_Send_Task_Handler();
}

/*********************状态机******************************/
void Run_FSM(void)   //FSM状态机 
{
	static u16 xdata temp = 0;  //1s计时
	switch(win_str_data.state)
	{
		case FSM_INIT:    //***************状态机：状态机初始化
			win_str_data.state = FSM_READY;
			RTU_Cmd_Pending(RTU_DC2_ON,ON);	//  上升电磁阀开
			RTU_Cmd_Pending(RTU_AC1_ON,ON);	//  灯
			win_str_data.sys_delay = 4*25;  //25s系统延时，默认开机液压缸回升
			break;
		case FSM_READY:
				win_str_data.disp_step = 1;
				win_str_data.disp_pressure = win_str_data.use_pressure;
				win_str_data.disp_hold_time = win_str_data.use_hold_time;
				win_str_data.disp_hold_time_countdown = win_str_data.use_hold_time;
		
				if(win_str_data.start == 1)    //接收到Start_win  start=1开始信号
				{
					if(str_sys.motor_sensor1 == 1)    //关到位
					{
						win_str_data.state = FSM_CLOSE;
					}
					else
					{
						RTU_Cmd_Pending(RTU_MOTOR_FLAG,1);	//  关闭
						win_str_data.state = FSM_CLOSE;
					}

				}
				if(win_str_data.sys_delay == 1)
				{
					RTU_Cmd_Pending(RTU_DC2_OFF,OFF);	//  上升电磁阀关
				}
			break;
		case FSM_CLOSE:
			if(str_sys.motor_sensor1 == 1)    //关到位
			{
				win_str_data.state = FSM_START;
			}
			break;

		case FSM_START:/*******************************************状态机：开始状态********************************/
				RTU_Cmd_Pending(RTU_DC2_OFF,OFF);	//  上升电磁阀关
				RTU_Cmd_Pending(RTU_DC1_ON,ON);	//  UP 液压机下压  第一个继电器
				RTU_Cmd_Pending(RTU_AC_EX_ON,ON);	//  UP 液压机下压  第一个继电器
				win_str_data.state = FSM_PUSH;   //切换到运行状态 update fsm
			break;

		case FSM_PUSH:/*******************************************状态机：开始状态********************************/
				if(win_str_data.real_pressure >= (win_str_data.use_pressure))
				{
					RTU_Cmd_Pending(RTU_AC_EX_OFF,OFF);	//  UP 液压机下压  第一个继电器
					win_str_data.load_bar_num = win_str_data.prog_step1_hold_time + win_str_data.prog_step2_hold_time + win_str_data.prog_step3_hold_time;
					win_str_data.load_bar = 10000/win_str_data.load_bar_num;
					win_str_data.state = FSM_RUN;   //切换到运行状态 update fsm
				}
				if(win_str_data.start == 0) //start = 0停止信号 start = 1 运行信号
				{
					win_change_page(TABLETING_DONE_PAGE);  //压片完成弹窗
					win_str_data.state = FSM_STOP;
				}
				break;

		case FSM_RUN:
			if(win_str_data.disp_step == 1)
			{
				if(win_str_data.disp_hold_time_countdown == 0)
				{
					memcpy((u8 *)&win_str_data.use_pressure,(u8 *)&win_str_data.prog_step2_pressure,4);  //运行值=设置值
					
					win_str_data.disp_step = 2;
					win_str_data.disp_pressure = win_str_data.use_pressure;
					win_str_data.disp_hold_time = win_str_data.use_hold_time;
					win_str_data.disp_hold_time_countdown = win_str_data.use_hold_time;
					win_str_data.state = FSM_START;
				}
			}
			if(win_str_data.disp_step == 2)
			{
				if(win_str_data.disp_hold_time_countdown == 0)
				{
					memcpy((u8 *)&win_str_data.use_pressure,(u8 *)&win_str_data.prog_step3_pressure,4);  //运行值=设置值
					
					win_str_data.disp_step = 3;
					win_str_data.disp_pressure = win_str_data.use_pressure;
					win_str_data.disp_hold_time = win_str_data.use_hold_time;
					win_str_data.disp_hold_time_countdown = win_str_data.use_hold_time;
					win_str_data.state = FSM_START;
				}
			}
			
			if(win_str_data.disp_step == 3)
			{
				if(win_str_data.disp_hold_time_countdown == 0)
				{
					win_str_data.start = 0;
					if(win_str_data.alarm == 0)
					{
						win_str_data.speaker_delay = 3;
						RTU_Cmd_Pending(RTU_DC3_ON,ON);	//蜂鸣器开
					}
				}
			}

			if(win_str_data.start == 0) //start = 0停止信号 start = 1 运行信号
			{
				win_change_page(TABLETING_DONE_PAGE);  //压片完成弹窗
				win_str_data.state = FSM_STOP;
			}
			if(win_str_data.use_pressure <= 3)
			{
				if(win_str_data.real_pressure < (win_str_data.use_pressure))
				{
					win_str_data.state = FSM_START;
				}
			}
			else
			{
				if(win_str_data.real_pressure < (win_str_data.use_pressure - 2))
				{
					win_str_data.state = FSM_START;
				}
			}
			break;

		case FSM_STOP:
			
				win_str_data.sampling_time_tick = 0;
				win_str_data.press_load_bar_num = 0;
				sys_write_vp(ICON_PICK_UP_LOAD_BAR_ADDR,(u8 *)&win_str_data.sampling_time_tick,1);
				win_str_data.out_start = 0;
		
				win_str_data.load_bar_tick = 0; // 进度条
	    		win_str_data.press_load_bar_num = 0;
		
				sys_write_vp(ICON_TABLETTING_LOAD_BAR_ADDR,(u8 *)&win_str_data.press_load_bar_num,1);
				memcpy((u8 *)&win_str_data.use_pressure,(u8 *)&win_str_data.prog_step1_pressure,4);  //运行值=设置值

				RTU_Cmd_Pending(RTU_DC1_OFF,OFF);	//  液压机液压油泵
				RTU_Cmd_Pending(RTU_AC_EX_OFF,OFF);// 下压电磁阀
				RTU_Cmd_Pending(RTU_DC2_ON,ON);	//  上升电磁阀开		
		
				win_str_data.pressure_relief_time_minus = 0;
		
				win_str_data.load_bar = 10000/win_str_data.pressure_relief_time;

				win_str_data.used_time_l = win_str_data.used_time & 0xffff;  //Save used time
				win_str_data.used_time_h = (win_str_data.used_time>>16) & 0xffff; 
				norflash_write(RUNTIME_MIN_HADDR,(u8*)&win_str_data.used_time_h,2);
			
				win_str_data.state = FSM_END;
			break;		
				
		case FSM_END:
			  if(win_str_data.pressure_relief_time_minus >= win_str_data.pressure_relief_time)
				{
					RTU_Cmd_Pending(RTU_DC2_OFF,OFF);	//  上升电磁阀开		
					RTU_Cmd_Pending(RTU_MOTOR_FLAG,2);	//  关闭
					win_str_data.state = FSM_OPEN;
					if(temp == 0xff) win_change_page(WORK_PAGE);
				}
				else
				{
					if(win_str_data.start == 1 || (win_str_data.out_start == 1))    //接收到Start_win  start=1开始信号
					{
						win_change_page(CYLINDER_RETURNING_PAGE);
						win_str_data.start = 0;
						win_str_data.out_start = 0;
						temp = 0xff;
					}
				}
	  	break;


		case FSM_OPEN:
			if(str_sys.motor_sensor2 == 1)    //开到位
			{
				win_str_data.state = FSM_READY;
			}
			if(win_str_data.start == 1 || (win_str_data.out_start == 1))    //接收到Start_win  start=1开始信号
			{
				win_str_data.start = 0;
				win_str_data.out_start = 0;
				temp = 0xff;
			}
		default:
			break;
	}
}
void HFPeriod_1msTask(void)
{
	win_str_data.real_pressure = ((str_sys.adc_per-350)/5);   //����ѹ��ֵ bar
	if((int)win_str_data.real_pressure <= 0) win_str_data.real_pressure = 0;
	
	if(win_str_data.real_pressure > win_str_data.use_pressure) 
		win_str_data.disp_real_pressure = win_str_data.use_pressure;
	else
		win_str_data.disp_real_pressure = win_str_data.real_pressure;
		
	sys_write_vp(ARTNUM_MAIN_REAL_PRESSURE_ADDR,(u8 *)&win_str_data.disp_real_pressure,1);

		
	btn_click_handler();//��ť����¼�����	
	rtu_response_handler();
	win_fresh_window();     //ˢ�½���
}


void Task_Manage_List_Init(void)
{
	TasksPare[0].Task_Period=HFPeriod_COUNT; //PERIOD_COUNT=1    1ms
	TasksPare[0].Task_Count=1;
	TasksPare[0].Task_Function=HFPeriod_1msTask;  

	TasksPare[1].Task_Period=RTUPeriod_COUNT; //2ms
	TasksPare[1].Task_Count=8;
	TasksPare[1].Task_Function=RTU_send_Rece; //  ͨѶ���պͷ���;

	TasksPare[2].Task_Period=FSMPeriod_COUNT; //100ms
	TasksPare[2].Task_Count=80;
	TasksPare[2].Task_Function=Run_FSM;//  ͨѶ���պͷ���;

	TasksPare[3].Task_Period = TIMERPeriod_COUNT;//500ms
	TasksPare[3].Task_Count=300;
	TasksPare[3].Task_Function = Task_Timer_Sec;   // 500ms��LED����˸
}


// USER CODE END

