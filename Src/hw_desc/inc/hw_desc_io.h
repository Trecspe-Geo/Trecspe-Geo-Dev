/********************************************************************************************************************
*
*
*
* Copyright (C) 2026 Trecspe.  All rights reserved.
*
********************************************************************************************************************/

/********************************************************************************************************************
* @file		hw_desc_io.h
* @company	Trecspe 
* @author	Armel Kamdem
* @date		30.04.2026
*********************************************************************************************************************
* @brief	Pins initialisations.
*
*		This file initialize all the pins that will be used inside the project.
*
*********************************************************************************************************************
*@remarks
*
********************************************************************************************************************/

#ifndef _IO_H_
#define _IO_H_

/********************************************************************************************************************
*													                                                                                          *
*                                  	I N C L U D E S                                                                 *
*   													                                                                                      *
********************************************************************************************************************/
#include <stdbool.h>
#include "common.h"
/********************************************************************************************************************
*													                                                                                          *
*	                                              D E F I N E S                                                       *
*   													                                                                                      *
*********************************************************************************************************************/
#define PORT_A           0
#define PORT_B           1
#define PORT_C           2
#define PORT_D           3
#define PORT_E           4
#define PORT_F           5

#define PA00             0x01
#define PA01             0x02
#define PA02             0x03
#define PA03             0x04
#define PA04             0x05
#define PA05             0x06
#define PA06             0x07
#define PA07             0x08

#define PB00             0x09
#define PB01             0x0A
#define PB02             0x0B
#define PB03             0x0C
#define PB04             0x0D
#define PB05             0x0E

#define PC00             0x0F
#define PC01             0x10
#define PC02             0x11
#define PC03             0x12
#define PC04             0x13
#define PC05             0x14
#define PC06             0x15
#define PC07             0x16

#define PD00             0x17
#define PD01             0x18
#define PD02             0x19
#define PD03             0x1A
#define PD04             0x1B
#define PD05             0x1C
#define PD06             0x1D
#define PD07             0x1E

#define PE00             0x1F
#define PE01             0x20
#define PE02             0x21
#define PE03             0x22

#define PF00             0x23
#define PF01             0x24
#define PF02             0x25
#define PF03             0x26
#define PF04             0x27
#define PF05             0x28
#define PF06             0x29
#define PF07             0x2A

/********************************************************************************************************************
*													                                                                                          *
*	                                           E N U M E R A T I O N S                                                *
*   										                                                                          			            *
********************************************************************************************************************/

/** 
 * GPIO pins list
 */
enum ioPortPin_tTag
{
  IO_PORT_A_PIN_00 = PA00,    ///< IO port A pin 0
  IO_PORT_A_PIN_01 = PA01,    ///< IO port A pin 1
  IO_PORT_A_PIN_02 = PA02,    ///< IO port A pin 2
  IO_PORT_A_PIN_03 = PA03,    ///< IO port A pin 3
  IO_PORT_A_PIN_04 = PA04,    ///< IO port A pin 4
  IO_PORT_A_PIN_05 = PA05,    ///< IO port A pin 5
  IO_PORT_A_PIN_06 = PA06,    ///< IO port A pin 6
  IO_PORT_A_PIN_07 = PA07,    ///< IO port A pin 7

  IO_PORT_B_PIN_00 = PB00,    ///< IO port B pin 00
  IO_PORT_B_PIN_01 = PB01,    ///< IO port B pin 01
  IO_PORT_B_PIN_02 = PB02,    ///< IO port B pin 02
  IO_PORT_B_PIN_03 = PB03,    ///< IO port B pin 03
  IO_PORT_B_PIN_04 = PB04,    ///< IO port B pin 04
  IO_PORT_B_PIN_05 = PB05,    ///< IO port B pin 05

  IO_PORT_C_PIN_00 = PC00,    ///< IO port C pin 00
  IO_PORT_C_PIN_01 = PC01,    ///< IO port C pin 01
  IO_PORT_C_PIN_02 = PC02,    ///< IO port C pin 02
  IO_PORT_C_PIN_03 = PC03,    ///< IO port C pin 03
  IO_PORT_C_PIN_04 = PC04,    ///< IO port C pin 04
  IO_PORT_C_PIN_05 = PC05,    ///< IO port C pin 05
  IO_PORT_C_PIN_06 = PC06,    ///< IO port C pin 06
  IO_PORT_C_PIN_07 = PC07,    ///< IO port C pin 07

  IO_PORT_D_PIN_00 = PD00,    ///< IO port D pin 00
  IO_PORT_D_PIN_01 = PD01,    ///< IO port D pin 01
  IO_PORT_D_PIN_02 = PD02,    ///< IO port D pin 02
  IO_PORT_D_PIN_03 = PD03,    ///< IO port D pin 03
  IO_PORT_D_PIN_04 = PD04,    ///< IO port D pin 04
  IO_PORT_D_PIN_05 = PD05,    ///< IO port D pin 05
  IO_PORT_D_PIN_06 = PD06,    ///< IO port D pin 06
  IO_PORT_D_PIN_07 = PD07,    ///< IO port D pin 07

  IO_PORT_E_PIN_00 = PE00,    ///< IO port E pin 00
  IO_PORT_E_PIN_01 = PE01,    ///< IO port E pin 01
  IO_PORT_E_PIN_02 = PE02,    ///< IO port E pin 02
  IO_PORT_E_PIN_03 = PE03,    ///< IO port E pin 03

  IO_PORT_F_PIN_00 = PF00,    ///< IO port F pin 00
  IO_PORT_F_PIN_01 = PF01,    ///< IO port F pin 01
  IO_PORT_F_PIN_02 = PF02,    ///< IO port F pin 02
  IO_PORT_F_PIN_03 = PF03,    ///< IO port F pin 03
  IO_PORT_F_PIN_04 = PF04,    ///< IO port F pin 04
  IO_PORT_F_PIN_05 = PF05,    ///< IO port F pin 05
  IO_PORT_F_PIN_06 = PF06,    ///< IO port F pin 06
  IO_PORT_F_PIN_07 = PF07,    ///< IO port F pin 07


  IO_PORT_PIN_MAX
};
typedef enum ioPortPin_tTag  eIoPortPin_t; 


/**
 *  Port list 
 */
enum ioPort_tTag
{
  IO_PORT_A = PORT_A,
  IO_PORT_B = PORT_B,
  IO_PORT_C = PORT_C,
  IO_PORT_D = PORT_D,
  IO_PORT_E = PORT_E,
  IO_PORT_F = PORT_F,

  IO_PORT_MAX 
};
typedef enum ioPort_tTag   ioPort_t; 


/**
 * Select types of gpio
 */
enum gpioAltFunc
{
  GPIO_ALT_FUNC_ID0 = 0,       // EVOUTA
  GPIO_ALT_FUNC_ID1,           // EVOUTB
  GPIO_ALT_FUNC_ID2,           // EVOUTC
  GPIO_ALT_FUNC_ID3,           // EVOUTD
  GPIO_ALT_FUNC_ID4,           // EVOUTE
  GPIO_ALT_FUNC_ID5,           // EVOUTF
 
  GPIO_ALT_FUNC_ID6,           // LUT0
  GPIO_ALT_FUNC_ID7,           // LUT1
  GPIO_ALT_FUNC_ID8,           // LUT2
  GPIO_ALT_FUNC_ID9,           // LUT3

  GPIO_ALT_FUNC_ID10,          // USART0[1:0]
  GPIO_ALT_FUNC_ID11,          // USART1[1:0]
  GPIO_ALT_FUNC_ID12,          // USART2[1:0]
  GPIO_ALT_FUNC_ID13,          // USART3[1:0]

  GPIO_ALT_FUNC_ID14,          // SPI0[1:0]

  GPIO_ALT_FUNC_ID15,          // TWI0[1:0]

  GPIO_ALT_FUNC_ID16,          // TCA0[2:0]

  GPIO_ALT_FUNC_ID16,          // TCB0
  GPIO_ALT_FUNC_ID16,          // TCB1
  GPIO_ALT_FUNC_ID16,          // TCB2
  GPIO_ALT_FUNC_ID16,          // TCB3



  MAX_GPIO_FUNC
};
typedef enum gpioAltFunc gpioAltFunc_t;


/** 
 * port direction 
 */
enum eIoDirection_tTag
{
  IO_DIR_INPUT  = 0,
  IO_DIR_OUTPUT = 1,
  MAX_DIR
};
typedef enum eIoDirection_tTag eIoDirection_t;


/**
 * Enable pull-up or pull-down on selected pin
 */
enum pullUp_tTag
{
  PULL_NONE = 0,
  PULL_UP   = 1,
  MAX_PULL
};
typedef enum pullUp_tTag  ePullUp_t;


/**
 * the direction sense of signal 
 */
enum ioDetectionSense_tTag
{
  FALLING_EDGE            = 0,
  RISING_EDGE             = 1,
  RISING_AND_FALLING_EDGE = 2,
  LOW_LEVEL               = 3,
  MAX_EDGE
};
typedef enum ioDetectionSense_tTag eIoDetectionSense_t;

/**
 * the Inverted I/O Enable
 */
enum ioInvertedStatus_tTag
{
  INVEN_ENABLE            = 0,
  INVEN_DESABLE           = 1,
  INVEN_MAX
};
typedef enum ioInvertedStatus_tTag eIoInvertedStatus_t;


/**
 * Pin level
 */
enum pinLevel_tTag
{
  LOW  = 0,
  HIGH = 1,
  MAX_PIN_LEVEL
};
typedef enum pinLevel_tTag ePinLevel_t;

/********************************************************************************************************************
*													                                                                                          *
*	                                          V A R I A B L E                                                         *
*   													                                                                                      *
*********************************************************************************************************************/
typedef void (*cbkFunc_t)(void);
typedef void (*setLevelFunc_t)(void);
typedef bool (*getLevelFunc_t)(void);
typedef uint16_t (*portReadFunc_t)(void);
typedef void (*portWriteFunc_t)(uint16_t);
typedef void (*regFuncbkFunc_t)(eIoDetectionSense_t, ePullUp_t, cbkFunc_t);


/********************************************************************************************************************
 *                                                                                                                  *
 *                                               S T R U C T U R E S                                                *
 *                                                                                                                  *
 *******************************************************************************************************************/

/**
 * structure for definition of pins
 */
struct __attribute__((packed)) dio_tTag  
{
  eIoPortPin_t     ePin;                    /* The pin to use */
  eIoDirection_t   eDirection;              /* The Direction of the pin */
  ePullUp_t        ePullUp;                 /* Enable internal pull up resistor */
  getLevelFunc_t   pfbGetLevel;             /* Get either the pin is ON or OFF */
  setLevelFunc_t   pfvLevelOn;              /* set the pin to ON */
  setLevelFunc_t   pfvLevelOff;             /* set the pin to OFF */
  setLevelFunc_t   pfvToggle;               /* set the pin to either ON or OFF */
  void (*pfvSetFunc)(struct dio_tTag*);     /* This function must be use only after when pin is modified */
};
typedef struct dio_tTag sDio_t;


/**
 * structure for GPIO interrupt
 */
struct __attribute__((packed)) IntIo_tTag  
{
  eIoPortPin_t          ePin;              /* The pin to use */
  eIoDetectionSense_t   eDetectionSense;   /* sense direction of signal */
  ePullUp_t             ePullUp;           /* Enable internal pull up resistor */
  cbkFunc_t             vFunCbk;           /* Call back function */
  regFuncbkFunc_t       pfvRegFunCbk;      /* register function callback */
  cbkFunc_t             pfvUnRegFuncbk;    /* remove the registered function */

};
typedef struct IntIo_tTag sIntIo_t;


/**
 * Structure for managing any port
 */
struct __attribute__((packed)) PortIo_tTag  
{
  ioPort_t              ePort;              /* The port to use */
  uint16_t              u16PortDirection;   /* the direction of port */
  portWriteFunc_t       pfvPortDirSet;      /* set the direction of each pin of port */
  portReadFunc_t        pfu16PortDirGet;    /* set the direction of each pin of port */
  portWriteFunc_t       pfvPortWrite;       /* write on the port */
  portReadFunc_t        pfu16PortRead;      /* read the value of selected port */
  cbkFunc_t             pfvPortToggle;      /* Toggle each pin of selected port */
};
typedef struct PortIo_tTag sPortIo_t;

/********************************************************************************************************************
 *                                                                                                                  *
 *  P U B L I C    F U N C T I O N    I M P L E M E N T A T I O N S                                                 *
 *                                                                                                                  *
 *******************************************************************************************************************/

/**
 * @brief Initialize a pin
 * 
 * @param psDigIO     : Pin object
 * @param ePin        : corresponding pin
 * @param eDirection  : set the direction of pin . 
 * @param ePullUp     : enable internal pull up resistor . 
 */
void vInitPin(sDio_t*          psDigIO, 
              eIoPortPin_t     ePin, 
              eIoDirection_t   eDirection,
			        ePullUp_t        ePullUp);


/**
 * @brief Initialize a port
 * 
 * @param psPortObj         : Port object
 * @param ePort             : corresponding port
 * @param u16PortDirection  : set the direction of each pin of port . 
 */
void vInitPort(sPortIo_t* psPortObj, ioPort_t ePort, uint16_t u16PortDirection);


/**
 * @brief 
 * @param IntObj            :  interrupt pin object
 * @param ePin              :  the pin that will generate the program interrupt 
 *                             the list of pins is as follows: 16 pins maximum. 
 *                             <DIV>
 *                                 <PR>                          
 *                                   <UL> PORT0 : P000, P001, P002 and P004 <BR> </UL>
 *                                   -> PORT1 : P100, P101, P102, P103, P104, P105, P106, P107 <BR>
 *                                   -> PORT2 : P205 <BR>
 *                                   -> PORT4 : P400, P401, P402 <BR>
 *                                 </PR>
 *                             </DIV>
 * @param eDetectionSense   : sense direction of signal , FALLING_EDGE and RISING_EDGE 
 * @param ePullUp           : set this parameter to enable internal pull up resistor or not
 * @param vFunCbk           : user callback
 */
void vIOSetInterrupt(  sIntIo_t* IntObj, eIoPortPin_t ePin);


/********************************************************************************************************************
 *                                                                                                                  *
 *                                          E N D   OF  M O D U L E                                                 *
 *                                                                                                                  *
 *******************************************************************************************************************/

#endif   /* _PIN_CONFIG_GPIO_H_ */


/************************ Copyright (C) 2026 Trecspe  All rights reserved. ****/
 