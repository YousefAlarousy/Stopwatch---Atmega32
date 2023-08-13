#include "STD_TYPES.h"
#include "MACROS.h"
#include "MDIO_interface.h"
#include "HSSD_interface.h"
#include "MTIMER_interface.h"
#include "MGIE_interface.h"
#include "MEXTI_interface.h"
#include "util/delay.h"

u8 Global_Seconds=0 ;
u8 Global_Minutes=0 ;
u8 Global_Hours=0 ;
u8 FLAG=0;

void EnableDigit(u8 Digit);

void Timer0_ISR();

void INT0_Pause();
void EXTI1_Continue();

int main()
{
	Port_voidInit();
	MGIE_voidEnable();

	MEXTI_voidInit0();
	MEXTI_voidInit1();

	MEXTI_voidINT0_SetCallBack(INT0_Pause);
	MEXTI_voidINT1_SetCallBack(EXTI1_Continue);

	MTIMER0_voidInit();
	MTIMER0_voidCompMatchValue(250);
	MTIMER0_voidSetCallBack_CMP(Timer0_ISR);
	while(1)
	{
		if (FLAG==1)
		{
			EnableDigit(1);
			HSSD_voidSendNumber(Global_Seconds/10);
			_delay_ms(5);
			EnableDigit(2);
			HSSD_voidSendNumber(Global_Seconds%10);
			_delay_ms(5);
			EnableDigit(3);
			HSSD_voidSendNumber(Global_Minutes/10);
			_delay_ms(5);
			EnableDigit(4);
			HSSD_voidSendNumber(Global_Minutes%10);
			_delay_ms(5);
			EnableDigit(5);
			HSSD_voidSendNumber(Global_Hours/10);
			_delay_ms(5);
			EnableDigit(6);
			HSSD_voidSendNumber(Global_Hours%10);
			_delay_ms(5);


		}
	}

}

void Timer0_ISR()
{
	static u16 DisplayingTime,Counter=0 ;
	static u8 f=0;
	Counter++ ;
	DisplayingTime++;
	if(DisplayingTime==20) //5msec
	{
		DisplayingTime=0 ;
		f++ ;
		EnableDigit(f);
		switch(f)
		{
		case 2 : HSSD_voidSendNumber(Global_Seconds%10);break;
		case 1 : HSSD_voidSendNumber(Global_Seconds/10);break;
		case 4 : HSSD_voidSendNumber(Global_Minutes%10);break;
		case 3 : HSSD_voidSendNumber(Global_Minutes/10);break;
		case 6 : HSSD_voidSendNumber(Global_Hours%10);break;
		case 5 : HSSD_voidSendNumber(Global_Hours/10);break;
		default:break;
		}
		if(f==6)
		{
			f=0 ;
		}
	}
	if(Counter==4000)//1sec
	{
		Counter=0 ;
		Global_Seconds++ ;
		if(Global_Seconds==60)
		{
			Global_Seconds=0 ;
			Global_Minutes++;
			if(Global_Minutes==60)
			{
				Global_Minutes=0;
				Global_Hours++;
			}
		}
	}
}
void EnableDigit(u8 Digit)
{
	switch(Digit)
	{
	case 2 : HSSD_voidDisable(DIO_PORTB,DIO_PIN0);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN1);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN2);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN3);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN4);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN5);break;

	case 1 : HSSD_voidDisable(DIO_PORTB,DIO_PIN0);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN1);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN2);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN3);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN5);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN4);break;

	case 4 : HSSD_voidDisable(DIO_PORTB,DIO_PIN0);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN1);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN2);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN4);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN5);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN3);break;

	case 3 : HSSD_voidDisable(DIO_PORTB,DIO_PIN0);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN1);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN3);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN4);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN5);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN2);break;

	case 6 : HSSD_voidDisable(DIO_PORTB,DIO_PIN0);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN2);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN3);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN4);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN5);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN1);break;

	case 5 : HSSD_voidDisable(DIO_PORTB,DIO_PIN1);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN2);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN3);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN4);
	HSSD_voidDisable(DIO_PORTB,DIO_PIN5);
	HSSD_voidEnable(DIO_PORTB,DIO_PIN0);break;
	}
}
void INT0_Pause()
{
	MTIMER0_voidDisable();
	FLAG=1 ;
}
void EXTI1_Continue()
{
	MTIMER0_voidInit();
	FLAG=0 ;
}

