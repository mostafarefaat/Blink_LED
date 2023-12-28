#ifndef LED_H_
#define LED_H_
/*-----------INCLUDES-----------*/
#include "..\..\MCAL\GPIO\GPIO.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs FUNCTIONS DECLARATION-----------*/
void Led_On( uint8_t PORT, uint8_t PIN );
void Led_Off( uint8_t PORT, uint8_t PIN );
void Led_Toggle( uint8_t PORT, uint8_t PIN );

#endif

