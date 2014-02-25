/***************************************************************************/
// ������ϴ�豸������
// ģ�飺������	
// �ļ���main.c
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�������
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#include <reg52.h>
//#include <STC12C5A60S2.H>
#include <basefunc.h>
#include <ra8806.h>
#include <parameter.h>
#include <timer.h>

/***************************************************************************/
// ��������	
/***************************************************************************/
//sbit OUT_PUT = P3^7; //���ڲ������
uchar currentTP=0; //���ڴ����������� 

/***************************************************************************/
// ��ʾˢ�º���
// ��������
// ����ֵ����	
/***************************************************************************/
void switchDisplay()
{
	switch(displayMode)
	{
		case MainDisplayMode:
			MainDisplay(0);
		break;
		case Setting:
			SettingDisplay(0);
		break;
		case SettingSaved:
			SettingDisplay(1);
		break;
		case PowerOffing:
			MainDisplay(1);
		break;
		case PowerOffed:
			MainDisplay(2);
		break;
		default:
		break;
	}	
}

/***************************************************************************/
// ����ҳ���ʼ������
// ��������
// ����ֵ����	
/***************************************************************************/
void initSettingPage()
{
	uchar i;
	for(i=0; i<8; i++)
	{
		cistern[i].perSettingTime = cistern[i].settingTime;
		cistern[i].isCurrentlSetting = 0;
	}
	cistern[1].isCurrentlSetting = 1;
}

/***************************************************************************/
// ����ҳ���ѡ�к���
// ������ѡ�е�ǰ����
// ����ֵ����	
/***************************************************************************/
void touchPadSetChooseCistern(uchar cisternNum)
{
	uchar i;
	for(i=0; i<8; i++)
	{
		cistern[i].isCurrentlSetting = 0;
	}
	cistern[cisternNum].isCurrentlSetting = 1;
}

/***************************************************************************/
// ���üӼ�ʱ�亯��
// ������0��һ����  1��һ����
// ����ֵ����	
/***************************************************************************/
void settingOperationTime(uchar opeartion)
{
	uchar i, cisternNum;
	for(i=0; i<8; i++)
	{
		if(cistern[i].isCurrentlSetting == 1)
		{
			cisternNum = i;
		}
	}
	if(opeartion) //��һ����
	{
		
		cistern[cisternNum].perSettingTime = (cistern[cisternNum].perSettingTime/60 -1)*60;
		if(cistern[cisternNum].perSettingTime > 1800 || cistern[cisternNum].perSettingTime <= 0)
		{
			cistern[cisternNum].perSettingTime = 1800;
		}		
	}
	else
	{
		cistern[cisternNum].perSettingTime = (cistern[cisternNum].perSettingTime/60 +1)*60;
		if(cistern[cisternNum].perSettingTime > 1800)
		{
			cistern[cisternNum].perSettingTime = 60;
		}
	}
}

/***************************************************************************/
// ��������Ӧ����
// ��������
// ����ֵ����	
/***************************************************************************/
void checkTouchPad(uchar tpValue)
{
	switch(tpValue)
	{
		case 0:
			currentTP = 0;
		break;
		case 1:	 //���ý���
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				displayMode = Setting;
				initSettingPage(); //��ʼ�����ý���
				SettingDisplay(0);
			}
		break;
		case 2:	 //���Զ�
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				if(runMode == ManualMode)
					runMode = AutoMode;
				else
					runMode = ManualMode;
				MainDisplay(0);
			}
		break;
		case 3:	 //�°ఴ��
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				displayMode = PowerOffing;
				MainDisplay(1);
			}
		break;
		case 4:	 //ȡ���°�
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				displayMode = MainDisplayMode;
				MainDisplay(0);
			}
		break;
		case 5:	 //һ�Ų�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(1);
				SettingDisplay(0);
			}
		break;
		case 6:	 //���Ų�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(2);
				SettingDisplay(0);
			}
		break;
		case 7:	 //���Ų�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(3);
				SettingDisplay(0);
			}
		break;
		case 8:	 //�ĺŲ�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(4);
				SettingDisplay(0);
			}
		break;
		case 9:	 //��Ų�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(5);
				SettingDisplay(0);
			}
		break;
		case 10:	 //���Ų�ѡ�� 
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				touchPadSetChooseCistern(6);
				SettingDisplay(0);
			}
		break;
		case 11:	 //��һ����
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(70);
				settingOperationTime(0);
				SettingDisplay(0);
			}
		break;
		case 12:	 //��һ����
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(70);
				settingOperationTime(1);
				SettingDisplay(0);
			}
		break;
		case 13:	 //����
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				//Save setting to eeprom
				SettingDisplay(3);
				if(parameter_save())
					SettingDisplay(1);
				else
					SettingDisplay(2);
				delay_ms(1000);
				//SettingDisplay(0);
				displayMode = MainDisplayMode;
				MainDisplay(0);
			}
		break;
		case 14:	 //����
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				displayMode = MainDisplayMode;
				MainDisplay(0);
			}
		break;
		case 15:	 //����
			if(currentTP == 2) 
			{
				TP_Response(tpValue);
				delay_ms(100);
				displayMode = MainDisplayMode;
				MainDisplay(0);
			}
		break;
		default:
			currentTP = 0;
		break;
	}
	//��������������
	if(tpValue > 0 && tpValue < 16)
	{
		currentTP++;	
		delay_ms(10);
	}
	else
	{
		currentTP = 0;
	}
}

/***************************************************************************/
// ������
// ��������
// ����ֵ����	
/***************************************************************************/
void main()
{
	lcd_inital();
	PowerOnDisplay();
	delay_ms(2000);
	parameter_init();
	timer_init();
	Enable_TP();
	Enable_Maunal_TP();
	MainDisplay(0);
	while(1)
	{
		
//		OUT_PUT = ~OUT_PUT;
		checkTouchPad(tp_ManualMode());
		//delay_ms(40);
		if(displayFlag == 1) //����ˢ��
		{
			switchDisplay();
			displayFlag = 0;
		}
		else if(displayFlag == 2) //ˢ�»�е�۶���
		{
			if(displayMode != Setting && displayMode != SettingSaved)
			{
				ManipulatorStatusDisplay();
				displayFlag = 0;
				delay_ms(10);
			}			
		}
	}   
}








