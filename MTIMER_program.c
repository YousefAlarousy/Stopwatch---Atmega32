/******************************************************/
/******************************************************/
/******************************************************/
/************* Author : YousefAlarousy ****************/
/************* Layer  : MCAL           ****************/
/************* Module : Timer          ****************/
/************* Version : 1.00          ****************/
/************* Date   : 13/8/2023      ****************/
/******************************************************/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "MACROS.h"

#include "MTIMER_interface.h"
#include "MTIMER_private.h"
#include "MTIMER_register.h"
#include "MTIMER_config.h"


void (*Timer0_PF_OVF)(void)=NULL ;
void (*Timer0_PF_CMP)(void)=NULL ;


void MTIMER0_voidInit()
{
	/****Mode Selection****/
#if TIMER0_MODE==TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_TOIE0); // Overflow Interrupt enable

#elif TIMER0_MODE==TIMER0_CTC_MODE
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_OCIE0); // Compare Match Interrupt enable
#else
#error "Wrong TIMRT0 Mode Configuration"
#endif

	/*Prescaler Selection */
#if TIMER0_PRESCALER==TIMER0_NO_PRESCALER
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif  TIMER0_PRESCALER==TIMER0_8_PRESCALER
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif  TIMER0_PRESCALER==TIMER0_64_PRESCALER
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif  TIMER0_PRESCALER==TIMER0_256_PRESCALER
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#elif  TIMER0_PRESCALER==TIMER0_1024_PRESCALER
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#else
#error"Wrong Timer0 Prescaler Selection"
#endif


}
void MTIMER0_voidDisable()
{
	/*No Clock Source*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}

void MTIMER0_voidPreload(u8 Copy_u8Preload)
{
	TCNT0=Copy_u8Preload ;
}

void MTIMER0_voidCompMatchValue(u8 Copy_u8ComMatchValue)
{
	OCR0=Copy_u8ComMatchValue ;
}

void MTIMER0_voidSetCallBack_OVF(void (*Copy_pf)(void) )
{
	Timer0_PF_OVF=Copy_pf ;
}
void MTIMER0_voidSetCallBack_CMP(void (*Copy_pf)(void) )
{
	Timer0_PF_CMP=Copy_pf ;
}

void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	if (Timer0_PF_OVF != NULL)
	{
		Timer0_PF_OVF() ;
	}
}
void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	if (Timer0_PF_CMP != NULL)
	{
		Timer0_PF_CMP() ;
	}
}
