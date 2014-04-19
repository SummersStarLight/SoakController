#include <reg52.h>
#include <position.h>
#include <parameter.h>
#include <basefunc.h>

//sbit sensorPositon = P3^4; //��е�۶�λ������
//��е�۶�λ������
#define sensorPositon P3


uchar sensorPosiCheck = 0; //��е��Aλ�ü���־λ 
							//0��û�и�Ӧ��û�е͵�λ״̬
							//1����⵽�͵�λ�����ӳ�״̬
							//2���ȴ��͵�λ�ͷŽ�����ʱ
							//3�����͵�λȷʵ�ͷ� 

uchar getPositonBySensor() //���ݴ�������ȡ��е��λ��
{
	if(sensorPositon == 0xFE) 	//����
	{
		return 	0;
	}
	else if(sensorPositon == 0xFD) //һ�Ų�
	{
		return 	2;
	}
	else if(sensorPositon == 0xFB)	 //���Ų�
	{
		return 	4;
	}
	else if(sensorPositon == 0xF7)	//���Ų�
	{
		return 	6;
	}
	else if(sensorPositon == 0xEF)	 //�ĺŲ�
	{
		return 	8;
	}
	else if(sensorPositon == 0xDF)	  //��Ų�
	{
		return 	10;
	}
	else if(sensorPositon == 0xBF)	 //���Ų�
	{
		return 	12;
	}
	else if(sensorPositon == 0x7F)	//����
	{
		return 	14;
	}
	else
	{
		//����������
		runMode = ManualMode;
		return 100;
	}	
}

void maniPosition(void) //��е�۶�λ
{
	uchar  getPositonBySensorValue = 0;
	//��е��Aλ�ü��
	if(sensorPosiCheck==0)
	{
		if(sensorPositon != 0xFF)
		{
			sensorPosiCheck = 1;
		}
	}
	else if(sensorPosiCheck==1)
	{
		if(sensorPositon != 0xFF)
		{
			if(drivingDirect == DGoOutfall)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition = getPositonBySensor();
			}
			else if (drivingDirect == DGoEntrance)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition = getPositonBySensor();	
			}
			sensorPosiCheck = 2;
		}
		else
		{
			//�����ź�ֱ���ͷ�
			sensorPosiCheck = 0;
		}
	}
	else if(sensorPosiCheck==2)
	{
		if(sensorPositon == 0xFF)
		{
			sensorPosiCheck = 3;
		}	
	}
	else
	{
		if(sensorPositon == 0xFF)
		{
			if(drivingDirect == DGoOutfall)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition++;
				displayFlag = 1;
				if(manipulator.currentPosition>14)
				{
					manipulator.currentPosition = 14;
				}
			}
			else if (drivingDirect == DGoEntrance)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition--;
				displayFlag = 1;
				if(manipulator.currentPosition>200)
				{
					manipulator.currentPosition = 0;
				}	
			}
			sensorPosiCheck = 0;
		}
	}
}
