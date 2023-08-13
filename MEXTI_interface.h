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
#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_


#define RISING			1
#define FALLING			2
#define ON_CHANGE		3

#define INT0      1
#define INT1      2
#define INT2      3

void MEXTI_voidINT0_SetCallBack();
void MEXTI_voidINT1_SetCallBack();
void MEXTI_voidINT2_SetCallBack();

/**** PreBuild Configuration****/
void MEXTI_voidInit0();
void MEXTI_voidInit1();
void MEXTI_voidInit2();

/**** PostBuild Configuration****/
void MEXTI_voidSetSenseControl(u8 Copy_u8INT,u8 Copy_u8SenseControl);






#endif /* MEXTI_INTERFACE_H_ */
