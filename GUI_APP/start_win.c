#include <stdio.h>
#include <string.h>
#include "func_handler.h"
#include "nor_flash.h"


#include "start_win.h"
#include "motor_cmd.h"
#include "main.h"

u16 xdata tick_sec = 0;
code const char Software_version[11]={"V5.02"};
code const char modle_version[11]={"--------"};
Product_TypeDef product_data[PRODUCT_TOTAL]={	 

//id,product name,	level				 hold time	
{ 0,	"BP40",		   1,400,1,	  	  1,999,1,   },
};

STR_WIN_TypeDef xdata win_str_data;

//man page button handler API
static void win_main_btn_click_handler(u16 btn_val);
//work parameters settings page
static void win_prog_para_btn_hold_handler(u16 btn_val);
static void win_para_keypad_btn_click_handler(u16 btn_val);
static void win_factory_keypad_btn_click_handler(u16 btn_val);
static void win_pass_keypad_btn_click_handler(u16 btn_val);
static void win_prog_num_sel_btn_click_handler(u16 btn_val);
//background page button handler API
static void win_setpara_btn_click_handler(u16 val);
static void win_passcode_btn_click_handler(u16 val);
//factory page button handler api
static void win_fac_set_btn_click_handler(u16 btn_val);
//function
static void win_calc_function(void);

static void win_light_set_btn_hold_handler(u16 btn_val);
static void win_language_set_btn_hold_handler(u16 btn_val);
static void win_buzz_set_btn_hold_handler(u16 btn_val);
static void win_clear_input_icon(void);
void Fresh_Service_Time(void);
void btn_click_callback(u16 addr,u16 val)
{
	switch(addr)
	{
		case BTN_MAIN_PAGE_ADDR:				//Main page button   0x1100 
				win_main_btn_click_handler(val);
			break;
		case BTN_PARA_KEYPAD_ADDR:
				win_para_keypad_btn_click_handler(val);
			break;
		case BTN_PASS_KEYPAD_ADDR:
				win_pass_keypad_btn_click_handler(val);
			break;
		case BTN_PROG_NUM_SEL_ADDR:
				win_prog_num_sel_btn_click_handler(val);
			break;
		case BTN_FAC_SET_ADDR:
				win_fac_set_btn_click_handler(val);
			break;		
		case BTN_FAC_KEYPAD_ADDR:
				win_factory_keypad_btn_click_handler(val);
			break;			
		
		default:
			break;
	}
}

void btn_hold_res_callback(u16 addr,u16 val)
{
	switch(addr)
	{
		case BTN_PROG_MODE_SET_ADDR:
			win_prog_para_btn_hold_handler(val);
			break;
		case BTN_SET_LIGHT_ADDR:
			win_light_set_btn_hold_handler(val);		
			break;
		case BTN_LANGUAGE_ADDR:
			win_language_set_btn_hold_handler(val);
			break;
		case BTN_SET_BUZZ_ADDR:
			win_buzz_set_btn_hold_handler(val);
			break;
		default:
			break;
	}
}
void btn_hold_click_callback(u16 addr,u16 val)
{
	STR_WIN_TypeDef	*obj = &win_str_data;
	val =0;
	if(obj->start == 1) return;
	switch(addr)
	{		
		default:
			break;
	}
}
//???????????????????
void btn_hold_callback(u16 addr,u16 val)
{
	STR_WIN_TypeDef	*obj = &win_str_data;
	val =0;
	if(obj->start == 1) return;
	switch(addr)
	{
		default:
			break;
	}
}


u16 const page_reg[16]={						//???????
	{1},//MENU_PAGE
	{2},//FAC_PAGE
	{3},//INFO_PAGE
	{4},//INFO_NO_LOGO_PAGE
	{6},//SYSTEM_PAGE
	{7},//PASSCODE_PAGE
	{8},//PASSCODE_CONFIRM_PAGE
	{10},//WORK_PAGE
	{11},//WORK_CONFIRM_PAGE
	{12},//TABLETING_DONE_PAGE
	{13},//DOOR_OPEN_PAGE
	{15},//PROGRAM_PAGE
	{16},//PROGRAM_CONFIRM_PAGE
	{18},//PICKING_TABLETS_PAGE
	{20},//CYLINDER_RETURNING_PAGE
	{21},//INPUT_NUM_PAGE
};

void win_change_page(u16 page)    //?��????????
{
	u16 xdata temp;
	temp = page_reg[page];
	//fresh page
	switch(page)
	{
		case WORK_PAGE:

				sys_write_vp(ARTNUM_MAIN_PROG_NUM_ADDR,(u8*)&win_str_data.prog_grp,1);

			break;
		case WORK_CONFIRM_PAGE:
			break;
		case SYSTEM_PAGE:
			break;

		case PROGRAM_PAGE:
			win_disp_level(PROG_NUM1,win_str_data.prog_step1_pressure);
			win_disp_level(PROG_NUM2,win_str_data.prog_step2_pressure);
			win_disp_level(PROG_NUM3,win_str_data.prog_step3_pressure);
			win_disp_hold_time(PROG_NUM1,win_str_data.prog_step1_hold_time);
			win_disp_hold_time(PROG_NUM2,win_str_data.prog_step2_hold_time);
			win_disp_hold_time(PROG_NUM3,win_str_data.prog_step3_hold_time);
		
			win_disp_level(SET_NUM1,win_str_data.set_step1_pressure);
			win_disp_level(SET_NUM2,win_str_data.set_step2_pressure);
			win_disp_level(SET_NUM3,win_str_data.set_step3_pressure);
			win_disp_hold_time(SET_NUM1,win_str_data.set_step1_hold_time);
			win_disp_hold_time(SET_NUM2,win_str_data.set_step2_hold_time);
			win_disp_hold_time(SET_NUM3,win_str_data.set_step3_hold_time);

			break;
		default:break;
	}
	//goto page
	sys_disp_page(temp);
}


/*
* Function: win_clear_input_icon
* Description: Clears the input icons on the display by resetting the corresponding display data variables to zero
*/
static void win_clear_input_icon(void)
{
	memset(&win_str_data.input_disp1,0,sizeof(win_str_data.input_disp1) * 6);
	sys_write_vp(ICON_INPUT1_ADDR,(u8 *)&win_str_data.input_disp1,6);
	sys_write_vp(ICON_INPUT1_WORD_ADDR,(u8 *)&win_str_data.input_disp1,6);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////???????????//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//?????????ˮ????????
static void win_main_btn_click_handler(u16 btn_val)
{
	#define  BTN_VAL_START	     0X01    //start
	#define  BTN_VAL_PAUSE    	 0X02    //pause
	#define  BTN_VAL_STOP        0X03    //stop 

	#define  BTN_VAL_TEST        0X05 	 //test mode
	#define  BTN_VAL_MENU        0X06    //
	#define  BTN_VAL_SET         0X07    //settings into
	#define  BTN_VAL_CONFIRM     0X08    //Confirm startup
	#define  BTN_VAL_INFO        0X09
	#define  BTN_VAL_BACK_MAIN   0X0A    //settings background
	#define  BTN_VAL_BACK_MENU   0X0B    //settings background
	#define  BTN_VAL_RESET       0X0C
	#define  BTN_VAL_TAKE_OUT         0X0D    //
	#define  BTN_VAL_TAKE_OUT_STOP    0X0E
	u16 xdata temp = 0;
	switch(btn_val)
	{
		case BTN_VAL_START:     //Page1:Push Start
		 if(win_str_data.start == 0)
				win_change_page(WORK_CONFIRM_PAGE);
			break;	
		case BTN_VAL_CONFIRM://Page13:********************  ???????????????
			win_str_data.start = 1;
			win_change_page(WORK_PAGE);
			break;
		case BTN_VAL_STOP:     //Page1:push Stop************************
			if(win_str_data.start != 0)
			{
				win_str_data.start = 0;
			}
			break;			 
		case BTN_VAL_MENU:
			if(win_str_data.start != 0)break;
			win_change_page(MENU_PAGE);		
			break;		 
		case BTN_VAL_SET:         //Page1:Setting*****************************
			if(win_str_data.start != 0) break;  
			Fresh_Service_Time();
			win_change_page(SYSTEM_PAGE);
			break;
		case BTN_VAL_BACK_MAIN:
			win_change_page(WORK_PAGE);
			break;

		case BTN_VAL_BACK_MENU:
			win_change_page(MENU_PAGE);
			break;
		case BTN_VAL_INFO:
			if(win_str_data.logo == 4) //no logo
				win_change_page(INFO_NO_LOGO_PAGE);
			else
				win_change_page(INFO_PAGE);
			break;
		case BTN_VAL_RESET:    //运行时间复位输入密码界面
				win_change_page(PASSCODE_PAGE);
			break;
		
		case BTN_VAL_TAKE_OUT:   //取片开始
			if(win_str_data.start == 0)
			 {
				 win_change_page(PICKING_TABLETS_PAGE);
				 win_str_data.out_start = 1;
			 }
			break;
		case BTN_VAL_TAKE_OUT_STOP:  //取片停止
			if(win_str_data.out_start != 0) 
				win_str_data.out_start = 0;	
		    break;
	}
}


#define  BTN_VAL_NO	   		0X1C00
#define  BTN_VAL_YES	   	0X1400
#define  BTN_VAL_RETURN		0X1000
#define  BTN_VAL_UPSET	 	0X0C00
#define  BTN_VAL_OVERSET  	0X0800
#define  BTN_VAL_TOSET	    0X0400
//10 0000 0000
#define  BTN_VAL_STEP3_HOLD_TIME	0X06
#define  BTN_VAL_STEP2_HOLD_TIME	0X05
#define  BTN_VAL_STEP1_HOLD_TIME	0X04
#define  BTN_VAL_STEP3_PRESSURE		0X03
#define  BTN_VAL_STEP2_PRESSURE		0X02
#define  BTN_VAL_STEP1_PRESSURE	    0X01

/********************************************************
* Function: disp_input_icon
* Description: Displays the input icon on the screen based on the selected parameter. The function updates
* the display data for the input icon according to the current language setting and the selected parameter (level, total time, run time, or pause time).
* Parameters:
*   btn_val - The value of the button that corresponds to the selected parameter for which the
*********************************************************/
void disp_input_icon(u16 btn_val)
{
	u8 offset_table[] = {0, 1, 2, 3};  // 语言对应的偏移量 (CN, EN, RUS, JAPAN)
	u8 *disp_ptr[] = {
		&win_str_data.input_disp1,
		&win_str_data.input_disp2,
		&win_str_data.input_disp3,
		&win_str_data.input_disp4,
		&win_str_data.input_disp5,
		&win_str_data.input_disp6,
	};
	u8 disp_index;
	
	// 根据按钮值确定要修改的显示索引
	switch(btn_val)
	{
		case  BTN_VAL_STEP1_PRESSURE:	 disp_index = 0; break;
		case  BTN_VAL_STEP2_PRESSURE:	 disp_index = 1; break;
		case  BTN_VAL_STEP3_PRESSURE:	 disp_index = 2; break;
		case  BTN_VAL_STEP1_HOLD_TIME:	 disp_index = 3; break;
		case  BTN_VAL_STEP2_HOLD_TIME:	 disp_index = 4; break;
		case  BTN_VAL_STEP3_HOLD_TIME:	 disp_index = 5; break;
		default: return;
	}
	
	// 根据语言添加偏移量
	if(win_str_data.language < 4)
	{
		*disp_ptr[disp_index] += offset_table[win_str_data.language];
	}
	sys_write_vp(ICON_INPUT1_ADDR, (u8 *)&win_str_data.input_disp1, 6);
	sys_write_vp(ICON_INPUT1_WORD_ADDR, (u8 *)&win_str_data.input_disp1, 6);
}

/*
 * 1. When the program parameters setting page is entered, the parameters of the current program group will be displayed in the set area, and the program parameters of the current program group will be displayed in the prog area. 
 * 2. When the user clicks the Set button, if it is in test mode (prog_grp=0), it will jump to the program setting page directly; if it is in program mode (prog_grp=1-100), it will pop up a confirmation page, and after confirming, it will jump to the program setting page. 
 * 3. In the program parameters setting page, when the user clicks the Return button, it will jump back to the background page directly; when the user clicks the OverSet button, it will pop up a confirmation page, and after confirming, it will jump back to the background page. 
 * 4. In the program parameters setting page, when the user clicks any parameter button, it will enter the parameter editing state. In this state, when the user clicks any parameter button again, it will update the display according to the current value of that parameter; when the user clicks the Return button, it will exit the parameter editing state and return to the program parameters setting page without saving; when the user clicks the OverSet button, it will save all parameters of this program group to flash and exit to background page after confirming.
*/
static void win_prog_para_btn_hold_handler(u16 btn_val)
{
	u16 xdata temp;
	if(win_str_data.start != 0)
	{
		temp = 0;
		sys_write_vp(BTN_PROG_MODE_SET_ADDR,(u8*)&temp,2);
		return;
	}
	if(win_str_data.paras_sel == BTN_VAL_STEP1_PRESSURE)
	{
		if(win_str_data.set_step1_pressure>product_data[win_str_data.product_id].para1.max) win_str_data.set_step1_pressure = product_data[win_str_data.product_id].para1.max;
		else if(win_str_data.set_step1_pressure < product_data[win_str_data.product_id].para1.min) win_str_data.set_step1_pressure = product_data[win_str_data.product_id].para1.min;
		win_disp_level(SET_NUM1,win_str_data.set_step1_pressure);
	}
	else if(win_str_data.paras_sel == BTN_VAL_STEP2_PRESSURE)
	{
		if(win_str_data.set_step2_pressure >product_data[win_str_data.product_id].para1.max) win_str_data.set_step2_pressure = product_data[win_str_data.product_id].para1.max;
		else if(win_str_data.set_step2_pressure < product_data[win_str_data.product_id].para1.min) win_str_data.set_step2_pressure = product_data[win_str_data.product_id].para1.min;
		win_disp_level(SET_NUM2,win_str_data.set_step2_pressure);				
	}
	else if(win_str_data.paras_sel == BTN_VAL_STEP3_PRESSURE)
	{
		if(win_str_data.set_step3_pressure >product_data[win_str_data.product_id].para1.max) win_str_data.set_step3_pressure = product_data[win_str_data.product_id].para1.max;
		else if(win_str_data.set_step3_pressure < product_data[win_str_data.product_id].para1.min) win_str_data.set_step3_pressure = product_data[win_str_data.product_id].para1.min;
		win_disp_level(SET_NUM3,win_str_data.set_step3_pressure);				
	}
	else if(win_str_data.paras_sel == BTN_VAL_STEP1_HOLD_TIME)	
	{
		if(win_str_data.set_step1_hold_time >product_data[win_str_data.product_id].para2.max) win_str_data.set_step1_hold_time = product_data[win_str_data.product_id].para2.max;
		else if(win_str_data.set_step1_hold_time < product_data[win_str_data.product_id].para2.min) win_str_data.set_step1_hold_time = product_data[win_str_data.product_id].para2.min;
		win_disp_hold_time(SET_NUM1,win_str_data.set_step1_hold_time);						
	}
	else if(win_str_data.paras_sel == BTN_VAL_STEP2_HOLD_TIME)	
	{
		if(win_str_data.set_step2_hold_time >product_data[win_str_data.product_id].para2.max) win_str_data.set_step2_hold_time = product_data[win_str_data.product_id].para2.max;
		else if(win_str_data.set_step2_hold_time < product_data[win_str_data.product_id].para2.min) win_str_data.set_step2_hold_time = product_data[win_str_data.product_id].para2.min;
		win_disp_hold_time(SET_NUM2,win_str_data.set_step2_hold_time);							
	}
	else if(win_str_data.paras_sel == BTN_VAL_STEP3_HOLD_TIME)	
	{
		if(win_str_data.set_step3_hold_time >product_data[win_str_data.product_id].para2.max) win_str_data.set_step3_hold_time = product_data[win_str_data.product_id].para2.max;
		else if(win_str_data.set_step3_hold_time < product_data[win_str_data.product_id].para2.min) win_str_data.set_step3_hold_time = product_data[win_str_data.product_id].para2.min;
		win_disp_hold_time(SET_NUM3,win_str_data.set_step3_hold_time);						
	}
	switch(btn_val)	
	{
		case  BTN_VAL_STEP1_PRESSURE:
		case  BTN_VAL_STEP2_PRESSURE:
		case  BTN_VAL_STEP3_PRESSURE:
		case  BTN_VAL_STEP1_HOLD_TIME:
		case  BTN_VAL_STEP2_HOLD_TIME:
		case  BTN_VAL_STEP3_HOLD_TIME:
		{
			u8 xdata idx;
			memset(&win_str_data.input_disp1,0,sizeof(win_str_data.input_disp1) * 6);
			idx = (u8)(btn_val - 1);  /* 0x01~0x04 -> 0~3 */
			switch(idx)
			{
				case 0:
					win_str_data.input_disp1 = 0x01;
					break;
				case 1:
					win_str_data.input_disp2 = 0x01;
					break;
				case 2:
					win_str_data.input_disp3 = 0x01;
					break;
				case 3:
					win_str_data.input_disp4 = 0x01;
					break;
				case 4:
					win_str_data.input_disp5 = 0x01;
					break;
				case 5:
					win_str_data.input_disp6 = 0x01;
					break;	
				default:
					break;
			}
			disp_input_icon(btn_val);
			win_str_data.paras_sel = btn_val;
		}
			break;


		case BTN_VAL_TOSET:
				if(win_str_data.prog_grp == 0) win_str_data.prog_grp = 1;
				sys_write_vp(ARTNUM_PROG_NUM_ADDR,(u8*)&win_str_data.prog_grp,1);
				win_change_page(PROGRAM_PAGE);	 //change page
			break;
		case BTN_VAL_RETURN: //Reset the key value when returning and jump page and clean paras_sel
				temp = 0;
				sys_write_vp(BTN_PROG_MODE_SET_ADDR,(u8*)&temp,2);	
				win_str_data.paras_sel = 0;
				win_clear_input_icon();//clear input icon
				win_change_page(WORK_PAGE);
			break;
		case BTN_VAL_OVERSET:  //Jump to pop-up page
				win_clear_input_icon();//clear input icon
				win_change_page(PROGRAM_CONFIRM_PAGE);	
			break;
		
		case BTN_VAL_YES:  	 //pop-up page YES   Put Set -> Prog and save flash
				memcpy((u8 *)&win_str_data.prog_step1_pressure,(u8 *)&win_str_data.set_step1_pressure,12);  					//Set value to prog value
				win_save_prog_paras(PROG_STEP1_PRESSURE,(u8*)&win_str_data.prog_step1_pressure,6);	//write norflash
				win_change_page(PROGRAM_PAGE);		//change page
			break;
		
		case BTN_VAL_NO:
				win_change_page(PROGRAM_PAGE);	
			break;
		case BTN_VAL_UPSET://???download program parameters to current parameters
               
				win_str_data.paras_sel = 0;
				win_clear_input_icon();//clear input icon

				norflash_write(SYS_LAST_PROG_OFFSET,(u8*)&win_str_data.prog_grp,2);

				memcpy((u8 *)&win_str_data.set_step1_pressure,(u8 *)&win_str_data.prog_step1_pressure,sizeof(win_str_data.prog_step1_pressure) * 6); 
				memcpy((u8 *)&win_str_data.use_pressure,(u8 *)&win_str_data.prog_step1_pressure,sizeof(win_str_data.prog_step1_pressure) * 2);
				win_disp_level(SET_NUM1,win_str_data.set_step1_pressure);
				win_disp_level(SET_NUM2,win_str_data.set_step2_pressure);
				win_disp_level(SET_NUM3,win_str_data.set_step3_pressure);
				win_disp_hold_time(SET_NUM1,win_str_data.set_step1_hold_time);
				win_disp_hold_time(SET_NUM2,win_str_data.set_step2_hold_time);
				win_disp_hold_time(SET_NUM3,win_str_data.set_step3_hold_time);

				temp = 0;
				sys_write_vp(BTN_PROG_MODE_SET_ADDR,(u8*)&temp,2);	
		
			break;
				
		default:
			
			win_str_data.paras_sel = btn_val;
			break;
	}
}



/*

*/
static void win_para_keypad_btn_click_handler(u16 btn_val)
{
	#define  BTN_VAL_0		10
	#define  BTN_VAL_CANCEL	11
	u16 xdata temp;
	u16 xdata max_val = 0;
	u16 xdata disp_ch = 0;
	u16 xdata *p_set_val = 0;
	u8 xdata is_hold_time = 0;

	switch(win_str_data.paras_sel)
	{
		case BTN_VAL_STEP1_PRESSURE:
			p_set_val = &win_str_data.set_step1_pressure;
			max_val = product_data[win_str_data.product_id].para1.max;
			disp_ch = SET_NUM1;
			break;
		case BTN_VAL_STEP2_PRESSURE:
			p_set_val = &win_str_data.set_step2_pressure;
			max_val = product_data[win_str_data.product_id].para1.max;
			disp_ch = SET_NUM2;
			break;
		case BTN_VAL_STEP3_PRESSURE:
			p_set_val = &win_str_data.set_step3_pressure;
			max_val = product_data[win_str_data.product_id].para1.max;
			disp_ch = SET_NUM3;
			break;
		case BTN_VAL_STEP1_HOLD_TIME:
			p_set_val = &win_str_data.set_step1_hold_time;
			max_val = product_data[win_str_data.product_id].para2.max;
			disp_ch = SET_NUM1;
			is_hold_time = 1;
			break;
		case BTN_VAL_STEP2_HOLD_TIME:
			p_set_val = &win_str_data.set_step2_hold_time;
			max_val = product_data[win_str_data.product_id].para2.max;
			disp_ch = SET_NUM2;
			is_hold_time = 1;
			break;
		case BTN_VAL_STEP3_HOLD_TIME:
			p_set_val = &win_str_data.set_step3_hold_time;
			max_val = product_data[win_str_data.product_id].para2.max;
			disp_ch = SET_NUM3;
			is_hold_time = 1;
			break;
		default:
			break;
	}

	if(p_set_val == 0) return;

	temp = *p_set_val;
	if(btn_val < BTN_VAL_CANCEL)
	{
		if(btn_val == BTN_VAL_0) btn_val = 0;
		if(max_val > 99) temp = temp % 100;
		else if(max_val > 9) temp = temp % 10;
		temp = temp * 10;
		temp += btn_val;
	}
	else
	{
		temp = temp / 10;
	}

	*p_set_val = temp;
	if(is_hold_time) win_disp_hold_time(disp_ch,*p_set_val);
	else win_disp_level(disp_ch,*p_set_val);
}




#define  BTN_VAL_ACC	    0X02
#define  BTN_VAL_DEC	    0X01
/*
 * When the user clicks the program group selection button, it will switch the program group according to the button value (increment or decrement), and then load the parameters of the new program group from flash and update the display.
*/
static void win_prog_num_sel_btn_click_handler(u16 btn_val)
{
	switch(btn_val)
	{
		case BTN_VAL_ACC:
				if(win_str_data.prog_grp<20) win_str_data.prog_grp++;	
			break;
		case BTN_VAL_DEC:
				if(win_str_data.prog_grp>1) win_str_data.prog_grp--;	
			break;
		default:break;
	}
	sys_write_vp(ARTNUM_PROG_NUM_ADDR,(u8*)&win_str_data.prog_grp,1);
	
	win_load_prog_paras(PROG_STEP1_PRESSURE,(u8*)&win_str_data.prog_step1_pressure,6);
	win_disp_level(PROG_NUM1,win_str_data.prog_step1_pressure);
	win_disp_level(PROG_NUM2,win_str_data.prog_step2_pressure);
	win_disp_level(PROG_NUM3,win_str_data.prog_step3_pressure);
	win_disp_hold_time(PROG_NUM1,win_str_data.prog_step1_hold_time);
	win_disp_hold_time(PROG_NUM2,win_str_data.prog_step2_hold_time);
	win_disp_hold_time(PROG_NUM3,win_str_data.prog_step3_hold_time);
	
}


/*

*/
static void win_pass_keypad_btn_click_handler(u16 btn_val)
{
	u16 xdata temp;
	STR_WIN_TypeDef	*obj = &win_str_data;	
	temp = win_str_data.passcode;
	if(btn_val == 0X0C)   //弹窗√
	{
		win_str_data.used_time_h = 0;
		win_str_data.used_time_l = 0;

		norflash_write(RUNTIME_MIN_HADDR,(u8 *)&win_str_data.used_time_h,2);

		win_str_data.used_time = win_str_data.used_time_h;
		win_str_data.used_time <<= 16;
		win_str_data.used_time |= win_str_data.used_time_l;
		win_str_data.disp_time = win_str_data.used_time/3600;  //小时数
	
		sys_write_vp(ARTNUM_UT_ADDR,(u8*)&win_str_data.disp_time,1);	 //总运行时间清零
		win_str_data.passcode = 0;
		win_change_page(PASSCODE_PAGE);
	}
	if(btn_val == 0X0D)   //弹窗 ×
	{
		win_change_page(PASSCODE_PAGE);
	}
	
	else if(btn_val < BTN_VAL_CANCEL)
	{
		if(btn_val == 10) btn_val =0;
		temp = temp%1000;
		temp = temp*10;
		temp +=btn_val;
		if(temp>9999) temp =9999;
		else if(temp <0) temp =0;
		win_str_data.passcode = temp;
		sys_write_vp(ARTNUM_PASSCODE_ADDR,(u8*)&win_str_data.passcode,1);				
	}
	else
	{			
		temp= temp/10;
		if(temp <0) temp=0;
		win_str_data.passcode = temp;
		sys_write_vp(ARTNUM_PASSCODE_ADDR,(u8*)&win_str_data.passcode,1);			
	}
	if(temp == 1010)
	{
		win_change_page(PASSCODE_CONFIRM_PAGE);
		win_str_data.passcode = 0;
		sys_write_vp(ARTNUM_PASSCODE_ADDR,(u8*)&win_str_data.passcode,1);	
	}
	else if(temp == 5973)
	{
		win_change_page(FAC_PAGE);
		win_str_data.passcode = 0;
		sys_write_vp(ARTNUM_PASSCODE_ADDR,(u8*)&win_str_data.passcode,1);	
	}

}



void win_save_prog_paras(u16 offaddr,u8 *var_addr,u16 len)
{
	u16 addr;
	addr = PROG1_BASE_NORADDR + 0x10 * (win_str_data.prog_grp - 1) + offaddr;

	norflash_write(addr,var_addr,len);
}

/*

*/
void win_load_prog_paras(u16 offaddr,u8 *var_addr,u16 len)
{
	u16 xdata addr;
	u16 xdata i;	

	addr = PROG1_BASE_NORADDR + 0x10 * (win_str_data.prog_grp - 1) + offaddr;

	norflash_read(addr,var_addr,len);
	
	for(i = 0;i<len;i++)
	{
		addr = offaddr + i;
		switch(addr)
		{
			case PROG_STEP1_PRESSURE:
				if(win_str_data.prog_step1_pressure > product_data[win_str_data.product_id].para1.max)	win_str_data.prog_step1_pressure = product_data[win_str_data.product_id].para1.min;	
				if(win_str_data.prog_step1_pressure < product_data[win_str_data.product_id].para1.min)	win_str_data.prog_step1_pressure = product_data[win_str_data.product_id].para1.min;	
				break;
			
			case PROG_STEP2_PRESSURE:	
				if(win_str_data.prog_step2_pressure > product_data[win_str_data.product_id].para1.max)	win_str_data.prog_step2_pressure = product_data[win_str_data.product_id].para1.min;	
				if(win_str_data.prog_step2_pressure < product_data[win_str_data.product_id].para1.min)	win_str_data.prog_step2_pressure = product_data[win_str_data.product_id].para1.min;		
				break;
			
			case PROG_STEP3_PRESSURE:
				if(win_str_data.prog_step3_pressure > product_data[win_str_data.product_id].para1.max)	win_str_data.prog_step3_pressure = product_data[win_str_data.product_id].para1.min;	
				if(win_str_data.prog_step3_pressure < product_data[win_str_data.product_id].para1.min)	win_str_data.prog_step3_pressure = product_data[win_str_data.product_id].para1.min;	
				break;
			
			case PROG_STEP1_HOLD_TIME:
				if(win_str_data.prog_step1_hold_time > product_data[win_str_data.product_id].para2.max)	win_str_data.prog_step1_hold_time = product_data[win_str_data.product_id].para2.min;	
				if(win_str_data.prog_step1_hold_time < product_data[win_str_data.product_id].para2.min)	win_str_data.prog_step1_hold_time = product_data[win_str_data.product_id].para2.min;	
				break;
			case PROG_STEP2_HOLD_TIME:
				if(win_str_data.prog_step2_hold_time > product_data[win_str_data.product_id].para2.max)	win_str_data.prog_step2_hold_time = product_data[win_str_data.product_id].para2.min;	
				if(win_str_data.prog_step2_hold_time < product_data[win_str_data.product_id].para2.min)	win_str_data.prog_step2_hold_time = product_data[win_str_data.product_id].para2.min;	
				break;
			case PROG_STEP3_HOLD_TIME:
				if(win_str_data.prog_step3_hold_time > product_data[win_str_data.product_id].para2.max)	win_str_data.prog_step3_hold_time = product_data[win_str_data.product_id].para2.min;	
				if(win_str_data.prog_step3_hold_time < product_data[win_str_data.product_id].para2.min)	win_str_data.prog_step3_hold_time = product_data[win_str_data.product_id].para2.min;	
				break;

		
			default:break;
		}
	}
}

/********************************************************
????????win_fac_set_btn_click_handler(u16 btn_val)
?????????????????
*********************************************************/
#define BTN_PRESSURE_RELIEF_TIME    0X01
#define BTN_SAMPLING_TIME	     	0X02
#define BTN_MOLD_PRESSING1				 0X03
#define BTN_MOLD_PRESSING2				 0X04

static void win_fac_set_btn_click_handler(u16 btn_val)
{
	switch(btn_val)
	{
		case 0X05://logo
		case 0X06://logo
			win_change_page(SYSTEM_PAGE);
			break;
		case 0X08://logo
			win_str_data.factory_sel = 0;
			win_str_data.logo = 4 - win_str_data.logo;
			if(win_str_data.logo >0) win_str_data.logo = 4;
			sys_write_vp(ANIMOTION_LOGO_ADDR,(u8*)&win_str_data.logo,1);	//no logo for oem	
			norflash_write(SYS_LOGO_OFFSET,(u8 *)&win_str_data.logo,2);
			if(win_str_data.logo == 4)
			{
				sys_write_vp(STRING_PRODUCT_ADDR,(u8*)modle_version,sizeof(modle_version));
			}
			else
			{
				sys_write_vp(STRING_PRODUCT_ADDR,(u8*)product_data[win_str_data.product_id].name,sizeof(product_data[win_str_data.product_id].name));
			}				
			break;
		case BTN_PRESSURE_RELIEF_TIME:
			win_str_data.factory_sel = BTN_PRESSURE_RELIEF_TIME;
			win_str_data.sys_input_num = win_str_data.pressure_relief_time;
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&win_str_data.sys_input_num,1);
			win_change_page(INPUT_NUM_PAGE);
			break;
		case BTN_SAMPLING_TIME:
			win_str_data.factory_sel = BTN_SAMPLING_TIME;
			win_str_data.sys_input_num = win_str_data.sampling_time;
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&win_str_data.sys_input_num,1);
			win_change_page(INPUT_NUM_PAGE);
			break;
		case BTN_MOLD_PRESSING1:
			win_str_data.factory_sel = BTN_MOLD_PRESSING1;
			win_str_data.sys_input_num = win_str_data.mold_pressing1;
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&win_str_data.sys_input_num,1);
			win_change_page(INPUT_NUM_PAGE);
			break;
		case BTN_MOLD_PRESSING2:
			win_str_data.factory_sel = BTN_MOLD_PRESSING2;
			win_str_data.sys_input_num = win_str_data.mold_pressing2;
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&win_str_data.sys_input_num,1);
			win_change_page(INPUT_NUM_PAGE);
			break;
		
		default:break;
	}
}

static void win_factory_keypad_btn_click_handler(u16 btn_val)
{
	#define  BTN_FACTORY_VAL_0		0X0A	
	#define  BTN_FACTORY_VAL_CANCLE	0X0B	
	#define  BTN_FACTORY_VAL_ENTER	0X0C
	u16 xdata temp,flag;

	switch(win_str_data.factory_sel)//��̨����0X1300
	{
		case BTN_PRESSURE_RELIEF_TIME:
			temp = win_str_data.sys_input_num;
			if(btn_val < BTN_FACTORY_VAL_CANCLE)
			{
				if(btn_val == BTN_FACTORY_VAL_0) btn_val = 0;
				temp = temp%100;
				temp = temp*10;
				temp += btn_val;
				if(temp > 99) temp = 99;
			}
			else if(btn_val == BTN_FACTORY_VAL_CANCLE)
			{
				temp = temp/10;
			}
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&temp,1);
			win_str_data.sys_input_num = temp;

			if(btn_val == BTN_FACTORY_VAL_ENTER)
			{
				win_str_data.pressure_relief_time = win_str_data.sys_input_num;
				if(win_str_data.pressure_relief_time < 1) win_str_data.pressure_relief_time = 1;
				if(win_str_data.pressure_relief_time > 99) win_str_data.pressure_relief_time = 99;

				sys_write_vp(ARTNUM_BACKEND_PRESSURE_RELIEF_TIME_ADDR,(u8 *)&win_str_data.pressure_relief_time,2);
				norflash_write(PRE_RELIEF_TIME_ADDR,(u8*)&win_str_data.pressure_relief_time,2);
				flag = FACTORY_PARAMS_INIT_VALUE;
				norflash_write(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&flag,2);
				win_str_data.factory_sel = 0;
				win_change_page(SYSTEM_PAGE);
			}
			break;

		case BTN_SAMPLING_TIME:
			temp = win_str_data.sys_input_num;
			if(btn_val < BTN_FACTORY_VAL_CANCLE)
			{
				if(btn_val == BTN_FACTORY_VAL_0) btn_val = 0;
				temp = temp%100;
				temp = temp*10;
				temp += btn_val;
				if(temp > 99) temp = 99;
			}
			else if(btn_val == BTN_FACTORY_VAL_CANCLE)
			{
				temp = temp/10;
			}
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&temp,1);
			win_str_data.sys_input_num = temp;

			if(btn_val == BTN_FACTORY_VAL_ENTER)
			{
				win_str_data.sampling_time = win_str_data.sys_input_num;
				if(win_str_data.sampling_time < 1) win_str_data.sampling_time = 1;
				if(win_str_data.sampling_time > 99) win_str_data.sampling_time = 99;

				sys_write_vp(ARTNUM_BACKEND_SAMPLING_TIME_ADDR,(u8 *)&win_str_data.sampling_time,1);
				norflash_write(SAMPLING_TIME_ADDR,(u8*)&win_str_data.sampling_time,2);
				flag = FACTORY_PARAMS_INIT_VALUE;
				norflash_write(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&flag,2);
				win_str_data.factory_sel = 0;
				win_change_page(SYSTEM_PAGE);
			}
			break;

		case BTN_MOLD_PRESSING1:
			temp = win_str_data.sys_input_num;
			if(btn_val < BTN_FACTORY_VAL_CANCLE)
			{
				if(btn_val == BTN_FACTORY_VAL_0) btn_val = 0;
				temp = temp%1000;
				temp = temp*10;
				temp += btn_val;
				if(temp > 400) temp = 400;
			}
			else if(btn_val == BTN_FACTORY_VAL_CANCLE)
			{
				temp = temp/10;
			}
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&temp,1);
			win_str_data.sys_input_num = temp;

			if(btn_val == BTN_FACTORY_VAL_ENTER)
			{
				win_str_data.mold_pressing1 = win_str_data.sys_input_num;
				if(win_str_data.mold_pressing1 < 1) win_str_data.mold_pressing1 = 1;
				if(win_str_data.mold_pressing1 > 400) win_str_data.mold_pressing1 = 400;

				sys_write_vp(ARTNUM_BACKEND_MOLD_PRESSING1_ADDR,(u8 *)&win_str_data.mold_pressing1,1);
				norflash_write(MOLD_PRESSING1_ADDR,(u8*)&win_str_data.mold_pressing1,2);
				flag = FACTORY_PARAMS_INIT_VALUE;
				norflash_write(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&flag,2);
				win_str_data.factory_sel = 0;
				win_change_page(SYSTEM_PAGE);
			}
			break;

		case BTN_MOLD_PRESSING2:
			temp = win_str_data.sys_input_num;
			if(btn_val < BTN_FACTORY_VAL_CANCLE)
			{
				if(btn_val == BTN_FACTORY_VAL_0) btn_val = 0;
				temp = temp%1000;
				temp = temp*10;
				temp += btn_val;
				if(temp > 400) temp = 400;
			}
			else if(btn_val == BTN_FACTORY_VAL_CANCLE)
			{
				temp = temp/10;
			}
			sys_write_vp(ARTNUM_INPUTNUM_ADDR,(u8 *)&temp,1);
			win_str_data.sys_input_num = temp;

			if(btn_val == BTN_FACTORY_VAL_ENTER)
			{
				win_str_data.mold_pressing2 = win_str_data.sys_input_num;
				if(win_str_data.mold_pressing2 < 1) win_str_data.mold_pressing2 = 1;
				if(win_str_data.mold_pressing2 > 400) win_str_data.mold_pressing2 = 400;

				sys_write_vp(ARTNUM_BACKEND_MOLD_PRESSING2_ADDR,(u8 *)&win_str_data.mold_pressing2,1);
				norflash_write(MOLD_PRESSING2_ADDR,(u8*)&win_str_data.mold_pressing2,2);
				flag = FACTORY_PARAMS_INIT_VALUE;
				norflash_write(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&flag,2);
				win_str_data.factory_sel = 0;
				win_change_page(SYSTEM_PAGE);
			}
			break;

		default:
			break;
	}
}


void win_disp_step(u16 ch,u16 val)
{
	if(ch & MAIN_NUM)
	{
		sys_write_vp(ARTNUM_MAIN_TABLETTING_STEP_ADDR,(u8 *)&val,1);
	}
}

void win_disp_level(u16 ch,u16 val)
{
	u8 *pval;
	// sys_write_vp len is word-count (1 word = 2 bytes), not byte-count.
	// So len=1 writes one 16-bit variable; changing to len=2 will write two words.
	pval = (u8 *)&val;

#define DISP_LEVEL_IF(mask, addr) do { if(ch & (mask)) sys_write_vp((addr), pval, 1); } while(0)
	DISP_LEVEL_IF(MAIN_NUM,  ARTNUM_MAIN_SET_PRESSURE_ADDR);
	DISP_LEVEL_IF(SET_NUM1,  ARTNUM_SET_STEP1_PRESSURE_ADDR);
	DISP_LEVEL_IF(SET_NUM2,  ARTNUM_SET_STEP2_PRESSURE_ADDR);
	DISP_LEVEL_IF(SET_NUM3,  ARTNUM_SET_STEP3_PRESSURE_ADDR);
	DISP_LEVEL_IF(PROG_NUM1, ARTNUM_PROG_STEP1_PRESSURE_ADDR);
	DISP_LEVEL_IF(PROG_NUM2, ARTNUM_PROG_STEP2_PRESSURE_ADDR);
	DISP_LEVEL_IF(PROG_NUM3, ARTNUM_PROG_STEP3_PRESSURE_ADDR);
#undef DISP_LEVEL_IF
}
/******************************************************************************************
??????void win_disp_hold_time(u16 ch,u16 val)
?????????????????																														
*******************************************************************************************/

void win_disp_hold_time(u16 ch,u16 val)  //???????? ???????????
{
	u8 *pval;
	// Keep len=1 here for one 16-bit VP variable write.
	pval = (u8 *)&val;

#define DISP_HOLD_IF(mask, addr) do { if(ch & (mask)) sys_write_vp((addr), pval, 1); } while(0)
	DISP_HOLD_IF(MAIN_NUM,  ARTNUM_MAIN_SET_HOLD_TIME_ADDR);
	DISP_HOLD_IF(SET_NUM1,  ARTNUM_SET_STEP1_HOLD_TIME_ADDR);
	DISP_HOLD_IF(SET_NUM2,  ARTNUM_SET_STEP2_HOLD_TIME_ADDR);
	DISP_HOLD_IF(SET_NUM3,  ARTNUM_SET_STEP3_HOLD_TIME_ADDR);
	DISP_HOLD_IF(PROG_NUM1, ARTNUM_PROG_STEP1_HOLD_TIME_ADDR);
	DISP_HOLD_IF(PROG_NUM2, ARTNUM_PROG_STEP2_HOLD_TIME_ADDR);
	DISP_HOLD_IF(PROG_NUM3, ARTNUM_PROG_STEP3_HOLD_TIME_ADDR);
#undef DISP_HOLD_IF
}

void win_disp_count_time(u16 ch,u16 val)
{
	if(ch & MAIN_NUM)
	{
		// len=1 means one 16-bit word write.
		sys_write_vp(ARTNUM_MAIN_HOLD_TIME_ADDR,(u8 *)&val,1);
	}
}


/******************************************************************************************
??????void win_fresh_window(SysDataDef *sys)
???????????��??????																														
*******************************************************************************************/
void win_fresh_window(void)
{
	if(str_sys.door == 0) win_str_data.door_warning = 1;   //??��?????
	else win_str_data.door_warning = 0;
	
	sys_write_vp(ICON_DOOR_WARRING_ADDR,(u8*)&win_str_data.door_warning,1);
	sys_write_vp(ICON_START_ADDR,(u8*)&win_str_data.start,1);
	win_fresh_timer_block();
}
	
/*************??????????************************/
void win_fresh_timer_block(void)
{
	static u16 timer_fresh_ratio;
	if(timer_fresh_ratio >0) timer_fresh_ratio--;	
	{
		timer_fresh_ratio = 50;//20hz
		
		win_disp_step(MAIN_NUM,win_str_data.disp_step);  //?????????
		win_disp_level(MAIN_NUM,win_str_data.disp_pressure);
		win_disp_hold_time(MAIN_NUM,win_str_data.disp_hold_time);
		win_disp_count_time(MAIN_NUM,win_str_data.disp_hold_time_countdown);
	
		sys_write_vp(ARTNUM_SAMPLING_TIME_TICK_ADDR,(u8 *)&win_str_data.sampling_time_tick,1);
	}
}

void Fresh_Service_Time(void)
{
	win_str_data.disp_time = win_str_data.used_time/3600;  //小时数
	sys_write_vp(ARTNUM_UT_ADDR,(u8*)&win_str_data.disp_time,1);
}


/********************************************************
函数名：win_light_set_btn_hold_handler()
函数功能：亮度设置
*********************************************************/
static void win_light_set_btn_hold_handler(u16 btn_val)
{
	win_str_data.light = btn_val;
	sys_setdis_light(win_str_data.light);
	norflash_write(SYS_LIGHT_OFFSET,(u8 *)&win_str_data.light,2);	
}
/********************************************************
函数名：win_language_set_btn_hold_handler()
函数功能：语言设置
*********************************************************/
static void win_language_set_btn_hold_handler(u16 btn_val)
{
	win_str_data.language = btn_val;
	norflash_write(SYS_LANGUAGE_OFFSET,(u8 *)&win_str_data.language,2);	
}
/********************************************************
函数名：win_buzz_set_btn_hold_handler()
函数功能：蜂鸣器设置
*********************************************************/
static void win_buzz_set_btn_hold_handler(u16 btn_val)
{
	win_str_data.alarm = btn_val;
	sys_enable_speaker(1-win_str_data.alarm);
	norflash_write(SYS_BUZZ_OFFSET,(u8 *)&win_str_data.alarm,2);	
}

void Init_read_norflash(void)
{
	norflash_read(SYS_LOGO_OFFSET,(u8 *)&win_str_data.logo,8);
}

void win_load_setpara()
{
	if(win_str_data.logo >0) win_str_data.logo = 4;
	sys_write_vp(ANIMOTION_LOGO_ADDR,(u8*)&win_str_data.logo,1);	//no logo for oem

	if(win_str_data.logo == 4)
		sys_write_vp(STRING_PRODUCT_ADDR,(u8*)modle_version,sizeof(modle_version));
	else
		sys_write_vp(STRING_PRODUCT_ADDR,(u8*)product_data[win_str_data.product_id].name,sizeof(product_data[win_str_data.product_id].name));

	sys_write_vp(STRING_VERSION_ADDR,(u8*)Software_version,sizeof(Software_version));
	

	if(win_str_data.light > 100) win_str_data.light = 100;
	if(win_str_data.light < 10) win_str_data.light = 10;
	sys_setdis_light(win_str_data.light);
	sys_write_vp(BTN_SET_LIGHT_ADDR,(u8*)&win_str_data.light,1);	

	if(win_str_data.alarm > 1) win_str_data.alarm = 1;
	sys_enable_speaker(1-win_str_data.alarm);		
	sys_write_vp(BTN_SET_BUZZ_ADDR,(u8*)&win_str_data.alarm,1);
	
	if(win_str_data.language >= 3) win_str_data.language = 3;
	sys_write_vp(BTN_LANGUAGE_ADDR,(u8*)&win_str_data.language,1);
}
void Prog_mode_para_read(void)
{
	if(win_str_data.prog_grp > 20) win_str_data.prog_grp = 1;

	win_load_prog_paras(PROG_STEP1_PRESSURE,(u8*)&win_str_data.prog_step1_pressure,6);
	memcpy((u8*)&win_str_data.use_pressure,(u8*)&win_str_data.prog_step1_pressure,4);
	memcpy((u8*)&win_str_data.set_step1_pressure,(u8*)&win_str_data.prog_step1_pressure,12);

	sys_write_vp(ARTNUM_MAIN_PROG_NUM_ADDR,(u8*)&win_str_data.prog_grp,1);
}
void win_init(void)
{

	u16 xdata init_flag;
	u16 xdata flag;
	memset(&win_str_data,0,sizeof(win_str_data));
	
//init workbence para
//read from flash///////////////////////////////////////////
	Init_read_norflash();
	if(win_str_data.product_id >= PRODUCT_TOTAL) win_str_data.product_id = 0;

//2.load system parametes settings
	win_load_setpara();
//3	service time

//4 program group
	Prog_mode_para_read();
//3	service time
	win_str_data.used_time = win_str_data.used_time_h;
	win_str_data.used_time <<= 16;
	win_str_data.used_time |= win_str_data.used_time_l;
	win_str_data.disp_time = win_str_data.used_time/3600;  //小时数

	init_flag = 0;
	norflash_read(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&init_flag,2);  // Read 2 bytes
	
	if(init_flag == FACTORY_PARAMS_INIT_VALUE)
	{
		// Parameters have been initialized and saved, load from Flash
		norflash_read(PRE_RELIEF_TIME_ADDR,(u8*)&win_str_data.pressure_relief_time,4);
		if(win_str_data.pressure_relief_time < 1 || win_str_data.pressure_relief_time > 99)
			win_str_data.pressure_relief_time = 45;  // Safety check: invalid saved value
		
		if(win_str_data.sampling_time < 1 || win_str_data.sampling_time > 99)
			win_str_data.sampling_time = 50;  // Safety check: invalid saved value

		if(win_str_data.mold_pressing1 < 1 || win_str_data.mold_pressing1 > 400)
			win_str_data.mold_pressing1 = 400;  // Safety check: invalid saved value

		if(win_str_data.mold_pressing2 < 1 || win_str_data.mold_pressing2 > 400)
			win_str_data.mold_pressing2 = 150;  // Safety check: invalid saved value
	}
	else
	{
		// First boot: use factory default values and mark as initialized
		win_str_data.pressure_relief_time = 45;   // Default: 45S pressure relief time
		win_str_data.sampling_time = 50;          // Default: 50S sampling time
		win_str_data.mold_pressing1 = 400;        // Default: 40T mold pressing1
		win_str_data.mold_pressing2 = 150;        // Default: 15T mold pressing2
		
		// Save defaults to Flash for first time
		flag = FACTORY_PARAMS_INIT_VALUE;  // Set magic number 0xA5A5
		norflash_write(FACTORY_PARAMS_INIT_FLAG_ADDR,(u8*)&flag,2);  // Write 2 bytes
		norflash_write(PRE_RELIEF_TIME_ADDR,(u8*)&win_str_data.pressure_relief_time,4);
	}
	sys_write_vp(ARTNUM_BACKEND_PRESSURE_RELIEF_TIME_ADDR,(u8 *)&win_str_data.pressure_relief_time,4);

	win_str_data.sampling_pressing = 10;
	
	sys_delay_about_ms(4000);  
	
	win_change_page(WORK_PAGE);
}
