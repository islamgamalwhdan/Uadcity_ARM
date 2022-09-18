/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port.h
 *       Module:  Port
 *
 *  Description:  header file for Port Module     
 *  
 *********************************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port_cfg.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
#define NUM_OF_PORTS                 6 
 //Port number
 
#define PORTA                        0
#define PORTB                        1
#define PORTC                        2
#define PORTD                        3
#define PORTE                        4
#define PORTF                        5

 
//Port pin number
 
#define GPIOA_P0                     0
#define GPIOA_P1                     1
#define GPIOA_P2                     2
#define GPIOA_P3                     3
#define GPIOA_P4                     4
#define GPIOA_P5                     5
#define GPIOA_P6                     6
#define GPIOA_P7                     7

#define GPIOB_P0                     8
#define GPIOB_P1                     9
#define GPIOB_P2                     10
#define GPIOB_P3                     11
#define GPIOB_P4                     12
#define GPIOB_P5                     13
#define GPIOB_P6                     14
#define GPIOB_P7                     15

#define GPIOC_P0                     16
#define GPIOC_P1                     17
#define GPIOC_P2                     18
#define GPIOC_P3                     19
#define GPIOC_P4                     20
#define GPIOC_P5                     21
#define GPIOC_P6                     22
#define GPIOC_P7                     23

#define GPIOD_P0                     24
#define GPIOD_P1                     25
#define GPIOD_P2                     26
#define GPIOD_P3                     27
#define GPIOD_P4                     28
#define GPIOD_P5                     29
#define GPIOD_P6                     30
#define GPIOD_P7                     31


#define GPIOE_P0                     32
#define GPIOE_P1                     33
#define GPIOE_P2                     34
#define GPIOE_P3                     35
#define GPIOE_P4                     36
#define GPIOE_P5                     37
#define GPIOE_P6                     38
#define GPIOE_P7                     39

#define GPIOF_P0                     40
#define GPIOF_P1                     41
#define GPIOF_P2                     42
#define GPIOF_P3                     43
#define GPIOF_P4                     44
#define GPIOF_P5                     45
#define GPIOF_P6                     46
#define GPIOF_P7                     47





//Pin direction type
#define INPUT_PIN_DIRECTION           0
#define OUPUT_PIN_DIRECTION           1




 //alternate functions modes encoding values from Data sheet table 23-5
#define GPIO_DIO                      0 
#define GPIOA_P0_MODE_U0RX            1
#define GPIOA_P0_MODE_CAN1RX          8
#define GPIOF_P0_MODE_U1RTS           1




/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
   
	

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
typedef uint8  Port_Type    ;           // 0 -5 [ PORTA , PORTB , PORTC , PORTD , PORTE , PORTF]
typedef uint8  Port_PinType ;           // 0-7 [43 pins]
typedef uint8  Port_PinDirectionType ;  // 0-1    
typedef uint8  Port_PinModeType ;       // 0-15

typedef enum
{
	NONE    = 0 ,
	PULL_UP     ,
	PULL_DOWN   ,
	OPENDRAIN  
}Port_PinInternalAttchType ;


typedef enum 
{
	DRIVE_CURRENT_2 = 0 ,
	DRIVE_CURRENT_4     ,
	DRIVE_CURRENT_8    
	
}Port_PinOutputCurrentType;


typedef struct
{
	Port_PinType                 Pin_Num  ;
	Port_PinDirectionType        Pin_Dir  ;
  Port_PinModeType             Pin_mode ;
  Port_PinInternalAttchType    Pin_Attach;
  Port_PinOutputCurrentType    Pin_OutCur;  
	
}Port_ConfigType ;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Port_ConfigType Port_cfg [ACTIVATED_PIN_SIZE];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Port_Init(void);
 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Port.h
 *********************************************************************************************************************/
