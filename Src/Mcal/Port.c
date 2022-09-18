/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port.c
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
#include "Port.h"
#include "Port_cfg.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

//#define READ_GPIO_REG(Port,Reg)            (*((__IO_32_)(Port##_APB + Reg##_OFFSET )))
#define ClearBit(Reg , Bit)                      ((Reg) &= ~( 1<< (Bit)))
#define SetBit(Reg , Bit)                         ((Reg) |= 1 << (Bit))
#define ACCESS_GPIO_REG(Port,RegBase)            ( *((volatile uint32*)(GPIOA_APB_BASE +Gpio_offset[Port] + RegBase)) )
	
#define UNLOCK_AND_COMMIT(Port,Pin)\
              do{\
								  /*unlocks (GPIOCR) register for write access*/\
								  /*Enable Write to AFSEL */\
                 ACCESS_GPIO_REG(Port , GPIOLOCK_OFFSET) = GPIO_UNLOCK_VALUE ;\
                 SetBit(ACCESS_GPIO_REG(Port , GPIOCR_OFFSET),Pin);\
               }while(0)	

						 
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const uint32 Gpio_offset[NUM_OF_PORTS] = 
{
	0 , GPIOB_OFFSET , GPIOC_OFFSET , GPIOD_OFFSET , GPIOE_OFFSET , GPIOF_OFFSET
} ;

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
* \Syntax          : void Port_Init(void)       
* \Description     : Initialize GPIO Ports for MCU                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/

void Port_Init(void)
{
	Port_PinType                 pin        ;
	Port_Type                    port       ;
	Port_PinDirectionType        pin_dir    ;
	Port_PinModeType             pin_dio    ;
	Port_PinOutputCurrentType    pin_current ;
	Port_PinInternalAttchType    attach      ;
	uint32 offset ;
	
	
	
	for(uint8 i=0 ; i< ACTIVATED_PIN_SIZE ; i++)
	
	 {
		  pin =  Port_cfg[i].Pin_Num %8 ;
		  port = Port_cfg[i].Pin_Num /8 ;
			pin_dir = Port_cfg[i].Pin_Dir ;
	//A-Direction selction 
		 
	 	 ACCESS_GPIO_REG(port , GPIODIR_OFFSET) |= pin_dir << pin;
		 
		 //DIO pin or alternate pin
		 pin_dio = Port_cfg[i].Pin_mode ;

 //B- Mode selction
      
     UNLOCK_AND_COMMIT(port,pin);		 
		 
		 if(pin_dio == GPIO_DIO )
		 {		 
			 ClearBit( ACCESS_GPIO_REG(port , GPIOAFSEL_OFFSET) ,pin); // Clear AFSEL 
		 }
		 
		 else  // Not DIO [ Alternate pin]
		 {
			 SetBit(ACCESS_GPIO_REG(port , GPIOAFSEL_OFFSET) ,pin) ; // Set AFSEL
			 ACCESS_GPIO_REG(port , GPIOPCTL_OFFSET) |= Port_cfg[i].Pin_mode << (pin<<2) ; //Set Mode field
		 }
		 
 //C- Drive current selection
		  pin_current = Port_cfg[i].Pin_OutCur ; 
		 
		 // select offest
		  offset =   
          		 pin_current == DRIVE_CURRENT_2? GPIODR2R_OFFSET :
		           pin_current == DRIVE_CURRENT_4? GPIODR4R_OFFSET :
          		                                 GPIODR8R_OFFSET ;
		 
  		SetBit( ACCESS_GPIO_REG(port , offset) , pin) ; 
		                            
 //D- Select internal attach
		 
		 attach = Port_cfg[i].Pin_Attach ;
		 if(attach != NONE)
		 {
        UNLOCK_AND_COMMIT(port,pin);
     
  	    offset =   
          		 attach == PULL_UP  ? GPIOPUR_OFFSET :
		           attach == PULL_DOWN? GPIOPDR_OFFSET :
          		                      GPIOODR_OFFSET ;	 
			 
			 SetBit( ACCESS_GPIO_REG(port , offset) , pin) ; 
		 }

 //E - DIO or Anlaog
    
    if( pin_dio == GPIO_DIO )
		{
			UNLOCK_AND_COMMIT(port , pin) ;
			SetBit( ACCESS_GPIO_REG(port , GPIODEN_OFFSET) , pin) ;
		}		
   else
	 {
		 SetBit( ACCESS_GPIO_REG(port , GPIOAMSEL_OFFSET) , pin) ;
	 }		 
		 
	}// for loop	

	
	 
}

/**********************************************************************************************************************
 *  END OF FILE: Port.c.c
 *********************************************************************************************************************/
