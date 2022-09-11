/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	
#define GROUP_XXX                      4                                          //Group priority[0-7] , sub-group[0]
#define GROUP_XXY                      5                                          //Group priority[0-3] , sub-group[0-1]
#define GROUP_XYY                      6                                          //Group priority[0-1] , sub-group[0-3]
#define GROUP_YYY                      7                                          //Group priority[0]   , sub-group[0-7]

#define PRIORITY_BITS                  3                                           //No. of priority bits
#define PRIBYTE_RESV_BITS             (8 - PRIORITY_BITS)                          //PRIx Reserved bits

#define NVIC_PRIORITY_BASE            ((volatile uint8 *)(CORE_PERI_BASE + 0x400)) // Accessing it byte by byte
#define NVIC_IRQENABLE_BASE           ((volatile uint8 *)(CORE_PERI_BASE + 0x100)) // Accessing it byte by byte
	


#define IntCtrl_SetPriorityGrouping(Irqn , Gr , Sb)\
        ( NVIC_PRIORITY_BASE[Irqn]  = (uint8)( (( (Gr)<<(GROUP_TYPE - GROUP_XXX )) | (Sb) ) << PRIBYTE_RESV_BITS) )

#define IntCtrl_EnableIRQ(Irqn)\
        ( NVIC_IRQENABLE_BASE[ (Irqn) >> 3] |= 1<< ( (Irqn) % 8 )  )
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void)
{

	/* Configure Grouping\SubGrouping System in APINT register in SCB*/
	
	       /* Note : writing on this register must be in WORD [32-bits] access */
	
    APINT = (APINT & 0x0000FFFF)|            //Read last 16-bits value
	            ((VECTKEY_APINT << 16) |       //Write VECTKEY
                      	(GROUP_TYPE << 8)) ; //Choose Prority grouping type
    
    /* Assign Group\Subgroup priority in NVIC Registers*/  
		for(uint8 i =0 ; i < NVIC_IQR_ACTIVE_NO  ; i++)
	{
		uint8 irqN      = IRQ_Cfg[i].IRQn ;
		uint8 group     = IRQ_Cfg[i].Group_Pr;
		uint8 subGroup  = IRQ_Cfg[i].SubGroup_Pr ;
		
		IntCtrl_SetPriorityGrouping(irqN , group  , subGroup) ;
	
  /* Enable\Disable  Registers */
		
		IntCtrl_EnableIRQ(irqN) ;
		
	}

	


	

}

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
