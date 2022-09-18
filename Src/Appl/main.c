#include "Platform_Types.h"
#include "Mcu_Hw.h"

//Mcal header files
#include "McalHeaders.h"

//Appl header files
#include "LedControl.h"



#define T_ON_SEC    5U
#define T_OFF_SEC   1U


int main (void)
{	
  IntCrtl_Init() ;	       // Configure Exceptions controls
  SysCtrl_ClockInit() ;   // Configure System clock
	Port_Init() ;          // configure MCU ports
	Systick_Init() ;      //intialize Systick timer 

	LedControl_TicksType TicksON  = (T_ON_SEC  *1000 ) / SystickCfg.TickFreq ;
	LedControl_TicksType TicksOFF = (T_OFF_SEC *1000 ) / SystickCfg.TickFreq ;
	
  while(1)
		{
		      Led_control(TicksON , TicksOFF) ;
   }	

}
