/*-----------INCLUDES-----------*/
#include "led.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/		
void Led_On( uint8_t PORT, uint8_t PIN )
{
	Dio_Write_Pin(&(GPIODATA(PORT)), PIN, HIGH);
	
}
void Led_Off( uint8_t PORT, uint8_t PIN )
{
	Dio_Write_Pin(&(GPIODATA(PORT))  , PIN, LOW);
	
}
void Led_Toggle( uint8_t PORT, uint8_t PIN )
{
	Dio_Toggle_Pin(&(GPIODATA(PORT)), PIN);
	
}

