/********************************************************************************************************************
*
*
*
* Copyright (C) 2026 Trecspe .  All rights reserved.
*
********************************************************************************************************************/

/********************************************************************************************************************
* @file		hw_desc_io_ra2e1.c
* @company	Trecspe
* @author	Armel Kamdem
* @date		14.05.2026
*********************************************************************************************************************
* @brief	Pins initialisations.
*
*		This file initialize all the pins that will be used inside the project.
*
*********************************************************************************************************************
*@remarks
*
********************************************************************************************************************/

/********************************************************************************************************************
*													            *
*	I N C L U D E S                                                                                             *
*   													            *
********************************************************************************************************************/
#include "Src/hw_desc/inc/hw_desc_io.h"
#include <avr/io.h>         // AVR device definitions for ATmega4809

/********************************************************************************************************************
*													            *
*	D E F I N E S                                                                                               *
*   													            *
********************************************************************************************************************/
#define PORT_NUM                      (6U)
#define PIN_MAX                       (8U)

#define IO_RESET                      (0U)
#define IO_SET                        (1U)
#define IO_MASK                       (1U)

#define IO_INT_PIN_MAX                (8U)
#define IO_PORT_PIN_OFFSET            (3U)                                        /* Because this mcu is 8 bit*/
#define IO_PORT_PIN_MSK               (0x07U)
#define IO_SENSE_DETECTION_MSk        (0x01)

#define IO_LEVEL_HIGH                 (1U)
#define IO_LEVEL_LOW                  (0U)

#define IO_PORT_TOGGLE_MSK            (0xFFFFUL)
#define IO_PRIORITY                   (3UL)
#define IO_KINT_PRIORITY              IO_PRIORITY        
#define IO_IRQ0_PRIORITY              IO_PRIORITY
#define IO_IRQ1_PRIORITY              IO_PRIORITY
#define IO_IRQ2_PRIORITY              IO_PRIORITY
#define IO_IRQ3_PRIORITY              IO_PRIORITY
#define IO_IRQ4_PRIORITY              IO_PRIORITY
#define IO_IRQ5_PRIORITY              IO_PRIORITY
#define IO_IRQ6_PRIORITY              IO_PRIORITY
#define IO_IRQ7_PRIORITY              IO_PRIORITY


#define IO_IRQ_OFFSET                 (IEL24_IRQn)
#define IO_KINT_CHANNEL               (IEL0_IRQn)
#define IO_IRQ0_CHANNEL               ((IRQn_Type)(0 + IO_IRQ_OFFSET))
#define IO_IRQ1_CHANNEL               ((IRQn_Type)(1 + IO_IRQ_OFFSET))
#define IO_IRQ2_CHANNEL               ((IRQn_Type)(2 + IO_IRQ_OFFSET))
#define IO_IRQ3_CHANNEL               ((IRQn_Type)(3 + IO_IRQ_OFFSET))
#define IO_IRQ4_CHANNEL               ((IRQn_Type)(4 + IO_IRQ_OFFSET))
#define IO_IRQ5_CHANNEL               ((IRQn_Type)(5 + IO_IRQ_OFFSET))
#define IO_IRQ6_CHANNEL               ((IRQn_Type)(6 + IO_IRQ_OFFSET))
#define IO_IRQ7_CHANNEL               ((IRQn_Type)(7 + IO_IRQ_OFFSET))
#define IO_IRQ0_INDEX                 (0)
#define IO_IRQ1_INDEX                 (1 + IO_IRQ0_INDEX)
#define IO_IRQ2_INDEX                 (2 + IO_IRQ0_INDEX)
#define IO_IRQ3_INDEX                 (3 + IO_IRQ0_INDEX)
#define IO_IRQ4_INDEX                 (4 + IO_IRQ0_INDEX)
#define IO_IRQ5_INDEX                 (5 + IO_IRQ0_INDEX)
#define IO_IRQ6_INDEX                 (6 + IO_IRQ0_INDEX)
#define IO_IRQ7_INDEX                 (7 + IO_IRQ0_INDEX)

#define IO_IRQ0_IELSR_MSK             (0x01U)
#define IO_IRQ1_IELSR_MSK             (0x01U)
#define IO_IRQ2_IELSR_MSK             (0x01U)
#define IO_IRQ3_IELSR_MSK             (0x01U)
#define IO_IRQ4_IELSR_MSK             (0x16U)
#define IO_IRQ5_IELSR_MSK             (0x13U)
#define IO_IRQ6_IELSR_MSK             (0x13U)
#define IO_IRQ7_IELSR_MSK             (0x11U)
#define IO_KINT_IELSR_MSK             (0x18U)

#define IO_IELSR_IR_BIT               (16UL)
#define IO_IELSR_IR_MSK               (1UL << IO_IELSR_IR_BIT)

#define IO_PFS_PODR_BIT          	  (0UL)
#define IO_PFS_PODR_MSK          	  (1UL << IO_PFS_PODR_BIT)
#define IO_PFS_PIDR_BIT          	  (1UL)
#define IO_PFS_PIDR_MSK          	  (1UL << IO_PFS_PIDR_BIT)
#define IO_PFS_PDR_BIT           	  (2UL)
#define IO_PFS_PDR_MSK           	  (1UL << IO_PFS_PDR_BIT)
#define IO_PFS_PCR_BIT           	  (4UL)
#define IO_PFS_PCR_MSK           	  (1UL << IO_PFS_PCR_BIT)
#define IO_PFS_ISEL_BIT          	  (14UL)
#define IO_PFS_ISEL_MSK          	  (1UL << IO_PFS_ISEL_BIT)
#define IO_PFS_ASEL_BIT          	  (15UL)
#define IO_PFS_ASEL_MSK          	  (1UL << IO_PFS_ASEL_BIT)
#define IO_PFS_PMR_BIT           	  (16UL)
#define IO_PFS_PMR_MSK           	  (1UL << IO_PFS_PMR_BIT)
#define IO_PFS_PSEL_START_BIT    	  (24UL)
#define IO_PFS_PSEL_MSK(x)       	  ((uint32_t)(x) << IO_PFS_PSEL_START_BIT)
#define IO_KINT_PSEL_MSK         	  IO_PFS_PSEL_MSK(0x08UL)
#define IO_PSEL_IRQ_MSK          	  (1 << IO_PFS_PSEL_START_BIT)

#define IO_KINT_KRTCL_KRMD_BIT        (7U)
#define IO_KINT_KRTCL_KREG_BIT        (0U)
#define IO_KINT_KRM_KIF0_BIT          (0U)
#define IO_KINT_KRM_KIF1_BIT          (1U)
#define IO_KINT_KRM_KIF2_BIT          (2U)
#define IO_KINT_KRM_KIF3_BIT          (3U)
#define IO_KINT_KRM_KIF4_BIT          (4U)
#define IO_KINT_KRM_KIF5_BIT          (5U)
#define IO_KINT_KRM_KIF6_BIT          (6U)
#define IO_KINT_KRM_KIF7_BIT          (7U)

#define IO_IRQCR_IRQMD_BIT            (0U)
#define IO_IRQCR_IRQMD_MSK            (1U << IO_IRQCR_IRQMD_BIT)
#define IO_IRQCR_FCLKSEL_BIT          (4U)
#define IO_IRQCR_FCLKSEL_PCLKB_DIV1   (0  << IO_IRQCR_FCLKSEL_BIT)
#define IO_IRQCR_FCLKSEL_PCLKB_DIV8   (1U << IO_IRQCR_FCLKSEL_BIT)
#define IO_IRQCR_FCLKSEL_PCLKB_DIV32  (2U << IO_IRQCR_FCLKSEL_BIT)
#define IO_IRQCR_FCLKSEL_PCLKB_DIV64  (3U << IO_IRQCR_FCLKSEL_BIT)
#define IO_IRQCR_FCLKSEL_MSK          IO_IRQCR_FCLKSEL_PCLKB_DIV8
#define IO_IRQCR_FLTEN_BIT            (7U) 
#define IO_IRQCR_FLTEN_MSK            (1U << IO_IRQCR_FLTEN_BIT) 

#define IO_PWPR_B0WI_BIT              (7U)
#define IO_PWPR_PFSWE_BIT             (6U)

#define IO_PRWCNTR_WAIT_BIT           (1U)
#define IO_PRWCNTR_WAIT_1_CYCLE_MSK   (0x01U)
#define IO_PRWCNTR_WAIT_2_CYCLE_MSK   (0x02U)
#define IO_PRWCNTR_WAIT_3_CYCLE_MSK   (0x03U)
#define IO_PRWCNTR_WAIT_MSK           IO_PRWCNTR_WAIT_2_CYCLE_MSK

/********************************************************************************************************************
*													                                                                *
*	                                     V A R I A B L E                                                            *
*   													                                                            *
********************************************************************************************************************/

static volatile cbkFunc_t vKintFunCbk [IO_INT_PIN_MAX];
static volatile cbkFunc_t vIRQFunCbk  [IO_INT_PIN_MAX];
static bool bWriteEnable = false;


/********************************************************************************************************************
 *                                                                                                                  *
 *  E X T E R N   F U N C T I O N   D E C L A R A T I O N                                                           *
 *                                                                                                                  *
 *******************************************************************************************************************/

 void vIOInterruptHandler(void);

/********************************************************************************************************************
*													                                                                                          *
*	                           S T A T I C   F U N C T I O N  D E C L A T I O N                                       *
*   													                                                                                      *
********************************************************************************************************************/

/**
 * @brief       This function enable writing on the GPIO port
 */
static void vPinAccessEnable(void);

/**
 * @brief      Compute the port and mask from the pin
 * 
 * @param      u8Mask           : pointer to the mask
 * @param      u8Port           : pointer to the port
 * @param      ePin             : corresponding pin
 */
static void vComputePortAndMaskFromPin(uint8_t *u8Mask, uint8_t *u8Port, eIoPortPin_t ePin);

/**
 * @brief     set the level of pin to high
 * 
 * @param     ePin              : corresponding pin
 * @warning   The pin must have been previously configured as output  
 */
static void vPinSet(eIoPortPin_t ePin);

/**
 * @brief      set the level of pin to low
 * 
 * @param      ePin             : corresponding pin
 * @warning    The pin must have been previously configured as output  
 */
static void vPinClear(eIoPortPin_t ePin);

/**
 * @brief      toggle the pin
 * 
 * @param      ePin             : corresponding pin
 * @warning    The pin must have been previously configured as output  
 *
 */
static void vPinToggle(eIoPortPin_t ePin);

#if !defined(UNUSEDFUNCTION)

/**
 * @brief       This function disable writing on the GPIO port
 */
static void vPinAccessDisable(void);

/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 * @param      ePull            : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */
static void vPinDirInput(eIoPortPin_t ePin, ePullUp_t ePull);

/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 */
static void vPinDirOutput(eIoPortPin_t ePin);

#endif

/**
 * @brief      This function return the state of the 
 * 
 * @param      ePin             : corresponding pin
 */
static bool bPinRead(eIoPortPin_t ePin);

/**
 * @brief       configure the pin as Input or output and enable pull up
 * 
 * @param       ePin             : corresponding pin
 * @param       eDirection       : direction of pin . The direction take two value IO_DIR_INPUT and IO_DIR_OUTPUT
 * @param       ePull            : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */
static void vPinCfg(eIoPortPin_t ePin, eIoDirection_t eDirection, ePullUp_t ePull);

/**
 * 
 * @brief        enable kint interrupt 
 * 
 * @param        eDetectionSense : sense direction of signal , FALLING_EDGE and RISING_EDGE 
 */
static void vKintIntEnable(eIoDetectionSense_t eDetectionSense);

/**
 * @brief        This function initialize kint feature
 * 
 * @param        ePin            : corresponding pin
 * @param        eDetectionSense : sense direction of signal , FALLING_EDGE and RISING_EDGE 
 * @param        ePullUp         : set this parameter to enable internal pull up resistor or nicht
 * @param        vFunCbk         : user callback
 */
static void vKintInit(eIoPortPin_t ePin,  
					  eIoDetectionSense_t eDetectionSense, 
					  ePullUp_t ePullUp,
					  cbkFunc_t vFunCbk);

/**
 * @brief This function uninitialize kint feature on selected pin
 * 
 * @param ePin   corresponding pin
 * @param eDetectionSense  sense direction of signal , FALLING_EDGE and RISING_EDGE 
 * @param ePullUp : set this parameter to enable internal pull up resistor or nicht
 * @param vFunCbk  user callback
 */
static void vKintUnInit(sIntIo_t*   IntObj);

/**
 * @brief        This function initialize kint feature
 *
 * @param        u8Pin           : corresponding pin
 * @param        ePullUp         : set this parameter to enable internal pull up resistor or nicht
 * @param        pfvCbk          : user callback
 */
static void vKintPinEnable(uint8_t  u8Pin,  
					       ePullUp_t ePullUp,
					       cbkFunc_t vFunCbk);

/**
 * @brief This function uninitialize kint feature on selected pin
 *
 * @param u8Pin   corresponding pin
 */
static void vKintPinDisable(uint8_t  u8Pin);

/** @brief       This function enable IRQ0 interrupt on pin P400
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ0Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk); 

/** @brief       This function enable IRQ1 interrupt on pin P205
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ1Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ2 interrupt on pin P002
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ2Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ3 interrupt on pin P004
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ3Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ4 interrupt on pin P402
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ4Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ4 interrupt on pin P401
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ5Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ6 interrupt on pin P000
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ6Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function enable IRQ7 interrupt on pin P001
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ7Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk);

/** @brief       This function disable IRQ0 interrupt on pin P400
  * @return      none
 **/
static void vIRQ0Disable(void);
/** @brief       This function disable IRQ1 interrupt on pin P205
  * @return      none
 **/
static void vIRQ1Disable(void);
/** @brief       This function disable IRQ2 interrupt on pin P002
  * @return      none
 **/
static void vIRQ2Disable(void);
/** @brief       This function disable IRQ3 interrupt on pin P004
  * @return      none
 **/
static void vIRQ3Disable(void);
/** @brief       This function disable IRQ4 interrupt on pin P402
  * @return      none
 **/
static void vIRQ4Disable(void);
/** @brief       This function disable IRQ0 interrupt on pin P401
  * @return      none
 **/
static void vIRQ5Disable(void);
/** @brief       This function disable IRQ0 interrupt on pin P000
  * @return      none
 **/
static void vIRQ6Disable(void);
/** @brief       This function disable IRQ0 interrupt on pin P001
  * @return      none
 **/
static void vIRQ7Disable(void);

/**
 * @brief        key interrupt handler
 */
static void vKintHandler(void);

/** @brief       IRQ0 interrupt is generated in the event of a change of state of pins "P400" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ0InterruptHandler(void);

/** @brief       IRQ1 interrupt is generated in the event of a change of state of pins "P205" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ1InterruptHandler(void);

/** @brief       IRQ2 interrupt is generated in the event of a change of state of pins "P002" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ2InterruptHandler(void);

/** @brief       IRQ3 interrupt is generated in the event of a change of state of pins "P004" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ3InterruptHandler(void);

/** @brief       IRQ4 interrupt is generated in the event of a change of state of pins "P402" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ4InterruptHandler(void);

/** @brief       IRQ5 interrupt is generated in the event of a change of state of pins "P401" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ5InterruptHandler(void);

/** @brief       IRQ6 interrupt is generated in the event of a change of state of pins "P000" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ6InterruptHandler(void);

/** @brief       IRQ7 interrupt is generated in the event of a change of state of pins "P001" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ7InterruptHandler(void);









/*===================================================================================================================
 *        C O N F I G U R E  J U S T  P I N   T H A T  D O  N O T  H A V E  F U N C T I O N     S E T  O N           *
 *   PC2                                                                                                    PC7      *
 *   PC3                                                                                                    PC6      *
 *   PB2                                                                                                    PC5      *
 *   PB3                                                                                                    PC4      *
 * 
 *   PE0                                                                                                    PB5      *                                                                                         
 *   PE1                                                                                                    PB4      *
 *   PE2                                                                                                    PF5 LEDO *
 *   РЕЗ                                                                                                    PF4      *
 *   
 *                                                                                                                   *
 ====================================================================================================================*/

static void vSetOnPA00(void);








/********************************************************************************************************************
*													                                                                                          *
*	                     S T A T I C   F U N C T I O N  I M P L E M E N T A T I O N S                                 *
*   													                                                                                      *
********************************************************************************************************************/



/**
 * @brief      Compute the port and mask from the pin
 * 
 * @param      u8Mask           : pointer to the mask
 * @param      u8Port           : pointer to the port
 * @param      ePin             : corresponding pin
 */
static void vComputePortAndMaskFromPin(uint8_t *u8Mask, uint8_t *u8Port, eIoPortPin_t ePin)
{
  uint8_t u8Index    = 0;                                                      // Init the index , the index open from the pin
  uint8_t u8Bit      = 0;                                                      // Get the bit value from the index 
  uint8_t u8PortVal  = 0;                                                      // Get the port value from the index
  uint8_t u8MaskVal  = 0;                                                      // Get the mask value from the bit value  


  u8Index     = (uint8_t)(ePin - ONE);                                         // Get the index from the pin value
	u8PortVal   = (uint8_t)(u8Index >> IO_PORT_PIN_OFFSET);                      // Get the port from the index value
  u8Bit       = (uint8_t)(u8Index BITAND IO_PORT_PIN_MSK);                     // Get the bit from the index value
	u8MaskVal   = (uint8_t)(IO_MASK << (u8Index - 1));                           // Get the mask from the bit value


  *u8Mask = u8MaskVal;                                                          // Return the mask value
  *u8Port = u8PortVal;                                                          // Return the port value
}



/**
 * @brief     set the level of pin to high
 * 
 * @param     ePin              : corresponding pin
 * @warning   The pin must have been previously configured as output  
 */
static void vPinSet(eIoPortPin_t ePin)
{
  uint8_t u8Port  = 0;                                                  // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                                  // Get the pin mask from the index 
  
  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);

	switch (u8Port)
	{
		case IO_PORT_A:
			PORTA.OUTSET = u8Mask;
			break;

    case IO_PORT_B:
			PORTB.OUTSET = u8Mask;
			break;  

    case IO_PORT_C:
			PORTC.OUTSET = u8Mask;
			break;
    
    case IO_PORT_D:
			PORTD.OUTSET = u8Mask;
			break;  
    
    case IO_PORT_E:
      PORTF.OUTSET = u8Mask;
			break;  

    case IO_PORT_F:
      PORTF.OUTSET = u8Mask;
			break;
		
		default:
			break;
	}

}



/**
 * @brief      set the level of pin to low
 * 
 * @param      ePin             : corresponding pin
 * @warning    The pin must have been previously configured as output  
 */
static void vPinClear(eIoPortPin_t ePin)
{
  uint8_t u8Port  = 0;                                      // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                      // Get the pin mask from the index 

  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);       // Get the mask and the port value from the pin value

	switch (u8Port)
	{
		case IO_PORT_A:
			PORTA.OUTCLR = u8Mask;
			break;

    case IO_PORT_B:
			PORTB.OUTCLR = u8Mask;
			break;  

    case IO_PORT_C:
			PORTC.OUTCLR = u8Mask;
			break;
    
    case IO_PORT_D:
			PORTD.OUTCLR = u8Mask;
			break;  
    
    case IO_PORT_E:
      PORTF.OUTCLR = u8Mask;
			break;  

    case IO_PORT_F:
      PORTF.OUTCLR = u8Mask;
			break;
		
		default:
			break;
	}
}


/**
 * @brief      toggle the pin
 * 
 * @param      ePin             : corresponding pin
 * @warning    The pin must have been previously configured as output  
 *
 */
static void vPinToggle(eIoPortPin_t ePin)
{
  uint8_t u8Port  = 0;                                      // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                      // Get the pin mask from the index 

  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);       // Get the mask and the port value from the pin value

	switch (u8Port)
	{
		case IO_PORT_A:
			PORTA.OUTTGL = u8Mask;
			break;

    case IO_PORT_B:
			PORTB.OUTTGL = u8Mask;
			break;  

    case IO_PORT_C:
			PORTC.OUTTGL = u8Mask;
			break;
    
    case IO_PORT_D:
			PORTD.OUTTGL = u8Mask;
			break;  
    
    case IO_PORT_E:
      PORTE.OUTTGL = u8Mask;
			break;  

    case IO_PORT_F:
      PORTF.OUTTGL = u8Mask;
			break;
		
		default:
			break;
	}
}



/**
 * @brief      This function return the state of the 
 * 
 * @param      ePin             : corresponding pin
 */
static bool bPinRead(eIoPortPin_t ePin)
{
  uint8_t u8Port  = 0;                                      // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                      // Get the pin mask from the index 


  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);       // Get the mask and the port value from the pin value

  (void)u8Port;                                             // To avoid unused variable warning if not used in the switch statement

	switch (u8Port)
	{
		case IO_PORT_A:
      return ((PORTA.IN & u8Mask) == IO_LEVEL_HIGH);
			break;

    case IO_PORT_B:
			return ((PORTB.IN & u8Mask) == IO_LEVEL_HIGH);
			break;  

    case IO_PORT_C:
			return ((PORTC.IN & u8Mask) == IO_LEVEL_HIGH);
			break;
    
    case IO_PORT_D:
			return ((PORTD.IN & u8Mask) == IO_LEVEL_HIGH);
			break;  
    
    case IO_PORT_E:
      return ((PORTF.IN & u8Mask) == IO_LEVEL_HIGH);
			break;  

    case IO_PORT_F:
      return ((PORTF.IN & u8Mask) == IO_LEVEL_HIGH);
			break;
		
		default:
			break;
	}
}



/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 * @param      ePull            : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */
static void vPinDirInput(eIoPortPin_t ePin, ePullUp_t ePull)
{
  uint8_t u8Port  = 0;                                      // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                      // Get the pin mask from the index 

  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);       // Get the mask and the port value from the pin value

	switch (u8Port)
	{
		case IO_PORT_A:
			PORTA.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTA.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTA.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;

    case IO_PORT_B:
			PORTB.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTB.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTB.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;  

    case IO_PORT_C:
			PORTC.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTC.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTC.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;
    
    case IO_PORT_D:
			PORTD.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTD.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTD.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;  
    
    case IO_PORT_E:
      PORTF.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTF.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTF.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;  

    case IO_PORT_F:
      PORTF.DIRCLR = u8Mask;
      if (ePull == PULL_NONE)
      {
        PORTF.PIN0CTRL &= ~u8Mask; // Disable pull-up resistor
      }
      else
      {
        PORTF.PIN0CTRL |= u8Mask; // Enable pull-up resistor
      }
			break;
		
		default:
			break;
	}
  

}


/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 */
static void vPinDirOutput(eIoPortPin_t ePin)
{
  uint8_t u8Port  = 0;                                      // Init the port calculation from the index

  uint8_t u8Mask  = 0;                                      // Get the pin mask from the index 

  vComputePortAndMaskFromPin(&u8Mask, &u8Port, ePin);       // Get the mask and the port value from the pin value

	switch (u8Port)
	{
		case IO_PORT_A:
			PORTA.DIRSET = u8Mask;
			break;

    case IO_PORT_B:
			PORTB.DIRSET = u8Mask;
			break;  

    case IO_PORT_C:
			PORTC.DIRSET = u8Mask;
			break;
    
    case IO_PORT_D:
			PORTD.DIRSET = u8Mask;
			break;  
    
    case IO_PORT_E:
      PORTF.DIRSET = u8Mask;
			break;  

    case IO_PORT_F:
      PORTF.DIRSET = u8Mask;
			break;
		
		default:
			break;
	}
}






/*===================================================================================================================
 *        C O N F I G U R E  J U S T  P I N   T H A T  D O  N O T  H A V E  F U N C T I O N     S E T  O N           *
 *   PC2                                                                                                    PC7      *
 *   PC3                                                                                                    PC6      *
 *   PB2                                                                                                    PC5      *
 *   PB3                                                                                                    PC4      *
 * 
 *   PE0                                                                                                    PB5      *                                                                                         
 *   PE1                                                                                                    PB4      *
 *   PE2                                                                                                    PF5 LEDO *
 *   РЕЗ                                                                                                    PF4      *
 *   
 *                                                                                                                   *
 ====================================================================================================================*/

static void vSetOnPA00(void)
{
  vPinSet(PA00);  // Set pin PA00 to high
}

static void vSetOnPA01(void)
{
  vPinSet(PA01);  // Set pin PA01 to high
}

static void vSetOnPA02(void)
{
  vPinSet(PA02);  // Set pin PA02 to high
}

static void vSetOnPA03(void)
{
  vPinSet(PA03);  // Set pin PA03 to high
}

static void vSetOnPA04(void)
{
  vPinSet(PA04);  // Set pin PA04 to high
}

static void vSetOnPA05(void)
{
  vPinSet(PA05);  // Set pin PA05 to high
}

static void vSetOnPA06(void)
{
  vPinSet(PA06);  // Set pin PA06 to high
}

static void vSetOnPA07(void)
{
  vPinSet(PA07);  // Set pin PA07 to high
}

static void vSetOnPB00(void)
{
  vPinSet(PB00);  // Set pin PB00 to high
}

static void vSetOnPB01(void)
{
  vPinSet(PB01);  // Set pin PB01 to high
}

static void vSetOnPB02(void)
{
  vPinSet(PB02);  // Set pin PB02 to high
}

static void vSetOnPB03(void)
{
  vPinSet(PB03);  // Set pin PB03 to high
}

static void vSetOnPB04(void)
{
  vPinSet(PB04);  // Set pin PB04 to high
}

static void vSetOnPB05(void)
{
  vPinSet(PB05);  // Set pin PB05 to high
}

static void vSetOnPC00(void)
{
  vPinSet(PC00);  // Set pin PC00 to high
}

static void vSetOnPC01(void)
{
  vPinSet(PC01);  // Set pin PC01 to high
}

static void vSetOnPC02(void)
{
  vPinSet(PC02);  // Set pin PC02 to high
}

static void vSetOnPC03(void)
{
  vPinSet(PC03);  // Set pin PC03 to high
}

static void vSetOnPC04(void)
{
  vPinSet(PC04);  // Set pin PC04 to high
}

static void vSetOnPC05(void)
{
  vPinSet(PC05);  // Set pin PC05 to high
}

static void vSetOnPC06(void)
{
  vPinSet(PC06);  // Set pin PC06 to high
}

static void vSetOnPC07(void)
{
  vPinSet(PC07);  // Set pin PC07 to high
}

static void vSetOnPD00(void)
{
  vPinSet(PD00);  // Set pin PD00 to high
}

static void vSetOnPD01(void)
{
  vPinSet(PD01);  // Set pin PD01 to high
}

static void vSetOnPD02(void)
{
  vPinSet(PD02);  // Set pin PD02 to high
}

static void vSetOnPD03(void)
{
  vPinSet(PD03);  // Set pin PD03 to high
}

static void vSetOnPD04(void)
{
  vPinSet(PD04);  // Set pin PD04 to high
}

static void vSetOnPD05(void)
{
  vPinSet(PD05);  // Set pin PD05 to high
}

static void vSetOnPD06(void)
{
  vPinSet(PD06);  // Set pin PD06 to high
}

static void vSetOnPD07(void)
{
  vPinSet(PD07);  // Set pin PD07 to high
}

static void vSetOnPE00(void)
{
  vPinSet(PE00);  // Set pin PE00 to high
}

static void vSetOnPE01(void)
{
  vPinSet(PE01);  // Set pin PE01 to high
}

static void vSetOnPE02(void)
{
  vPinSet(PE02);  // Set pin PE02 to high
}

static void vSetOnPE03(void)
{
  vPinSet(PE03);  // Set pin PE03 to high
}

static void vSetOnPF00(void)
{
  vPinSet(PF00);  // Set pin PF00 to high
}

static void vSetOnPF01(void)
{
  vPinSet(PF01);  // Set pin PF01 to high
}

static void vSetOnPF02(void)
{
  vPinSet(PF02);  // Set pin PF02 to high
}

static void vSetOnPF03(void)
{
  vPinSet(PF03);  // Set pin PF03 to high
}

static void vSetOnPF04(void)
{
  vPinSet(PF04);  // Set pin PF04 to high
}

static void vSetOnPF05(void)
{
  vPinSet(PF05);  // Set pin PF05 to high
}

static void vSetOnPF06(void)
{
  vPinSet(PF06);  // Set pin PF06 to high
}

static void vSetOnPF07(void)
{
  vPinSet(PF07);  // Set pin PF07 to high
}


/*===================================================================================================================
 *        C O N F I G U R E  J U S T  P I N   T H A T  D O  N O T  H A V E  F U N C T I O N     S E T  O F F         *
 *   PC2                                                                                                    PC7      *
 *   PC3                                                                                                    PC6      *
 *   PB2                                                                                                    PC5      *
 *   PB3                                                                                                    PC4      *
 * 
 *   PE0                                                                                                    PB5      *                                                                                         
 *   PE1                                                                                                    PB4      *
 *   PE2                                                                                                    PF5 LEDO *
 *   РЕЗ                                                                                                    PF4      *
 *   
 *                                                                                                                   *
 ====================================================================================================================*/

static void vSetOffPA00(void)
{
  vPinClear(PA00);  // Set pin PA00 to low
}

static void vSetOffPA01(void)
{
  vPinClear(PA01);  // Set pin PA01 to low
}

static void vSetOffPA02(void)
{
  vPinClear(PA02);  // Set pin PA02 to low
}

static void vSetOffPA03(void)
{
  vPinClear(PA03);  // Set pin PA03 to low
}

static void vSetOffPA04(void)
{
  vPinClear(PA04);  // Set pin PA04 to low
}

static void vSetOffPA05(void)
{
  vPinClear(PA05);  // Set pin PA05 to low
}

static void vSetOffPA06(void)
{
  vPinClear(PA06);  // Set pin PA06 to low
}

static void vSetOffPA07(void)
{
  vPinClear(PA07);  // Set pin PA07 to low
}

static void vSetOffPB00(void)
{
  vPinClear(PB00);  // Set pin PB00 to low
}

static void vSetOffPB01(void)
{
  vPinClear(PB01);  // Set pin PB01 to low
}

static void vSetOffPB02(void)
{
  vPinClear(PB02);  // Set pin PB02 to low
}

static void vSetOffPB03(void)
{
  vPinClear(PB03);  // Set pin PB03 to low
}

static void vSetOffPB04(void)
{
  vPinClear(PB04);  // Set pin PB04 to low
}

static void vSetOffPB05(void)
{
  vPinClear(PB05);  // Set pin PB05 to low
}

static void vSetOffPC00(void)
{
  vPinClear(PC00);  // Set pin PC00 to low
}

static void vSetOffPC01(void)
{
  vPinClear(PC01);  // Set pin PC01 to low
}

static void vSetOffPC02(void)
{
  vPinClear(PC02);  // Set pin PC02 to low
}

static void vSetOffPC03(void)
{
  vPinClear(PC03);  // Set pin PC03 to low
}

static void vSetOffPC04(void)
{
  vPinClear(PC04);  // Set pin PC04 to low
}

static void vSetOffPC05(void)
{
  vPinClear(PC05);  // Set pin PC05 to low
}

static void vSetOffPC06(void)
{
  vPinClear(PC06);  // Set pin PC06 to low
}

static void vSetOffPC07(void)
{
  vPinClear(PC07);  // Set pin PC07 to low
}

static void vSetOffPD00(void)
{
  vPinClear(PD00);  // Set pin PD00 to low
}

static void vSetOffPD01(void)
{
  vPinClear(PD01);  // Set pin PD01 to low
}

static void vSetOffPD02(void)
{
  vPinClear(PD02);  // Set pin PD02 to low
}

static void vSetOffPD03(void)
{
  vPinClear(PD03);  // Set pin PD03 to low
}

static void vSetOffPD04(void)
{
  vPinClear(PD04);  // Set pin PD04 to low
}

static void vSetOffPD05(void)
{
  vPinClear(PD05);  // Set pin PD05 to low
}

static void vSetOffPD06(void)
{
  vPinClear(PD06);  // Set pin PD06 to low
}

static void vSetOffPD07(void)
{
  vPinClear(PD07);  // Set pin PD07 to low
}

static void vSetOffPE00(void)
{
  vPinClear(PE00);  // Set pin PE00 to low
}

static void vSetOffPE01(void)
{
  vPinClear(PE01);  // Set pin PE01 to low
}

static void vSetOffPE02(void)
{
  vPinClear(PE02);  // Set pin PE02 to low
}

static void vSetOffPE03(void)
{
  vPinClear(PE03);  // Set pin PE03 to low
}

static void vSetOffPF00(void)
{
  vPinClear(PF00);  // Set pin PF00 to low
}

static void vSetOffPF01(void)
{
  vPinClear(PF01);  // Set pin PF01 to low
}

static void vSetOffPF02(void)
{
  vPinClear(PF02);  // Set pin PF02 to low
}

static void vSetOffPF03(void)
{
  vPinClear(PF03);  // Set pin PF03 to low
}

static void vSetOffPF04(void)
{
  vPinClear(PF04);  // Set pin PF04 to low
}

static void vSetOffPF05(void)
{
  vPinClear(PF05);  // Set pin PF05 to low
}

static void vSetOffPF06(void)
{
  vPinClear(PF06);  // Set pin PF06 to low
}

static void vSetOffPF07(void)
{
  vPinClear(PF07);  // Set pin PF07 to low
}




/*===================================================================================================================
 *        C O N F I G U R E  J U S T  P I N   T H A T  D O  N O T  H A V E  F U N C T I O N     S E T  T G L         *
 *   PC2                                                                                                    PC7      *
 *   PC3                                                                                                    PC6      *
 *   PB2                                                                                                    PC5      *
 *   PB3                                                                                                    PC4      *
 * 
 *   PE0                                                                                                    PB5      *                                                                                         
 *   PE1                                                                                                    PB4      *
 *   PE2                                                                                                    PF5 LEDO *
 *   РЕЗ                                                                                                    PF4      *
 *   
 *                                                                                                                   *
 ====================================================================================================================*/

static void vTogglePA00(void)
{
  vPinToggle(PA00);  // Toggle pin PA00
}

static void vTogglePA01(void)
{
  vPinToggle(PA01);  // Toggle pin PA01
}

static void vTogglePA02(void)
{
  vPinToggle(PA02);  // Toggle pin PA02
}

static void vTogglePA03(void)
{
  vPinToggle(PA03);  // Toggle pin PA03
}

static void vTogglePA04(void)
{
  vPinToggle(PA04);  // Toggle pin PA04
}

static void vTogglePA05(void)
{
  vPinToggle(PA05);  // Toggle pin PA05
}

static void vTogglePA06(void)
{
  vPinToggle(PA06);  // Toggle pin PA06
}

static void vTogglePA07(void)
{
  vPinToggle(PA07);  // Toggle pin PA07
}

static void vTogglePB00(void)
{
  vPinToggle(PB00);  // Toggle pin PB00
}

static void vTogglePB01(void)
{
  vPinToggle(PB01);  // Toggle pin PB01
}

static void vTogglePB02(void)
{
  vPinToggle(PB02);  // Toggle pin PB02
}

static void vTogglePB03(void)
{
  vPinToggle(PB03);  // Toggle pin PB03
}

static void vTogglePB04(void)
{
  vPinToggle(PB04);  // Toggle pin PB04
}

static void vTogglePB05(void)
{
  vPinToggle(PB05);  // Toggle pin PB05
}

static void vTogglePC00(void)
{
  vPinToggle(PC00);  // Toggle pin PC00
}

static void vTogglePC01(void)
{
  vPinToggle(PC01);  // Toggle pin PC01
}

static void vTogglePC02(void)
{
  vPinToggle(PC02);  // Toggle pin PC02
}

static void vTogglePC03(void)
{
  vPinToggle(PC03);  // Toggle pin PC03
}

static void vTogglePC04(void)
{
  vPinToggle(PC04);  // Toggle pin PC04
}

static void vTogglePC05(void)
{
  vPinToggle(PC05);  // Toggle pin PC05
}

static void vTogglePC06(void)
{
  vPinToggle(PC06);  // Toggle pin PC06
}

static void vTogglePC07(void)
{
  vPinToggle(PC07);  // Toggle pin PC07
}

static void vTogglePD00(void)
{
  vPinToggle(PD00);  // Toggle pin PD00
}

static void vTogglePD01(void)
{
  vPinToggle(PD01);  // Toggle pin PD01
}

static void vTogglePD02(void)
{
  vPinToggle(PD02);  // Toggle pin PD02
}

static void vTogglePD03(void)
{
  vPinToggle(PD03);  // Toggle pin PD03
}

static void vTogglePD04(void)
{
  vPinToggle(PD04);  // Toggle pin PD04
}

static void vTogglePD05(void)
{
  vPinToggle(PD05);  // Toggle pin PD05
}

static void vTogglePD06(void)
{
  vPinToggle(PD06);  // Toggle pin PD06
}

static void vTogglePD07(void)
{
  vPinToggle(PD07);  // Toggle pin PD07
}

static void vTogglePE00(void)
{
  vPinToggle(PE00);  // Toggle pin PE00
}

static void vTogglePE01(void)
{
  vPinToggle(PE01);  // Toggle pin PE01
}

static void vTogglePE02(void)
{
  vPinToggle(PE02);  // Toggle pin PE02
}

static void vTogglePE03(void)
{
  vPinToggle(PE03);  // Toggle pin PE03
}

static void vTogglePF00(void)
{
  vPinToggle(PF00);  // Toggle pin PF00
}

static void vTogglePF01(void)
{
  vPinToggle(PF01);  // Toggle pin PF01
}

static void vTogglePF02(void)
{
  vPinToggle(PF02);  // Toggle pin PF02
}

static void vTogglePF03(void)
{
  vPinToggle(PF03);  // Toggle pin PF03
}

static void vTogglePF04(void)
{
  vPinToggle(PF04);  // Toggle pin PF04
}

static void vTogglePF05(void)
{
  vPinToggle(PF05);  // Toggle pin PF05
}

static void vTogglePF06(void)
{
  vPinToggle(PF06);  // Toggle pin PF06
}

static void vTogglePF07(void)
{
  vPinToggle(PF07);  // Toggle pin PF07
}


/*===================================================================================================================
 *        C O N F I G U R E  J U S T  P I N   T H A T  D O  N O T  H A V E  F U N C T I O N      R E A D  P I N      *
 *   PC2                                                                                                    PC7      *
 *   PC3                                                                                                    PC6      *
 *   PB2                                                                                                    PC5      *
 *   PB3                                                                                                    PC4      *
 * 
 *   PE0                                                                                                    PB5      *                                                                                         
 *   PE1                                                                                                    PB4      *
 *   PE2                                                                                                    PF5 LEDO *
 *   РЕЗ                                                                                                    PF4      *
 *   
 *                                                                                                                   *
 ====================================================================================================================*/

static bool bReadPA00(void)
{
  return bPinRead(PA00);  // Read pin PA00
}

static bool bReadPA01(void)
{
  return bPinRead(PA01);  // Read pin PA01
}

static bool bReadPA02(void)
{
  return bPinRead(PA02);  // Read pin PA02
}

static bool bReadPA03(void)
{
  return bPinRead(PA03);  // Read pin PA03
}

static bool bReadPA04(void)
{
  return bPinRead(PA04);  // Read pin PA04
}

static bool bReadPA05(void)
{
  return bPinRead(PA05);  // Read pin PA05
}

static bool bReadPA06(void)
{
  return bPinRead(PA06);  // Read pin PA06
}

static bool bReadPA07(void)
{
  return bPinRead(PA07);  // Read pin PA07
}

static bool bReadPB00(void)
{
  return bPinRead(PB00);  // Read pin PB00
}

static bool bReadPB01(void)
{
  return bPinRead(PB01);  // Read pin PB01
}

static bool bReadPB02(void)
{
  return bPinRead(PB02);  // Read pin PB02
}

static bool bReadPB03(void)
{
  return bPinRead(PB03);  // Read pin PB03
}

static bool bReadPB04(void)
{
  return bPinRead(PB04);  // Read pin PB04
}

static bool bReadPB05(void)
{
  return bPinRead(PB05);  // Read pin PB05
}

static bool bReadPC00(void)
{
  return bPinRead(PC00);  // Read pin PC00
}

static bool bReadPC01(void)
{
  return bPinRead(PC01);  // Read pin PC01
}

static bool bReadPC02(void)
{
  return bPinRead(PC02);  // Read pin PC02
}

static bool bReadPC03(void)
{
  return bPinRead(PC03);  // Read pin PC03
}

static bool bReadPC04(void)
{
  return bPinRead(PC04);  // Read pin PC04
}

static bool bReadPC05(void)
{
  return bPinRead(PC05);  // Read pin PC05
}

static bool bReadPC06(void)
{
  return bPinRead(PC06);  // Read pin PC06
}

static bool bReadPC07(void)
{
  return bPinRead(PC07);  // Read pin PC07
}

static bool bReadPD00(void)
{
  return bPinRead(PD00);  // Read pin PD00
}

static bool bReadPD01(void)
{
  return bPinRead(PD01);  // Read pin PD01
}

static bool bReadPD02(void)
{
  return bPinRead(PD02);  // Read pin PD02
}

static bool bReadPD03(void)
{
  return bPinRead(PD03);  // Read pin PD03
}

static bool bReadPD04(void)
{
  return bPinRead(PD04);  // Read pin PD04
}

static bool bReadPD05(void)
{
  return bPinRead(PD05);  // Read pin PD05
}

static bool bReadPD06(void)
{
  return bPinRead(PD06);  // Read pin PD06
}

static bool bReadPD07(void)
{
  return bPinRead(PD07);  // Read pin PD07
}

static bool bReadPE00(void)
{
  return bPinRead(PE00);  // Read pin PE00
}

static bool bReadPE01(void)
{
  return bPinRead(PE01);  // Read pin PE01
}

static bool bReadPE02(void)
{
  return bPinRead(PE02);  // Read pin PE02
}

static bool bReadPE03(void)
{
  return bPinRead(PE03);  // Read pin PE03
}

static bool bReadPF00(void)
{
  return bPinRead(PF00);  // Read pin PF00
}

static bool bReadPF01(void)
{
  return bPinRead(PF01);  // Read pin PF01
}

static bool bReadPF02(void)
{
  return bPinRead(PF02);  // Read pin PF02
}

static bool bReadPF03(void)
{
  return bPinRead(PF03);  // Read pin PF03
}

static bool bReadPF04(void)
{
  return bPinRead(PF04);  // Read pin PF04
}

static bool bReadPF05(void)
{
  return bPinRead(PF05);  // Read pin PF05
}

static bool bReadPF06(void)
{
  return bPinRead(PF06);  // Read pin PF06
}

static bool bReadPF07(void)
{
  return bPinRead(PF07);  // Read pin PF07
}







/**
 * @brief       configure the pin as Input or output and enable pull up
 * 
 * @param       ePin             : corresponding pin
 * @param       eDirection       : direction of pin . The direction take two value IO_DIR_INPUT and IO_DIR_OUTPUT
 * @param       ePull            : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */
static void vPinCfg(eIoPortPin_t ePin, eIoDirection_t eDirection, ePullUp_t ePull)
{

  if (eDirection == IO_DIR_INPUT) 
  {
    vPinDirInput(ePin, ePull);  // Configure the pin as input with the specified pull-up setting
  }
  else
  {
    vPinDirOutput(ePin);       // Configure the pin as output
  }

}






 /*===================================================================================================================
 *                    S E T  B A S I S  P I N S  F U N C T I O N S                                                   *                                                                                                          *
 ==================================================================================================================*/
static void vSetPinFunc(sDio_t*  psDigIO)
 {
	/* configure the pin as Input or output */
  vPinCfg(psDigIO->ePin, psDigIO->eDirection, psDigIO->ePullUp); 

	/* set pin functions */
	switch(psDigIO->ePin)
	{
    case PA00:
    // vSetOnPA00();
      psDigIO->pfvLevelOn   = vSetOnPA00;
      psDigIO->pfvLevelOff  = vSetOffPA00;
      psDigIO->pfvToggle    = vTogglePA00;
      psDigIO->pfbGetLevel  = bReadPA00;
      break;

    case PA01:
      psDigIO->pfvLevelOn   = vSetOnPA01;
      psDigIO->pfvLevelOff  = vSetOffPA01;
      psDigIO->pfvToggle    = vTogglePA01;
      psDigIO->pfbGetLevel  = bReadPA01;
      break;

    case PA02:
      psDigIO->pfvLevelOn   = vSetOnPA02;
      psDigIO->pfvLevelOff  = vSetOffPA02;
      psDigIO->pfvToggle    = vTogglePA02;
      psDigIO->pfbGetLevel  = bReadPA02;
      break;

    case PA03:
      psDigIO->pfvLevelOn   = vSetOnPA03;
      psDigIO->pfvLevelOff  = vSetOffPA03;
      psDigIO->pfvToggle    = vTogglePA03;
      psDigIO->pfbGetLevel  = bReadPA03;
      break;

    case PA04:
      psDigIO->pfvLevelOn   = vSetOnPA04;
      psDigIO->pfvLevelOff  = vSetOffPA04;
      psDigIO->pfvToggle    = vTogglePA04;
      psDigIO->pfbGetLevel  = bReadPA04;
      break;

    case PA05:
      psDigIO->pfvLevelOn   = vSetOnPA05;
      psDigIO->pfvLevelOff  = vSetOffPA05;
      psDigIO->pfvToggle    = vTogglePA05;
      psDigIO->pfbGetLevel  = bReadPA05;
      break;

    case PA06:
      psDigIO->pfvLevelOn   = vSetOnPA06;
      psDigIO->pfvLevelOff  = vSetOffPA06;
      psDigIO->pfvToggle    = vTogglePA06;
      psDigIO->pfbGetLevel  = bReadPA06;
      break;

    case PA07:
      psDigIO->pfvLevelOn   = vSetOnPA07;
      psDigIO->pfvLevelOff  = vSetOffPA07;
      psDigIO->pfvToggle    = vTogglePA07;
      psDigIO->pfbGetLevel  = bReadPA07;
      break;

    case PB00:
      psDigIO->pfvLevelOn   = vSetOnPB00;
      psDigIO->pfvLevelOff  = vSetOffPB00;
      psDigIO->pfvToggle    = vTogglePB00;
      psDigIO->pfbGetLevel  = bReadPB00;
      break;

    case PB01:
      psDigIO->pfvLevelOn   = vSetOnPB01;
      psDigIO->pfvLevelOff  = vSetOffPB01;
      psDigIO->pfvToggle    = vTogglePB01;
      psDigIO->pfbGetLevel  = bReadPB01;
      break;

    case PB02:
      psDigIO->pfvLevelOn   = vSetOnPB02;
      psDigIO->pfvLevelOff  = vSetOffPB02;
      psDigIO->pfvToggle    = vTogglePB02;
      psDigIO->pfbGetLevel  = bReadPB02;
      break;

    case PB03:
      psDigIO->pfvLevelOn   = vSetOnPB03;
      psDigIO->pfvLevelOff  = vSetOffPB03;
      psDigIO->pfvToggle    = vTogglePB03;
      psDigIO->pfbGetLevel  = bReadPB03;
      break;

    case PB04:
      psDigIO->pfvLevelOn   = vSetOnPB04;
      psDigIO->pfvLevelOff  = vSetOffPB04;
      psDigIO->pfvToggle    = vTogglePB04;
      psDigIO->pfbGetLevel  = bReadPB04;
      break;

    case PB05:
      psDigIO->pfvLevelOn   = vSetOnPB05;
      psDigIO->pfvLevelOff  = vSetOffPB05;
      psDigIO->pfvToggle    = vTogglePB05;
      psDigIO->pfbGetLevel  = bReadPB05;
      break;

    case PC00:
      psDigIO->pfvLevelOn   = vSetOnPC00;
      psDigIO->pfvLevelOff  = vSetOffPC00;
      psDigIO->pfvToggle    = vTogglePC00;
      psDigIO->pfbGetLevel  = bReadPC00;
      break;

    case PC01:
      psDigIO->pfvLevelOn   = vSetOnPC01;
      psDigIO->pfvLevelOff  = vSetOffPC01;
      psDigIO->pfvToggle    = vTogglePC01;
      psDigIO->pfbGetLevel  = bReadPC01;
      break;

    case PC02:
      psDigIO->pfvLevelOn   = vSetOnPC02;
      psDigIO->pfvLevelOff  = vSetOffPC02;
      psDigIO->pfvToggle    = vTogglePC02;
      psDigIO->pfbGetLevel  = bReadPC02;
      break;

    case PC03:
      psDigIO->pfvLevelOn   = vSetOnPC03;
      psDigIO->pfvLevelOff  = vSetOffPC03;
      psDigIO->pfvToggle    = vTogglePC03;
      psDigIO->pfbGetLevel  = bReadPC03;
      break;

    case PC04:
      psDigIO->pfvLevelOn   = vSetOnPC04;
      psDigIO->pfvLevelOff  = vSetOffPC04;
      psDigIO->pfvToggle    = vTogglePC04;
      psDigIO->pfbGetLevel  = bReadPC04;
      break;

    case PC05:
      psDigIO->pfvLevelOn   = vSetOnPC05;
      psDigIO->pfvLevelOff  = vSetOffPC05;
      psDigIO->pfvToggle    = vTogglePC05;
      psDigIO->pfbGetLevel  = bReadPC05;
      break;

    case PC06:
      psDigIO->pfvLevelOn   = vSetOnPC06;
      psDigIO->pfvLevelOff  = vSetOffPC06;
      psDigIO->pfvToggle    = vTogglePC06;
      psDigIO->pfbGetLevel  = bReadPC06;
      break;

    case PC07:
      psDigIO->pfvLevelOn   = vSetOnPC07;
      psDigIO->pfvLevelOff  = vSetOffPC07;
      psDigIO->pfvToggle    = vTogglePC07;
      psDigIO->pfbGetLevel  = bReadPC07;
      break;

    case PD00:
      psDigIO->pfvLevelOn   = vSetOnPD00;
      psDigIO->pfvLevelOff  = vSetOffPD00;
      psDigIO->pfvToggle    = vTogglePD00;
      psDigIO->pfbGetLevel  = bReadPD00;
      break;

    case PD01:
      psDigIO->pfvLevelOn   = vSetOnPD01;
      psDigIO->pfvLevelOff  = vSetOffPD01;
      psDigIO->pfvToggle    = vTogglePD01;
      psDigIO->pfbGetLevel  = bReadPD01;
      break;

    case PD02:
      psDigIO->pfvLevelOn   = vSetOnPD02;
      psDigIO->pfvLevelOff  = vSetOffPD02;
      psDigIO->pfvToggle    = vTogglePD02;
      psDigIO->pfbGetLevel  = bReadPD02;
      break;

    case PD03:
      psDigIO->pfvLevelOn   = vSetOnPD03;
      psDigIO->pfvLevelOff  = vSetOffPD03;
      psDigIO->pfvToggle    = vTogglePD03;
      psDigIO->pfbGetLevel  = bReadPD03;
      break;

    case PD04:
      psDigIO->pfvLevelOn   = vSetOnPD04;
      psDigIO->pfvLevelOff  = vSetOffPD04;
      psDigIO->pfvToggle    = vTogglePD04;
      psDigIO->pfbGetLevel  = bReadPD04;
      break;

    case PD05:
      psDigIO->pfvLevelOn   = vSetOnPD05;
      psDigIO->pfvLevelOff  = vSetOffPD05;
      psDigIO->pfvToggle    = vTogglePD05;
      psDigIO->pfbGetLevel  = bReadPD05;
      break;

    case PD06:
      psDigIO->pfvLevelOn   = vSetOnPD06;
      psDigIO->pfvLevelOff  = vSetOffPD06;
      psDigIO->pfvToggle    = vTogglePD06;
      psDigIO->pfbGetLevel  = bReadPD06;
      break;

    case PD07:
      psDigIO->pfvLevelOn   = vSetOnPD07;
      psDigIO->pfvLevelOff  = vSetOffPD07;
      psDigIO->pfvToggle    = vTogglePD07;
      psDigIO->pfbGetLevel  = bReadPD07;
      break;

    case PE00:
      psDigIO->pfvLevelOn   = vSetOnPE00;
      psDigIO->pfvLevelOff  = vSetOffPE00;
      psDigIO->pfvToggle    = vTogglePE00;
      psDigIO->pfbGetLevel  = bReadPE00;
      break;

    case PE01:
      psDigIO->pfvLevelOn   = vSetOnPE01;
      psDigIO->pfvLevelOff  = vSetOffPE01;
      psDigIO->pfvToggle    = vTogglePE01;
      psDigIO->pfbGetLevel  = bReadPE01;
      break;

    case PE02:
      psDigIO->pfvLevelOn   = vSetOnPE02;
      psDigIO->pfvLevelOff  = vSetOffPE02;
      psDigIO->pfvToggle    = vTogglePE02;
      psDigIO->pfbGetLevel  = bReadPE02;
      break;

    case PE03:
      psDigIO->pfvLevelOn   = vSetOnPE03;
      psDigIO->pfvLevelOff  = vSetOffPE03;
      psDigIO->pfvToggle    = vTogglePE03;
      psDigIO->pfbGetLevel  = bReadPE03;
      break;

    case PF00:
      psDigIO->pfvLevelOn   = vSetOnPF00;
      psDigIO->pfvLevelOff  = vSetOffPF00;
      psDigIO->pfvToggle    = vTogglePF00;
      psDigIO->pfbGetLevel  = bReadPF00;
      break;

    case PF01:
      psDigIO->pfvLevelOn   = vSetOnPF01;
      psDigIO->pfvLevelOff  = vSetOffPF01;
      psDigIO->pfvToggle    = vTogglePF01;
      psDigIO->pfbGetLevel  = bReadPF01;
      break;

    case PF02:
      psDigIO->pfvLevelOn   = vSetOnPF02;
      psDigIO->pfvLevelOff  = vSetOffPF02;
      psDigIO->pfvToggle    = vTogglePF02;
      psDigIO->pfbGetLevel  = bReadPF02;
      break;

    case PF03:
      psDigIO->pfvLevelOn   = vSetOnPF03;
      psDigIO->pfvLevelOff  = vSetOffPF03;
      psDigIO->pfvToggle    = vTogglePF03;
      psDigIO->pfbGetLevel  = bReadPF03;
      break;

    case PF04:
      psDigIO->pfvLevelOn   = vSetOnPF04;
      psDigIO->pfvLevelOff  = vSetOffPF04;
      psDigIO->pfvToggle    = vTogglePF04;
      psDigIO->pfbGetLevel  = bReadPF04;
      break;

    case PF05:
      psDigIO->pfvLevelOn   = vSetOnPF05;
      psDigIO->pfvLevelOff  = vSetOffPF05;
      psDigIO->pfvToggle    = vTogglePF05;
      psDigIO->pfbGetLevel  = bReadPF05;
      break;

    case PF06:
      psDigIO->pfvLevelOn   = vSetOnPF06;
      psDigIO->pfvLevelOff  = vSetOffPF06;
      psDigIO->pfvToggle    = vTogglePF06;
      psDigIO->pfbGetLevel  = bReadPF06;
      break;

    case PF07:
      psDigIO->pfvLevelOn   = vSetOnPF07;
      psDigIO->pfvLevelOff  = vSetOffPF07;
      psDigIO->pfvToggle    = vTogglePF07;
      psDigIO->pfbGetLevel  = bReadPF07;
      break;

    default:
      psDigIO->pfvLevelOn   = NULL;
      psDigIO->pfvLevelOff  = NULL;
      psDigIO->pfvToggle    = NULL;
      psDigIO->pfbGetLevel  = NULL;
      break;
  }
 }  





/********************************************************************************************************************
*													                                                                                          *
*	                     P U B L I C   F U N C T I O N  I M P L E M E N T A T I O N S                                 *
*   													                                                                                      *
********************************************************************************************************************/
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
			        ePullUp_t        ePullUp)
{
  psDigIO->ePin       = ePin;
  psDigIO->eDirection = eDirection;
  psDigIO->ePullUp    = ePullUp;
  psDigIO->pfvSetFunc = vSetPinFunc;

  vSetPinFunc(psDigIO);  // Configure the pin functions based on the pin object
}







/********************************************************************************************************************
 *                                                                                                                  *
 *                                          E N D   OF  M O D U L E                                                 *
 *                                                                                                                  *
 *******************************************************************************************************************/

/************************ Copyright (C) 2026 Trecspe.  All rights reserved. ****/
