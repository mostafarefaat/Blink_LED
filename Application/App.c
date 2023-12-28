/*-----------INCLUDES-----------*/
#include "App.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/
const Port_ConfigType PortsConfig_array[ACTIVE_PINS_NUM];

const User_data_type g_user_data[CFG_INT_NUM];

const User_pin_data_type g_user_pin_data[CFG_INT_NUM_PIN];

const Gpt_ConfigType user_timer_Config[NUM_OF_TIMERS_Config];

const Clk_user_Config Clk_Config;
/*-----------LOCAL Variables-----------*/

uint16_t Timer_On_sec_user   = 0;
uint16_t Timer_Off_sec_user  = 0;
uint16_t Timer_On_sec				 = 2;
uint16_t Timer_Off_sec 			 = 3;
uint16_t Reset 							 = 0;
uint16_t Confirm 						 = 0;

/*-----------GLOBAL EXTERN VARIABLES-----------*/
extern uint8_t Timer_Handler_served;
extern uint8_t Timer_Stopped;
extern uint8_t SYS_TICK_INT_SERVED;
/*-----------APIs FUNCTIONS DEFINITON-----------*/
void App_init(void)
{
	const Port_ConfigType PortsConfig_array[ACTIVE_PINS_NUM] =  /*PINs 0,4,5,6 Inputs & PIN 1 output*/
	{
		{PORTF,PIN0, PORT_PIN_DEN, NULL, PORT_PIN_INTPUT, PORT_PIN_PUR, NULL, PORT_PIN_CURRENT_2mA},
		
		{PORTF,PIN4, PORT_PIN_DEN, NULL, PORT_PIN_INTPUT, PORT_PIN_PUR, PORT_PIN_LOW, PORT_PIN_CURRENT_2mA},
		
		{PORTF,PIN5, PORT_PIN_DEN, NULL, PORT_PIN_INTPUT, PORT_PIN_PUR, PORT_PIN_LOW, PORT_PIN_CURRENT_2mA},
		
		{PORTF,PIN6, PORT_PIN_DEN, NULL, PORT_PIN_INTPUT, PORT_PIN_PUR, PORT_PIN_LOW, PORT_PIN_CURRENT_2mA},
		
		{PORTF,PIN1, PORT_PIN_DEN, NULL, PORT_PIN_OUTPUT, NULL, PORT_PIN_LOW, PORT_PIN_CURRENT_2mA},
	};
	
	const User_data_type g_user_data[CFG_INT_NUM] = /*Enable Interrupts to Timer_1_A & PORT_F*/
	{
		{Timer_1_A,MAIN_GROUP_0,SUB_GROUP_0},
		{INT_GPIOPORTF,MAIN_GROUP_1,SUB_GROUP_0},
	};
	
	const User_pin_data_type g_user_pin_data[CFG_INT_NUM_PIN] = /*Define interrupt settings on needed PINS*/
	{
		{PORTF, PIN0, EDGE, FALLING_LOW}, /*Timer_On_Count*/
		{PORTF, PIN4, EDGE, FALLING_LOW}, /*Timer_Off_Count*/
		{PORTF, PIN5, EDGE, FALLING_LOW}, /*Confirm*/
		{PORTF, PIN6, EDGE, FALLING_LOW}, /*Reset*/
	};
	/*Config Timer_1_A to be used and enable it's Interrrupt*/  /*THIS IS COMMENTED DUE TO SIMULATION LIMITATIONS UNCOMMENT IT IF YOU HAVE HARDWARE*/
	/*const Gpt_ConfigType user_timer_Config[NUM_OF_TIMERS_Config]= 
	{
		{TIMER1, TIMERA, 16, 256, PERIODIC, DOWN_COUNT, pos_edge, NULL, NULL, TIMER1A_Driver_Handler},
	};*/  
	
	const Clk_user_Config Clk_Config =  /*Config system clk*/
	{
		SYSTEM_CLK, INTERRUPT_ON
	};
	
	
	Port_Init(PortsConfig_array);
	
	IntCtrl_init(g_user_data);
	
	IntCtrl_PIN_Enable(g_user_pin_data);
	
	Gpt_Init(user_timer_Config);
	
	register_systick_cb(SysTick_Driver_Handler);   /*Passing Handler Address to Driver for Call-Back Function*/
	
	Sys_Timer_init(&Clk_Config);
	
	register_gpio_cb(GPIOF_Driver_Handler);        /*Passing Handler Address to Driver for Call-Back Function*/
	
	

}
void App_run(void)
{
		if(!(Timer_On_sec == 0 && Timer_Off_sec == 0))
		{
				Sys_Timer_delay(ceil( (Timer_Off_sec) / ((SysTick_scale)) ));
	
	      Sys_Timer_delay(ceil( (Timer_On_sec) / ((SysTick_scale)) ));
			
				/*Gpt_StartTimer(TIMER1_16_32, TIMERA, Timer_On_sec * 1000);*/
			
				/*Gpt_StartTimer(TIMER1_16_32, TIMERA, Timer_Off_sec * 1000);*/
		}
}
void GPIOF_Driver_Handler(void)
{
	if((Dio_Read_Pin(&(GPIORIS(PORTF)), PIN0)) == 1)      /*Timer_On*/
	{
		Dio_Write_Pin(&(GPIOICR(PORTF)), PIN0, HIGH); //Clear Interrupt Flag
		Timer_On_sec++;

	}
	else if((Dio_Read_Pin(&(GPIORIS(PORTF)), PIN4)) == 1) /*Timer_Off*/
	{
		Dio_Write_Pin(&(GPIOICR(PORTF)), PIN4, HIGH);
		Timer_Off_sec++;
		
	}
	else if((Dio_Read_Pin(&(GPIORIS(PORTF)), PIN5)) == 1)  /*Confirm*/ /*TODO: Confirm button (Needs Hardware)*/
	{
		Dio_Write_Pin(&(GPIOICR(PORTF)), PIN5, HIGH);
		Timer_On_sec  += Timer_On_sec_user;
		Timer_Off_sec +=  Timer_Off_sec_user;
		
	}
	else if((Dio_Read_Pin(&(GPIORIS(PORTF)), PIN6)) == 1)  /*Reset*/  /*TODO: Reset button (Needs Hardware)*/
	{
		Dio_Write_Pin(&(GPIOICR(PORTF)), PIN6, HIGH);
		Timer_On_sec  =  0;
		Timer_Off_sec =  0;
	}
}

void TIMER1A_Driver_Handler(void)
{
	Dio_Toggle_Pin(&(GPIODATA(PORTF)),PIN1);
	Dio_Write_Pin(&(GPTMICR(TIMER1_16_32)), TATOCINT, HIGH);
	Timer_Handler_served = 1;
}

void SysTick_Driver_Handler(void)
{
		//RESET CURRENT VALUE IN STCURRENT REGISTER AND TO CLEAR COUNT FLAG
	Dio_Write_Port(&(STCURRENT), CURRENT_VALUE_RESET);
	Dio_Toggle_Pin(&(GPIODATA(PORTF)),PIN1);
    /*Write code here*/
	SYS_TICK_INT_SERVED = 1;
	
}

