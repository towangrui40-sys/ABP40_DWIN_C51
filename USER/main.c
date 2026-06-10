#include "main.h"
#include "string.h"



/**************************************************
void btn_click_callback(u16 addr,u16 val)
**************************************************/
SysDataDef xdata str_sys;

void Init_Rtu_RegHoldingBuf(SysDataDef* dat)
{
	memset(&str_sys,0,sizeof(str_sys));

	usRegHoldingBuf[ADDR_DOOR].dat = (u16 *)&dat->door;
	usRegHoldingBuf[ADDR_LOCK].dat = (u16 *)&dat->lock;

	usRegHoldingBuf[ADDR_SET_DC1].dat = (u16 *)&dat->set_dc1;
	usRegHoldingBuf[ADDR_SET_DC2].dat = (u16 *)&dat->set_dc2;
	usRegHoldingBuf[ADDR_SET_DC3].dat = (u16 *)&dat->set_dc3;
	
	usRegHoldingBuf[ADDR_SET_AC1].dat = (u16 *)&dat->set_ac1;
	usRegHoldingBuf[ADDR_SET_AC2].dat = (u16 *)&dat->set_ac2;
	usRegHoldingBuf[ADDR_SET_AC3].dat = (u16 *)&dat->set_ac3;

	usRegHoldingBuf[ADDR_SET_AC_RELAY].dat = (u16 *)&dat->set_acex;
	usRegHoldingBuf[ADDR_GET_ADC_PER].dat = (u16 *)&dat->adc_per;

	usRegHoldingBuf[ADDR_MOTOR_STATE].dat = (u16 *)&dat->motor_state;
	usRegHoldingBuf[ADDR_MOTOR_SENSOR1].dat = (u16 *)&dat->motor_sensor1;
	usRegHoldingBuf[ADDR_MOTOR_SENSOR2].dat = (u16 *)&dat->motor_sensor2;
	usRegHoldingBuf[ADDR_MOTOR_FLAG].dat = (u16 *)&dat->motor_flag;
}

void main(void)
{
	sys_init();
	Init_Rtu_RegHoldingBuf(&str_sys);
	rtu_data_init();
	win_init();
	btn_init();
	T5L_HMIslvInit(); 
	EA=1;
	Task_Manage_List_Init( );
	while(1)
	{
							
		Execute_Task_List_RUN();
		T5L_HMIslvSub();
	}

}


