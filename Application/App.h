#ifndef APP_H_
#define APP_H_
/*-----------INCLUDES-----------*/
#include "..\MCAL\GPIO\GPIO.h"
#include "..\MCAL\INT_CTRL\INTCtrl.h"
#include "..\MCAL\MCU\MCU.h"
#include "..\MCAL\GPTM\GPTM.h"
#include "math.h"

/*-----------LOCAL MACROS-----------*/
#define SysTick_scale 	  0.0000000625
/*-----------GLOBAL STATIC VARIABLES-----------*/


void SysTick_Driver_Handler(void);
void GPIOF_Driver_Handler(void);
void TIMER1A_Driver_Handler(void);
void TIMER0A_Driver_Handler(void);
void WTIMER1B_Driver_Handler(void);

/*-----------GLOBAL EXTERN VARIABLES-----------*/
//extern uint8_t SYS_TICK_INT_SERVED;
/*-----------APIs FUNCTIONS DECLARATION-----------*/
void App_init(void);
void App_run(void);
#endif
