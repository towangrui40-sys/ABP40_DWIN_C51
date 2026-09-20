#ifndef __START_WIN_H__
#define __START_WIN_H__
#include "sys.h"

#define PRODUCT_TOTAL 1      //��������
/*---------------------define arae-------------------------*/
/********************************************************


**********************LOGO*****************************/
#define ANIMOTION_LOGO_ADDR		    0x2100  
//WORK PAGE VAR
/*******************MAIN_PAGE*************************/
#define ARTNUM_MAIN_REAL_PRESSURE_ADDR   				0x2000
#define ARTNUM_MAIN_HOLD_TIME_ADDR   		 		    0x2001

#define ARTNUM_MAIN_TABLETTING_STEP_ADDR	            0X2002
#define ARTNUM_MAIN_SET_PRESSURE_ADDR 					0x2003
#define ARTNUM_MAIN_SET_HOLD_TIME_ADDR					0X2004

#define ARTNUM_MAIN_PROG_NUM_ADDR				    	0x200A
 
/*******************SET_PAGE**************************/  
//0x2020~0x203F
#define ARTNUM_SET_STEP1_PRESSURE_ADDR 				0x2020
#define ARTNUM_SET_STEP1_HOLD_TIME_ADDR			    0X2021

#define ARTNUM_SET_STEP2_PRESSURE_ADDR 				0x2022
#define ARTNUM_SET_STEP2_HOLD_TIME_ADDR			    0X2023

#define ARTNUM_SET_STEP3_PRESSURE_ADDR 				0x2024
#define ARTNUM_SET_STEP3_HOLD_TIME_ADDR			   	0X2025


/******************PROGRAM_PAGE**************************/
//0x2040~0x205F
#define ARTNUM_PROG_STEP1_PRESSURE_ADDR 			0x2040
#define ARTNUM_PROG_STEP1_HOLD_TIME_ADDR			0X2041

#define ARTNUM_PROG_STEP2_PRESSURE_ADDR 			0x2042
#define ARTNUM_PROG_STEP2_HOLD_TIME_ADDR		    0X2043

#define ARTNUM_PROG_STEP3_PRESSURE_ADDR 			0x2044
#define ARTNUM_PROG_STEP3_HOLD_TIME_ADDR			0X2045


#define ARTNUM_PROG_NUM_ADDR	              		0X204E  //����

/******************��̨���������ʾ**********************/
//0x2050~0x205F
#define ARTNUM_BACKEND_PRESSURE_RELIEF_TIME_ADDR 	0x2050  //
#define ARTNUM_BACKEND_SAMPLING_TIME_ADDR		    0X2051  //

#define ARTNUM_BACKEND_MOLD_PRESSING1_ADDR 			0x2052  //
#define ARTNUM_BACKEND_MOLD_PRESSING2_ADDR			0X2053  //

#define ARTNUM_SAMPLING_TIME_TICK_ADDR		        0X2058  //
#define ARTNUM_RETURN_TIME_TICK_ADDR		        0X205A  //
/*******************************************************/



#define ARTNUM_PASSCODE_ADDR		      0x2060
#define ARTNUM_INPUTNUM_ADDR		      0x2061
#define ARTNUM_UT_ADDR					  0x2062 

//����ͼ��
#define ICON_START_ADDR 	              0x2501
#define ICON_TABLETTING_LOAD_BAR_ADDR 	  0x2502
#define ICON_PICK_UP_LOAD_BAR_ADDR    	  0x2503
#define ICON_UP_LOAD_BAR_ADDR    	      0x2504


#define ICON_INPUT1_ADDR    	      0x2505
#define ICON_INPUT2_ADDR    	      0x2506
#define ICON_INPUT3_ADDR    	      0x2507
#define ICON_INPUT4_ADDR    	      0x2508
#define ICON_INPUT5_ADDR    	      0x2509
#define ICON_INPUT6_ADDR    	      0x250A

#define ICON_INPUT1_WORD_ADDR    	      0x250B
#define ICON_INPUT2_WORD_ADDR    	      0x250C
#define ICON_INPUT3_WORD_ADDR    	      0x250D
#define ICON_INPUT4_WORD_ADDR    	      0x250E
#define ICON_INPUT5_WORD_ADDR    	      0x250F
#define ICON_INPUT6_WORD_ADDR    	      0x2510

#define ICON_DOOR_WARRING_ADDR            0x2530

//string
#define STRING_PRODUCT_ADDR 0x3000
#define STRING_VERSION_ADDR 0x3100


#define PROG_STEP1_PRESSURE         0
#define PROG_STEP1_HOLD_TIME     	1
#define PROG_STEP2_PRESSURE			2
#define PROG_STEP2_HOLD_TIME		3
#define PROG_STEP3_PRESSURE			4
#define PROG_STEP3_HOLD_TIME		5

//nor flash address list,the address lentgh is 2 bytes 


#define SYS_LOGO_OFFSET				0X00
#define SYS_LANGUAGE_OFFSET			0X01
#define SYS_LIGHT_OFFSET			0X02
#define SYS_BUZZ_OFFSET				0X03
#define SYS_PRUDUCT_OFFSET			0X04
#define SYS_LAST_PROG_OFFSET		0X05
#define RUNTIME_MIN_HADDR 	        0X06
#define RUNTIME_MIN_LADDR 			0X07


#define FACTORY_PARAMS_INIT_VALUE       0xA5A5  // 2-byte magic: 0xA5A5 = initialized (1/65536 probability)

#define PRE_RELIEF_TIME_ADDR		0X0A
#define SAMPLING_TIME_ADDR			0X0B
#define MOLD_PRESSING1_ADDR			0X0C
#define MOLD_PRESSING2_ADDR			0X0D
#define FACTORY_PARAMS_INIT_FLAG_ADDR  0X0E  // 2-byte magic number for initialization

#define PROG1_BASE_NORADDR		0x10
#define PROG2_BASE_NORADDR		0x20
#define PROG3_BASE_NORADDR		0x30
#define PROG4_BASE_NORADDR		0x40
#define PROG5_BASE_NORADDR		0x50
#define PROG6_BASE_NORADDR		0x60
#define PROG7_BASE_NORADDR		0x70
#define PROG8_BASE_NORADDR		0x80
#define PROG9_BASE_NORADDR		0x90
#define PROG10_BASE_NORADDR		0xA0
#define PROG11_BASE_NORADDR		0xB0
#define PROG12_BASE_NORADDR		0xC0
#define PROG13_BASE_NORADDR		0xD0
#define PROG14_BASE_NORADDR		0xE0
#define PROG15_BASE_NORADDR		0xF0
#define PROG16_BASE_NORADDR		0x110
#define PROG17_BASE_NORADDR		0x120
#define PROG18_BASE_NORADDR		0x130
#define PROG19_BASE_NORADDR		0x140
#define PROG20_BASE_NORADDR		0x150


/*-------------------------------------------------------*/
typedef enum{
	MENU_PAGE = 0,
	FAC_PAGE,
	INFO_PAGE,
	INFO_NO_LOGO_PAGE,
	SYSTEM_PAGE,
	PASSCODE_PAGE,
	PASSCODE_CONFIRM_PAGE,
	MANUAL_PAGE,
	ALARM_PAGE,
	WORK_PAGE,
	PROGRAM_PAGE,
	PROGRAM_CONFIRM_PAGE,
	PICKING_TABLETS_PAGE,	    //取片界面
}Change_Page_Def;


typedef struct{
	u16 min;	//para min value
	u16 max;	//para max value
	u16 unit;	//para unit����
}PARA_RangeDef;

typedef struct{
	u16 model_id;
	char name[20];//product name
	PARA_RangeDef para1;//level
	PARA_RangeDef para2;//hold time
}Product_TypeDef;




typedef struct{

	//norflash
	u16 logo;     //0:on  1:off
	u16 language;
	u16 light;
	u16 alarm;    //0:on  1:off
	u16 product_id;
 	u16 prog_grp; //0:test mode,1-100 program mode
	u16 used_time_h;   //记秒数高位
	u16 used_time_l;   //记秒数低位
	u16 pressure_relief_time;  //
	u16 sampling_time;   			 //  
	u16 mold_pressing1; 			 //   40T
	u16 mold_pressing2;				 //   

	u32 used_time;     //记总时间 秒数
	u16 disp_time;     ///显示时间 总小时数

	u16 start;     	// 0:stop 1:run
	u16 out_start;  //ȡƬ 0:stop 1:run
	u16 paras_sel;  //current work parasmeters selected 
	u16 state;
	u16 sys_input_num;	
	
	u16 passcode; 
	u16 factory_sel;
	u16 real_pressure;        //��ʾʵʱѹ��
	u16 disp_real_pressure;        //��ʾʵʱѹ��
	u16 disp_hold_time_countdown;  //��ʾ����ѹ��ʱ�䵹��ʱ
	u16 disp_step;                 //��ʾѹƬ����
	u16 disp_pressure;
	u16 disp_hold_time;
	u16 use_pressure;
	u16 use_hold_time;
	
	u16 set_step1_pressure;
	u16 set_step1_hold_time;
	u16 set_step2_pressure;
	u16 set_step2_hold_time;
	u16 set_step3_pressure;
	u16 set_step3_hold_time;

	u16 prog_step1_pressure;
	u16 prog_step1_hold_time;
	u16 prog_step2_pressure;
	u16 prog_step2_hold_time;
	u16 prog_step3_pressure;
	u16 prog_step3_hold_time;

	u16 sampling_time_tick;
	u16 sampling_pressing;
	u16 press_load_bar_num;
	u16 load_bar_num;
	u16 load_bar;
	u16 load_bar_tick;
	/*-----------------------------------------*/
    u16 pressure_relief_time_minus;
	u16 door_warning;
	u16 speaker_delay;
    u16 sys_delay;

	u16 input_disp1;
	u16 input_disp2;
	u16 input_disp3;
	u16 input_disp4;
	u16 input_disp5;
	u16 input_disp6;
}STR_WIN_TypeDef;

//START_WIN�ṹ��
extern STR_WIN_TypeDef xdata win_str_data;

typedef enum
{
	MAIN_NUM=1,
	PROG_NUM1=2,
	PROG_NUM2=4,
	PROG_NUM3=8,
	SET_NUM1=16,
	SET_NUM2=32,
	SET_NUM3=64,
}Timer_CH_Def;

void win_disp_level(u16 ch,u16 val);
void win_disp_hold_time(u16 channel,u16 val);
void win_disp_step(u16 channel,u16 val);
void win_disp_count_time(u16 ch,u16 val);

void win_init(void);

void win_fresh_timer_block(void);
void win_fresh_window(void);
void Fresh_Service_Time(void);
void win_save_prog_paras(u16 offaddr,u8 *var_addr,u16 len);
void win_load_prog_paras(u16 offaddr,u8 *var_addr,u16 len);
void win_change_page(u16 page);
#endif

