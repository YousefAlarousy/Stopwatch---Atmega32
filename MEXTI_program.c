/******************************************************/
/******************************************************/
/******************************************************/
/************* Author : YousefAlarousy ****************/
/************* Layer  : MCAL           ****************/
/************* Module : EXTI           ****************/
/************* Version : 1.00          ****************/
/************* Date   : 8/8/2023       ****************/
/******************************************************/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "MACROS.h"
#include "MEXTI_register.h"
#include "MEXTI_interface.h"
#include "MEXTI_private.h"
#include "MEXTI_config.h"


void (*INT0_ISR)(void)=NULL;
void (*INT1_ISR)(void)=NULL;
void (*INT2_ISR)(void)=NULL;


void MEXTI_voidInit0()
{
	/*Check interrupt sense mode*/
#if INT0_SENSE == RISING
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE == FALLING
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#else
#error"Wrong INT0 Sense Configuration"
#endif
	SET_BIT(GICR,GICR_INT0);
}
void MEXTI_voidInit1()
{
	/*Check interrupt sense mode*/
#if INT1_SENSE == RISING
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE == FALLING
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#else
#error"Wrong INT1 Sense Configuration"
#endif
	SET_BIT(GICR,GICR_INT1);
}
void MEXTI_voidInit2()
{
	/*Check interrupt sense mode*/
#if INT2_SENSE == RISING
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE == FALLING
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error"Wrong INT1 Sense Configuration"
#endif
	SET_BIT(GICR,GICR_INT2);
}

void MEXTI_voidSetSenseControl(u8 Copy_u8INT,u8 Copy_u8SenseControl)
{
	if (Copy_u8INT==INT0)
	{
		switch(Copy_u8SenseControl)
		{
		case RISING : SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);break;
		case FALLING : CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);break ;
		case ON_CHANGE : SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);break ;
		default : break ;
		}
		SET_BIT(GICR,GICR_INT0);
	}
	else if (Copy_u8INT==INT1)
	{
		switch(Copy_u8SenseControl)
		{
		case RISING : SET_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);break;
		case FALLING : CLR_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);break ;
		case ON_CHANGE : SET_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);break ;
		default : break ;
		}
		SET_BIT(GICR,GICR_INT1);
	}
	else if(Copy_u8INT==INT2)
	{
		switch(Copy_u8SenseControl)
		{
		case RISING : SET_BIT(MCUCSR,MCUCSR_ISC2); break;
		case FALLING : CLR_BIT(MCUCSR,MCUCSR_ISC2);break ;
		default : break ;
		}
		SET_BIT(GICR,GICR_INT2);
	}
}


void MEXTI_voidINT0_SetCallBack(void (*Copy_INT0_ISR)(void))
{
	INT0_ISR=Copy_INT0_ISR ;
}
void MEXTI_voidINT1_SetCallBack(void (*Copy_INT1_ISR)(void))
{
	INT1_ISR=Copy_INT1_ISR ;

}
void MEXTI_voidINT2_SetCallBack(void (*Copy_INT2_ISR)(void))
{
	INT2_ISR=Copy_INT2_ISR ;
}

void __vector_1 (void)  __attribute__((signal));
void __vector_1 (void)
{
	INT0_ISR();
}
void __vector_2 (void)  __attribute__((signal));
void __vector_2 (void)
{
	INT1_ISR();
}
void __vector_3 (void)  __attribute__((signal));
void __vector_3 (void)
{
	INT2_ISR();
}

