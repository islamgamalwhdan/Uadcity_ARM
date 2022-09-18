/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SysCtrl.h
 *       Module:  SysCrtl
 *
 *  Description:  header file for SysCrtl Module     
 *  
 *********************************************************************************************************************/
#ifndef SYSCTRL_H
#define SYSCTRL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "SysCtrl_cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PLL_USED              1
#define PLL_NOT_USED          0


#define OSCSRC_MOSC           0
#define OSCSRC_PIOSC          1
#define OSCSRC_PIOSC_4        2
#define OSCSRC_LFIOSC         3
#define OSCSRC_32KHZ          7


#define XTAL_CLOCK_8MHZ       0x0E
#define XTAL_CLOCK_10MHZ      0x10
#define XTAL_CLOCK_12MHZ      0x11
#define XTAL_CLOCK_16MHZ      0x15
#define XTAL_CLOCK_20MHZ      0x18


#define PLL_MAXCLOCK_KHZ      400000UL

#define DEFAULT_SYSTEM_CLOCK  16000UL

//Peripheral gates

#define WDT0_GATE             0
#define WDT1_GATE             1

#define TIMR0_16_32           6
#define TIMR1_16_32           7
#define TIMR2_16_32           8
#define TIMR3_16_32           9
#define TIMR4_16_32           10
#define TIMR5_16_32           11

#define GPIOA_GATE            12
#define GPIOB_GATE            13
#define GPIOC_GATE            14
#define GPIOD_GATE            15 
#define GPIOE_GATE            16
#define GPIOF_GATE            17





/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32 SysCtrl_PeripheralGateType ;
typedef uint32 SysCtr_CLockType ;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const SysCtr_CLockType SystemClock ;
extern const SysCtrl_PeripheralGateType PeriGate_cfg[ACTIVATED_PERPH_GATES] ; 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void SysCtrl_ClockInit(void) ;
SysCtr_CLockType SysCtrl_GetSytemClock(void);
 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: SysCtrl.h
 *********************************************************************************************************************/
