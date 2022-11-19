#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
unsigned int flag;

sbit right_ENA=P2^6;	//С���Ҳ�������
sbit right_ENB=P2^1;
sbit right_IN1=P2^2;
sbit right_IN2=P2^3;
sbit right_IN3=P2^4;
sbit right_IN4=P2^5;

sbit left_ENA=P0^5;		//С�����������
sbit left_ENB=P0^6;
sbit left_IN1=P0^1;
sbit left_IN2=P0^2;
sbit left_IN3=P0^3;
sbit left_IN4=P0^4;

sbit left1=P1^3;		//��·����
sbit left2=P1^2;
sbit right2=P1^0;
sbit right1=P1^1;

u8 pwm_t=0;				//��ʱ�����ͳ��
u8 pwm_right_val=0;		//�Ҳ���ʹ��ֵ
u8 pwm_left_val=0;		//�����ʹ��ֵ

void forward()			//ǰ��
{
	right_IN1=1;
	right_IN2=0;
	right_IN3=1;
	right_IN4=0;

	left_IN1=1;
	left_IN2=0;
	left_IN3=1;
	left_IN4=0;

	pwm_left_val=185;
	pwm_right_val=185;
}

void turnLeft1()		//��תС��
{
	right_IN1=1;
	right_IN2=0;
	right_IN3=1;
	right_IN4=0;

	left_IN1=0;
	left_IN2=1;
	left_IN3=0;
	left_IN4=1;

	pwm_left_val=120;
	pwm_right_val=100;
}

void turnLeft2()		//��ת����
{
	right_IN1=1;
	right_IN2=0;
	right_IN3=1;
	right_IN4=0;

	left_IN1=0;
	left_IN2=1;
	left_IN3=0;
	left_IN4=1;

	pwm_left_val=100;
	pwm_right_val=80;				
}

void turnRight1()		//��תС��
{
	right_IN1=0;
	right_IN2=1;
	right_IN3=0;
	right_IN4=1;

	left_IN1=1;
	left_IN2=0;
	left_IN3=1;				 
	left_IN4=0;

	pwm_left_val=100;
	pwm_right_val=120;
}

void turnRight2()		//��ת����
{
	right_IN1=0;
	right_IN2=1;
	right_IN3=0;
	right_IN4=1;

	left_IN1=1;
	left_IN2=0;
	left_IN3=1;
	left_IN4=0;

	pwm_left_val=80;
	pwm_right_val=100;
}

void stop()				//ֹͣ
{
	right_IN1=0;
	right_IN2=0;
	right_IN3=0;
	right_IN4=0;

	left_IN1=0;
	left_IN2=0;
	left_IN3=0;
	left_IN4=0;
}

void follow()			//���ݺ���Ĳ�ͬ���ѭ��
{
	if((right2 == 0)&&(right1 == 0)&&(left1 == 0)&&(left2 == 0)
		||(right2 == 1)&&(right1 == 1)&&(left1 == 1)&&(left2 == 1)
		||(right2 == 1)&&(right1 == 0)&&(left1 == 0)&&(left2 == 1))
	{
		flag = 0;
	}
	if((right2 == 1)&&(right1 ==0)&&(left1 == 0)&&(left2 == 0))
	{
		flag = 1;
	}
	if((right2 == 0)&&(right1 == 0)&&(left1 == 0)&&(left2 == 1))
	{
		flag = 2;
	}
	if((right2 == 0)&&(right1 == 0)&&(left1 == 1)&&(left2 == 0)
		||(right2 == 0)&&(right1 == 0)&&(left1 == 1)&&(left2 == 1))
	{
		flag = 3;
	}
	if((right2 == 0)&&(right1 == 1)&&(left1 == 0)&&(left2 == 0)
		||(right2 == 1)&&(right1 == 1)&&(left1 == 0)&&(left2 == 0))
	{
		flag = 4;
	}

	switch(flag)
	{
		case 0:forward();break;
		
		case 1:stop();turnRight1();break;
		
		case 2:stop();turnLeft1();break;
		
		case 3:stop();turnLeft2();break;
		
		case 4:stop();turnRight2();break;

		default:stop();break;
	}

}

void main()
{
	TMOD=0x02;			//��ʱ��ģʽ���ò�����ʼֵ���򿪶�ʱ�����ж�				                       
	TH0=220;              
	TL0=220;
	TR0=1;
	ET0=1;
	EA=1;

	while(1)
	{
		follow();	
	}

}

void time0() interrupt 1
{
	if(pwm_t >=256)					//ռ�ձȷ�Ϊ256�ݣ������200�Ͳ���ת
		pwm_t=20;
	if(pwm_t < pwm_left_val)
		left_ENA=left_ENB=0;
	else
		left_ENA=left_ENB=1;
	if(pwm_t < pwm_right_val)
		right_ENA=right_ENB=0;
	else
		right_ENA=right_ENB=1;
	pwm_t++;
}
