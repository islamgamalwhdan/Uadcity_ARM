/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
 //Systick
typedef struct
{
uint32
	        EN        :1  ,
	        INTEN     :1  ,
	        CLK_SRC   :1  ,
	                  :13 ,
	        COUNT     :1  ,
	                  :15 ;
	
}STCTRL_BF;

typedef struct 
{
    uint32 VECACT   :8;
    uint32          :3;
    uint32 RETBASE  :1;
    uint32 VECPEND  :8;
    uint32          :2;
    uint32 ISRPEND  :1;
    uint32 ISRPRE   :1;
    uint32          :1;
    uint32 PENDSTCLR:1;
    uint32 PENDSTSET:1;
    uint32 UNPENDSV :1;
    uint32 PENDSV   :1;
    uint32          :2;
    uint32 NMISET   :1; 
}INTCTRL_BF;
typedef union 
{
    uint32 R;
    INTCTRL_BF B;
}INTCTRL_Tag;

//RCC

typedef struct
{
uint32
  MOSCDIS    :1,
	           :3,
	OSCSRC     :2,
	XTAL       :5,
	BYPASS     :1,
	           :1,
	PWRDN      :1,
	           :3,
	PWMDIV     :3,
	USEPWMDIV  :1,
	           :1,
	USESYSDIV  :1,
	SYSDIV     :4,
	ACG        :1,
	           :4;
	
}RCC_BF ;	

typedef union
{
	uint32 R ;
	RCC_BF B ;
	
}RCC_Tag;	


//RCC2

typedef struct 
{
uint32
	           :4,
	OSCSRC2    :3,
             :4,
  BYPASS2    :1,
	           :1,
	PWRDN2     :1,
	USBPWRDN   :1,
	           :7,	
	SYSDIV2LSB :1,
	SYSDIV2    :6,
	           :1,
	DIV400     :1,
	USERCC2    :1;
	
}RCC2_BF ;	

typedef union
{
     uint32 R  ;
     RCC2_BF B ;
}RCC2_Tag ;



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CORE_PERI_BASE                         0xE000E000
#define RST_CTRL_BASE                          0x400FE000
#define GPIOA_APB_BASE                         0x40004000



#define GPIOB_OFFSET                           0x1000 
#define GPIOC_OFFSET                           0x2000 
#define GPIOD_OFFSET                           0x3000 
#define GPIOE_OFFSET                           0x20000 
#define GPIOF_OFFSET                           0x21000 

//systick
#define STCTRL_OFFSET                          0x10 
#define STRELOAD_OFFSET                        0x14 
#define STCURRENT_OFFSET                       0x18 

#define RCC_OFFSET                             0x60
#define RCC2_OFFSET                            0x70
#define RIS_OFFSET                             0x50
#define RCGCWD_OFFSET                          0x600
#define RCGCGPIO_OFFSET                        0x608
#define PLLMIS_BITOFFSET                       0x6

//GPIO 
#define GPIODATA_OFFSET                        0x000
#define GPIODIR_OFFSET                         0x400
#define GPIOAFSEL_OFFSET                       0x420
#define GPIOPCTL_OFFSET                        0x52C 
#define GPIOCR_OFFSET                          0x524
#define GPIODR2R_OFFSET                        0x500
#define GPIODR4R_OFFSET                        0x504
#define GPIODR8R_OFFSET                        0x508
#define GPIOODR_OFFSET                         0x50C
#define GPIOPUR_OFFSET                         0x510
#define GPIOPDR_OFFSET                         0x514
#define GPIODEN_OFFSET                         0x51C
#define GPIOAMSEL_OFFSET                       0x528

#define GPIOLOCK_OFFSET                        0x520 
#define GPIOCR_OFFSET                          0x524


#define STCTRL                                 (*((volatile STCTRL_BF*) (CORE_PERI_BASE+STCTRL_OFFSET)))
#define STCURRENT                              (*((volatile uint32*)(CORE_PERI_BASE+STCURRENT_OFFSET)))
#define STRELOAD                               (*((volatile uint32*)(CORE_PERI_BASE+STRELOAD_OFFSET)))	
	
#define APINT                                  (*((volatile uint32*)(CORE_PERI_BASE+0xD0C)))
#define INTCTRL                                (*((volatile INTCTRL_Tag*)(CORE_PERI_BASE+0xD04)))
#define RCC                                    (*((volatile RCC_Tag*) (RST_CTRL_BASE+RCC_OFFSET)))	
#define RCC2                                   (*((volatile RCC2_Tag*)(RST_CTRL_BASE+RCC2_OFFSET)))
#define RIS                                    (*((volatile uint32*)(RST_CTRL_BASE+RIS_OFFSET)))     
#define RCGCGPIO                               (*((volatile uint32*)(RST_CTRL_BASE+RCGCGPIO_OFFSET)))

#define VECTKEY_APINT                          0x05FA
#define GPIO_UNLOCK_VALUE                      0x4C4F434B



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
