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
#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

void MTIMER0_voidInit();
void MTIMER0_voidDisable();
void MTIMER0_voidPreload(u8 Copy_u8Preload);
void MTIMER0_voidCompMatchValue(u8 Copy_u8ComMatchValue);
void MTIMER0_voidSetCallBack_OVF(void (*Copy_pf)(void) );
void MTIMER0_voidSetCallBack_CMP(void (*Copy_pf)(void) );



#endif /* MTIMER_INTERFACE_H_ */
