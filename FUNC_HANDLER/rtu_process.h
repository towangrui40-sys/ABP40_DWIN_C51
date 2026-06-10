#ifndef __RTU_PROCESS_H_
#define __RTU_PROCESS_H_


//TRU CMD    //RTU״̬
typedef enum
{
	RTU_IDlE = 0,

	RTU_DC1_ON,
	RTU_DC1_OFF,
	RTU_DC2_ON,
	RTU_DC2_OFF,
	RTU_DC3_ON,
	RTU_DC3_STOP,
	
	RTU_AC1_ON,
	RTU_AC2_ON,
	RTU_AC_EX_ON,
	RTU_AC_EX_OFF,
//AC	
	RTU_ACFAN_RUN,
	RTU_ACFAN_STOP,

	RTU_MOTOR_FLAG,
}RTU_StateType;

void RTU_Send_Task_Handler(void);

void RTU_Cmd_Pending(u8 cmd,u16 dat);
#endif
