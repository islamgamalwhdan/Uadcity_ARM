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

#define ENABLE_EXTERNAL_IRQN()          (set_PRIMASK(0))
#define ENABLE_SYSTEM_EXCPTIONS()       (set_FAULTMASK(0))
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
 
static __inline  void set_PRIMASK(uint32 priMask)
{
  register uint32 __regPriMask        __asm("primask");
  __regPriMask = (priMask);
}



static __inline void set_FAULTMASK(uint32 faultMask)
{
  register uint32 __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32)1U);
}

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

	/* Enable system and external excptions */
	
	   ENABLE_EXTERNAL_IRQN() ;
	
	  ENABLE_SYSTEM_EXCPTIONS() ;
	
	/* Configure Grouping\SubGrouping System in APINT register in SCB*/
	
	       /* Note : writing on this register must be in WORD [32-bits] access */
	
    APINT = (APINT & 0x0000FFFF)|            //Read last 16-bits value
	            ((VECTKEY_APINT << 16) |       //Write VECTKEY
                      	(GROUP_TYPE << 8)) ; //Choose Prority grouping type
    
    /* Assign Group\Subgroup priority in NVIC Registers for each interrupt*/  
		for(uint8 i =0 ; i < NVIC_IQR_ACTIVE_NO  ; i++)
	{
		uint8 irqN      = IRQ_Cfg[i].IRQn ;
		uint8 group     = IRQ_Cfg[i].Group_Pr;
		uint8 subGroup  = IRQ_Cfg[i].SubGroup_Pr ;
		
		IntCtrl_SetPriorityGrouping(irqN , group  , subGroup) ;
	
  /* Enable\Disable  Registers  At NVIC  */
		
		IntCtrl_EnableIRQ(irqN) ;
		
	}

	
/*1-PRIMASK =0 ;
	//2-FAULTMASK = 0 ;
	//3 - Select Group priority
	//4-set level priorty [ group - sun groub] for each IRQn you want to activate it.
	//5- Enable IRQn at NVIC 
	//6- Enable IRQn at peripherial*/

	

}

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
