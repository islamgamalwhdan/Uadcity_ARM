/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SysTick.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Systick.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static volatile Systick_TicksType currTicks ;  // currTick +=1 every systic timer wrap [ count =1]
static Systick_TicksType desiredTicks ;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Systick_Init(void)     
* \Description     : Intilization of Systic timer by configuration data at Systic_Lcfg                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/
void Systick_Init(void)
{
	/* Disable Timer Until configuration completed */
	
	STCTRL.EN = 0 ; 
	
	/*Write dummy vale to clear systick current reg */
	
	STCURRENT = 0 ; 
	
	/*Select clock source for systick */
	
	STCTRL.CLK_SRC = SystickCfg.ClockSource ;
	
	/*Select disable/enable for systick */
	
	STCTRL.INTEN = SystickCfg.IntrMode  ;	
	
	/* Set Preload value */
	
	//STRELOAD = SystickCfg.TickFreq * SysCtrl_GetSytemClock()  - 1 ;
	STRELOAD = SystickCfg.TickFreq * SystickCfg.SystemClock -1  ;
}


/******************************************************************************
* \Syntax          : void Systick_Start(Systick_TicksType Ticks)    
* \Description     : Start systick timer to count Ticks value                             
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Ticks                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/

void Systick_Start(Systick_TicksType Ticks)
{
	/*Write dummy vale to clear systick current reg */
	
	STCURRENT = 0 ; 
	currTicks = 0 ;
	desiredTicks = Ticks ;
	
	STCTRL.EN = 1 ;       //trigger systick timer now
	
}

/******************************************************************************
* \Syntax          : void Systick_Disable(void) 
* \Description     : Disable systick timer                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                 
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/
void Systick_Disable(void) 
{
	STCTRL.EN = 0 ;
}


/******************************************************************************
* \Syntax          : Systick_TicksType Systick_GetTicksElapsed(void)
* \Description     : Get Number of ticks elapsed from Desired Ticks                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                 
* \Parameters (out): Systick_TicksType                                                     
* \Return value:   : None
*                                                              
*******************************************************************************/
Systick_TicksType Systick_GetTicksElapsed(void)
{
	return currTicks ;
}

/******************************************************************************
* \Syntax          : Systick_TicksType Systick_GetTicksRemaining(void)
* \Description     : Get Number of remaining ticks to reach desired Ticks                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                 
* \Parameters (out): Systick_TicksType                                                     
* \Return value:   : None
*                                                              
*******************************************************************************/
Systick_TicksType Systick_GetTicksRemaining(void)
{
	return desiredTicks - currTicks ;
}


void SysTick_Handler(void)
{
	currTicks ++ ;
}
/**********************************************************************************************************************
 *  END OF FILE: Systick.c
 *********************************************************************************************************************/
