#include "func_handler.h"
#include "start_win.h"
//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////button paras config///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/*********************��ά����********************/
code const u16 btn_click_pararlist[BTN_EVENT_NUM][2]={   //BTN_EVENT_NUM
{BTN_MAIN_PAGE_ADDR,				BTN_TYPE_CLICK},//paras input 
{BTN_PARA_KEYPAD_ADDR,			BTN_TYPE_CLICK},
{BTN_PASS_KEYPAD_ADDR,      BTN_TYPE_CLICK},
{BTN_PROG_NUM_SEL_ADDR,			BTN_TYPE_CLICK},
{BTN_FAC_SET_ADDR,			    BTN_TYPE_CLICK},
{BTN_FAC_KEYPAD_ADDR,				BTN_TYPE_CLICK},
{BTN_PROG_MODE_SET_ADDR,		BTN_TYPE_HOLD_RES},
{BTN_SET_LIGHT_ADDR,				BTN_TYPE_HOLD_RES},
{BTN_LANGUAGE_ADDR,					BTN_TYPE_HOLD_RES},
{BTN_SET_BUZZ_ADDR,					BTN_TYPE_HOLD_RES},
};
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

bit is_btn_scan = 0;//�Ƿ�Ҫ���а�ť���ɨ��

xdata STR_BTN_TypeDef btn_str_data[BTN_EVENT_NUM];



static void btn_InitStructure(STR_BTN_TypeDef *obj,u16 index)
{
	obj->addr = btn_click_pararlist[index][0];//button address
	obj->type = btn_click_pararlist[index][1];//button type
	switch(obj->type)
	{
		case BTN_TYPE_CLICK:
				obj->func_callback = btn_click_callback;
				obj->val =0;
				obj->val_temp = 0;
			break;
		case BTN_TYPE_HOLD_RES:
				sys_read_vp(obj->addr,(u8*)&obj->val,1);
				obj ->val_temp = obj ->val;
				obj ->func_callback = btn_hold_res_callback;
			break;
		case BTN_TYPE_HOLD_TIME:
				obj->func_callback = btn_hold_click_callback;
				obj->func_hold_callback = btn_hold_callback;
				obj->val =0;
				obj->val_temp = 0;
				obj->timer = 0;
			break;
		default:
				obj->func_callback = 0;
				obj->func_hold_callback = 0;
				obj->val =0;
				obj->val_temp = 0;
				obj->timer = 0;
			break;
	}

}
static void btn_click_event(STR_BTN_TypeDef *obj)
{
	u16 val;
	sys_read_vp(obj->addr,(u8*)&obj->val,1);
	switch(obj->type)
	{
		case BTN_TYPE_CLICK:
			//����Ƿ��а�ť����
			if(obj->val !=0)
			{
				//��ť����¼�����,���ݸ���Ӧ�Ľ���	
				obj->func_callback(obj->addr,obj->val);			
				//�������ֵ
				obj->val = 0;
				sys_write_vp(obj->addr,(u8*)&obj->val,1);	
			}
			break;
		case BTN_TYPE_HOLD_RES:
			if(obj->val !=obj->val_temp)
			{
				obj->func_callback(obj->addr,obj->val);			
				obj->val_temp = obj->val;
				val=1;
				sys_write_vp(HOLD_ACTIVE_ADDR,(u8*)&val,1);
				val=0;
				sys_write_vp(HOLD_PASSIVE_ADDR,(u8*)&val,1);
			}				
			break;
		case BTN_TYPE_HOLD_TIME://click event,selected func
			if(obj->val !=0)
			{		
				if((obj->timer <10)&&(obj->val != obj->val_temp))
				{
					obj->func_callback(obj->addr,obj->val);	
				}
				if(obj->timer ==20)// 600ms hold event,popup shotkey select menu
				{
					obj->func_hold_callback(obj->addr,obj->val);
					//�������ֵ
					obj->val = 0;
					sys_write_vp(obj->addr,(u8*)&obj->val,1);		
				}
				obj->timer++;
			}
			else
			{
				obj->timer = 0;
			}
			obj->val_temp = obj->val;
			break;
		default:
			break;
	}
}

void btn_init(void)
{
	u16 i;
	u16 val;
	for(i=0;i<BTN_EVENT_NUM;i++)
	{
		btn_InitStructure(&btn_str_data[i],i);
	}
	//init hold button reg
	val=1;
	sys_write_vp(HOLD_ACTIVE_ADDR,(u8*)&val,1);
	val=0;
	sys_write_vp(HOLD_PASSIVE_ADDR,(u8*)&val,1);
}

//���ڲ�����ť���ɨ���ź�,����1ms�Ķ�ʱ���е��ü���
void btn_click_tick()
{
	static idata u8 tick = 0;
	tick++;
	if(tick==BTN_SCAN_PERIOD)
	{
		tick = 0;
		is_btn_scan = 1;//����һ����ť���ɨ���ź�
	}
}

//��ť����¼�ɨ�貢����
void btn_click_handler(void)
{
	u16 i;

	if(is_btn_scan==0)//�Ƿ���ɨ���ź�,û�еĻ���ɶҲ����,ֱ�ӷ���
		return;
	
	is_btn_scan = 0;//���

	for(i=0;i<BTN_EVENT_NUM;i++)
	{
		btn_click_event(&btn_str_data[i]);
	}
}










