/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio.c
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
#include "Dio.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define KEIL_SIMULATOR                0

#define GPIODATA_MASKED_ALL           (0xFF <<2)
#define GPIOA_GPIODATA_OFFSET        (GPIOA_APB_BASE+GPIODATA_OFFSET)

#define Bit_Band_Reg(Addr,Bit)        ( ((Addr) & 0xF0000000) + 0x2000000 + (((Addr) &0xFFFFF) << 5) + ((Bit)<<2) )	
#define Bit_Band_Access(Addr , Bit , Value)           (*((volatile uint32 *)Bit_Band_Reg( (Addr),(Bit))) = (Value))

#define REG_READ(Addr)                (*((volatile uint32*)(Addr)))
 						 
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const uint32 Gpio_PortOffset[NUM_OF_PORTS] = 
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
* \Syntax          :  Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)  
* \Description     :  Write digital Level at Channel                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId                  
* \Parameters (out): Dio_LevelType                                                    
* \Return value:   : None
*                                                              
*******************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{

	uint8 port = ChannelId /8 ;
	uint8 pin  = ChannelId %8 ;
	uint8 level ;
	
	uint32 addr = GPIOA_GPIODATA_OFFSET+ Gpio_PortOffset[port] + GPIODATA_MASKED_ALL ;
	
	level = REG_READ(addr) & (1<< pin) ;
	
	return   level ?	DIO_LEVEL_HIGH : DIO_LEVEL_LOW ;
	
}


/******************************************************************************
* \Syntax          :  void Dio_WriteChannel(Dio_ChannelType ChannelId , Dio_LevelType Level)   
* \Description     :  Write digital Level at Channel                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId ,  Level                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId , Dio_LevelType Level) 
	
{


	uint8 port = ChannelId /8 ;
	uint8 pin  = ChannelId %8 ;
	
#if(KEIL_SIMULATOR == 0)	 // Hardware [regular Masking]
	uint32 addr = GPIOA_GPIODATA_OFFSET+ Gpio_PortOffset[port] + ( (1 << pin) <<2) ;
	
	 REG_READ(addr) = Level << pin  ;
#else  
	uint32 addr = GPIOA_GPIODATA_OFFSET+ Gpio_PortOffset[port] + GPIODATA_MASKED_ALL ;
	
	Bit_Band_Access(addr , pin , Level) ;
#endif	
}


/******************************************************************************
* \Syntax          :  void Dio_WritePort(Dio_PortType PortId , Dio_PortLevelType Level)  
* \Description     :  Write digital Level at Port                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PortId ,  Level                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/

void Dio_WritePort(Dio_PortType PortId , Dio_PortLevelType Level)
{

	uint32 addr = GPIOA_GPIODATA_OFFSET + Gpio_PortOffset[PortId] + GPIODATA_MASKED_ALL ;
	
	 REG_READ(addr) = Level   ;

}

/******************************************************************************
* \Syntax          :  Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)  
* \Description     :  Write digital Level at Port                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PortId                   
* \Parameters (out): Dio_PortLevelType                                                      
* \Return value:   : None
*                                                              
*******************************************************************************/


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	 uint32 addr = GPIOA_GPIODATA_OFFSET + Gpio_PortOffset[PortId] + GPIODATA_MASKED_ALL ;
	
	return REG_READ(addr) ;
}



/******************************************************************************
* \Syntax          :  Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)  
* \Description     :  Toggle Channel Level                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId                  
* \Parameters (out): Dio_LevelType                                                    
* \Return value:   : None
*                                                              
*******************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	
	if( Dio_ReadChannel(ChannelId) == DIO_LEVEL_HIGH )
	{
		Dio_WriteChannel(ChannelId ,DIO_LEVEL_LOW );
		return DIO_LEVEL_LOW ;
	}
	else
	{
		Dio_WriteChannel(ChannelId ,DIO_LEVEL_HIGH );
		return DIO_LEVEL_HIGH ;
	}
	
}


/**********************************************************************************************************************
 *  END OF FILE: Dio.c
 *********************************************************************************************************************/
