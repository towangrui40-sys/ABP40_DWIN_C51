#ifndef __SYS_H__
#define __SYS_H__
#include "t5los8051.h"
#include <string.h>
//�����ض���
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;
typedef signed char     s8;
typedef signed short    s16;
typedef signed long     s32;

//���Ź��궨��
#define	WDT_ON()				MUX_SEL|=0x02		//�������Ź�
#define	WDT_OFF()				MUX_SEL&=0xFD		//�رտ��Ź�
#define	WDT_RST()				MUX_SEL|=0x01		//ι��

//ϵͳ��Ƶ��1ms��ʱ��ֵ����
#define FOSC     				206438400UL
#define T1MS    				(65536-FOSC/12/1000)





//app setting parsmetes config
#define CFG_SYS_SLEEP_TIME  180 //3min,unit 1s  


//��������
//��״����
typedef enum {
	SHAPE_TYPE_POINT = 0x0001,//��һ��1���صĵ�
	SHAPE_TYPE_LINE = 0x0002, //�˵�����
	SHAPE_TYPE_RECT = 0x0003,//������
	SHAPE_TYPE_FILL_RECT = 0x0004,//��������
	SHAPE_TYPE_AREA_COPY = 0x0006,//�������򿽱�
	SHAPE_TYPE_VER_LINE =  0x0009//Ƶ��,��ʵ���Ǵ�ֱ��
}SHAPE_TYPE;

//����״������
typedef struct{
	u16 vp;//����һ��vp��ַд����״,��Ҫ�û�������Ӧ��ֵ
	u16 shape_type;//��״����,��Ҫ�û�������Ӧ��ֵ
	u16 shape_num;//������״�ĸ���,�ڲ�����ֱ�ӹ̶�Ϊ1��
	u16 x;//���x����,��Ҫ�û�������Ӧ��ֵ
	u16 y;//���y����,��Ҫ�û�������Ӧ��ֵ
	u16 color;//�����ɫ,��Ҫ�û�������Ӧ��ֵ
	u16 end_flag;//�������,�ڲ�����ֱ�ӹ̶�Ϊ0xff00
}SHAPE_DATA_POINT;

//�˵�������״���߶���״������
typedef struct{
	u16 vp;//����һ��vp��ַд����״,��Ҫ�û�������Ӧ��ֵ
	u16 shape_type;//��״����,��Ҫ�û�������Ӧ��ֵ
	u16 shape_num;//������״�ĸ���,�ڲ�����ֱ�ӹ̶�Ϊ1��
	u16 color;//�ߵ���ɫ,��Ҫ�û�������Ӧ��ֵ
	u16 x0;//��һ�����x����,��Ҫ�û�������Ӧ��ֵ
	u16 y0;//��һ�����y����,��Ҫ�û�������Ӧ��ֵ
	u16 x1;//�ڶ������x����,��Ҫ�û�������Ӧ��ֵ
	u16 y1;//�ڶ������y����,��Ҫ�û�������Ӧ��ֵ
	u16 end_flag;//�������,�ڲ�����ֱ�ӹ̶�Ϊ0xff00
}SHAPE_DATA_LINE;

//���λ���������
typedef struct{
	u16 vp;//����һ��vp��ַд����״,��Ҫ�û�������Ӧ��ֵ
	u16 shape_type;//��״����,��Ҫ�û�������Ӧ��ֵ
	u16 shape_num;//������״�ĸ���,�ڲ�����ֱ�ӹ̶�Ϊ1��
	u16 xs;//���Ͻǵ�x����,��Ҫ�û�������Ӧ��ֵ
	u16 ys;//���Ͻǵ�y����,��Ҫ�û�������Ӧ��ֵ
	u16 xe;//���½ǵ�x����,��Ҫ�û�������Ӧ��ֵ
	u16 ye;//���½ǵ�y����,��Ҫ�û�������Ӧ��ֵ
	u16 color;//�߻��������ɫ,��Ҫ�û�������Ӧ��ֵ
	u16 end_flag;//�������,�ڲ�����ֱ�ӹ̶�Ϊ0xff00
}SHAPE_DATA_RECT;
typedef SHAPE_DATA_RECT	 SHAPE_DATA_FILL_RECT;
	
//�������򿽱�
typedef struct{
	u16 vp;//����һ��vp��ַд����״,��Ҫ�û�������Ӧ��ֵ
	u16 shape_type;//��״����,��Ҫ�û�������Ӧ��ֵ
	u16 shape_num;//������״�ĸ���,�ڲ�����ֱ�ӹ̶�Ϊ1��
	u16 pic_id;//����id,��������һ��������ȥ��������,��Ҫ�û�������Ӧ��ֵ
	u16 xs;//�����������Ͻǵ�x����,��Ҫ�û�������Ӧ��ֵ
	u16 ys;//�����������Ͻǵ�y����,��Ҫ�û�������Ӧ��ֵ
	u16 xe;//�����������½ǵ�x����,��Ҫ�û�������Ӧ��ֵ
	u16 ye;//�����������½ǵ�y����,��Ҫ�û�������Ӧ��ֵ
	u16 x;//ճ������ǰ�����x����
	u16 y;//ճ������ǰ�����y����
	u16 end_flag;//�������,�ڲ�����ֱ�ӹ̶�Ϊ0xff00
}SHAPE_DATA_AREA_COPY;

//Ƶ��,��ֱ��
typedef struct{
	u16 vp;//����һ��vp��ַд����״,��Ҫ�û�������Ӧ��ֵ
	u16 shape_type;//��״����,��Ҫ�û�������Ӧ��ֵ
	u16 shape_num;//������״�ĸ���,�ڲ�����ֱ�ӹ̶�Ϊ1��
	u16 color;//�ߵ���ɫ,��Ҫ�û�������Ӧ��ֵ
	u16 x0;//x����,��Ҫ�û�������Ӧ��ֵ
	u16 y0s;//��ʼy����,��Ҫ�û�������Ӧ��ֵ
	u16 y0e;//��ֹy����,��Ҫ�û�������Ӧ��ֵ
	u16 end_flag;//�������,�ڲ�����ֱ�ӹ̶�Ϊ0xff00
}SHAPE_DATA_VER_LINE;


typedef struct
{
	short door;
	short lock;
	short set_dc1;
	short set_dc2;
	short set_dc3;
	short set_ac1;
	short set_ac2;
	short set_ac3;
	short set_acex;
	short adc_per;
	short motor_position;
	short motor_state;
	short motor_sensor1;
	short motor_sensor2;
	short motor_flag;
}SysDataDef;

extern SysDataDef str_sys;

typedef enum
{
  FSM_INIT = 0, 
	FSM_READY,
	FSM_CLOSE,
	FSM_OPEN,
	FSM_START,
	FSM_RUN,
	FSM_PUSH,
	FSM_PAUSE,
	FSM_UP,
	FSM_STOP,
	FSM_END,
}FSM_StateType;         //״̬���ṹ��


//��������
void sys_init(void);
void sys_delay_about_ms(u16 ms);
void sys_delay_about_us(u8 us);
void sys_delay_ms(u16 ms);
void sys_read_vp(u16 addr,u8* buf,u16 len);
void sys_write_vp(u16 addr,u8* buf,u16 len);
void sys_draw_shape(u16 * shape_data);
void sys_disp_page(u16 page);
u16 sys_read_disp_page(void);
void sys_enable_speaker(u16 enable);
void sys_speaker_work(u16 timer);//unit 8ms
void sys_setdis_light(u16 light_val);
void sys_readflash(u16 addr,u8*buf,u16 num);
void sys_wirteflash(u16 addr,u8*buf,u16 num);
#endif


