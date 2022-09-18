/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dio.h
 *       Module:  Dio
 *
 *  Description:  header file for Port Module     
 *  
 *********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
#define NUM_OF_PORTS                 6 

 //Port number
 
#define DIO_PORTA                   0
#define DIO_PORTB                   1
#define DIO_PORTC                   2
#define DIO_PORTD                   3
#define DIO_PORTE                   4
#define DIO_PORTF                   5

 
//Channel IDs
 
#define DIO_AP0                     0
#define DIO_AP1                     1
#define DIO_AP2                     2
#define DIO_AP3                     3
#define DIO_AP4                     4
#define DIO_AP5                     5
#define DIO_AP6                     6
#define DIO_AP7                     7

#define DIO_BP0                     8
#define DIO_BP1                     9
#define DIO_BP2                     10
#define DIO_BP3                     11
#define DIO_BP4                     12
#define DIO_BP5                     13
#define DIO_BP6                     14
#define DIO_BP7                     15

#define DIO_CP0                     16
#define DIO_CP1                     17
#define DIO_CP2                     18
#define DIO_CP3                     19
#define DIO_CP4                     20
#define DIO_CP5                     21
#define DIO_CP6                     22
#define DIO_CP7                     23

#define DIO_DP0                     24
#define DIO_DP1                     25
#define DIO_DP2                     26
#define DIO_DP3                     27
#define DIO_DP4                     28
#define DIO_DP5                     29
#define DIO_DP6                     30
#define DIO_DP7                     31


#define DIO_EP0                     32
#define DIO_EP1                     33
#define DIO_EP2                     34
#define DIO_EP3                     35
#define DIO_EP4                     36
#define DIO_EP5                     37
#define DIO_EP6                     38
#define DIO_EP7                     39

#define DIO_FP0                     40
#define DIO_FP1                     41
#define DIO_FP2                     42
#define DIO_FP3                     43
#define DIO_FP4                     44
#define DIO_FP5                     45
#define DIO_FP6                     46
#define DIO_FP7                     47



// Channel Levels

#define DIO_LEVEL_LOW                0
#define DIO_LEVEL_HIGH               1






/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
   
	

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
typedef uint8  Dio_PortType      ;       // 0 -5 [ PORTA , PORTB , PORTC , PORTD , PORTE , PORTF]
typedef uint8  Dio_ChannelType   ;      // 0-7 [43 pins]  
typedef uint8  Dio_LevelType     ;     // LOW - HIGH
typedef uint8  Dio_PortLevelType ;     // 0-255 


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId , Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId , Dio_PortLevelType Level);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
 
#endif  /* DIO_H*/

/**********************************************************************************************************************
 *  END OF FILE: Dio.h
 *********************************************************************************************************************/
