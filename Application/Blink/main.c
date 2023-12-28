
/*-----------INCLUDES-----------*/

#include "..\App.h"
/*-----------LOCAL MACROS-----------*/


/*-----------GLOBAL STATIC VARIABLES-----------*/


/*-----------GLOBAL EXTERN VARIABLES-----------*/
int main(void);
/*-----------APIs IMPLEMENTATION-----------*/
																							/*Memory map value for debug 0x40000000, 0x400FFFFF*/
void SystemInit(){}
													
int main(void)
{

	App_init();
			
	while(1)
	{	

		App_run();
	}
}


		

