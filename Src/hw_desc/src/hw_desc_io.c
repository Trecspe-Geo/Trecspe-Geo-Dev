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
#include "hw_desc_io.h"

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
#define IO_PORT_PIN_OFFSET            (8U)
#define IO_PORT_PIN_MSK               (0x0FU)
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
*													                                                                *
*	                           S T A T I C   F U N C T I O N  D E C L A T I O N                                     *
*   													                                                            *
********************************************************************************************************************/

/**
 * @brief       This function enable writing on the GPIO port
 */
static void vPinAccessEnable(void);

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

/********************************************************************************************************************
*													                                                                *
*	                     S T A T I C   F U N C T I O N  I M P L E M E N T A T I O N S                               *
*   													                                                            *
********************************************************************************************************************/

/**
 * @brief This function enable writing on the GPIO port
 */
static void vPinAccessEnable(void)
{
	if(PFS->PWPR & (1 << IO_PWPR_B0WI_BIT))
	{
		bWriteEnable = true;                       
		PFS->PWPR    = 0;                          // enable writing on PSF register
		PFS->PWPR   |= (1 << IO_PWPR_PFSWE_BIT);   // enable writing on GPIO port
	}

}

#if !defined(UNUSEDFUNCTION)
/**
 * @brief This function disable writing on the GPIO port
 */

/*Unused function */
static void vPinAccessDisable(void) UNUSED_FUNCTION;

static void vPinAccessDisable(void)
{	
	if(bWriteEnable == true)
	{
		bWriteEnable = false;
		PFS->PWPR  = 0;                                      // enable writing on PSF register
		PFS->PWPR &=  (uint8_t)(~(1 << IO_PWPR_PFSWE_BIT));  // disable writing on GPIO port
		PFS->PWPR |=  (1 << IO_PWPR_B0WI_BIT);               // disable writing on PSF register
	}
}
#endif

/**
 * @brief     set the level of pin to high
 * 
 * @param     ePin              : corresponding pin
 * @warning   The pin must have been previously configured as output  
 */
static void vPinSet(eIoPortPin_t ePin)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

	uint32_t u32Pfs = R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS;
	
	/* Enable writing on PFS */
	vPinAccessEnable();

	/* Clear PMR, ISEL and ASELbits */
	u32Pfs &= ~(IO_PFS_PMR_MSK | IO_PFS_ISEL_MSK | IO_PFS_ASEL_MSK); 

	/* set output level and pin direction to output */
	u32Pfs |= (IO_PFS_PODR_MSK); 

	R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS = u32Pfs; 

}

/**
 * @brief      set the level of pin to low
 * 
 * @param      ePin             : corresponding pin
 * @warning    The pin must have been previously configured as output  
 */
static void vPinClear(eIoPortPin_t ePin)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

	uint32_t u32Pfs = R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS;

	/* Enable writing on PFS */
	vPinAccessEnable();

	/* Clear PMR, ISEL ad ASEL bits */
	u32Pfs &= ~(IO_PFS_PMR_MSK | IO_PFS_ISEL_MSK | IO_PFS_ASEL_MSK); 

	/* set output level and pin direction to output */
    u32Pfs &= (~IO_PFS_PODR_MSK);

	R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS = u32Pfs; 

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
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

	uint32_t u32Pfs = R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS;

	/* Enable writing on PFS */
	vPinAccessEnable();

	/* Clear PMR, ISEL and ASEL bits */
	u32Pfs &= ~(IO_PFS_PMR_MSK | IO_PFS_ISEL_MSK | IO_PFS_ASEL_MSK ); 

	/* invert output level and set pin direction to output */
	u32Pfs ^= (IO_PFS_PODR_MSK);

	R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS = u32Pfs; 
}

/**
 * @brief     configure the pin as Input or output and enable pull up
 * 
 * @param     ePin        : corresponding pin
 * @param     eDirection  : direction of pin . The direction take two value IO_DIR_INPUT and IO_DIR_OUTPUT
 * @param     ePull       : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */
static void vPinCfg(eIoPortPin_t ePin, eIoDirection_t eDirection, ePullUp_t ePull)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

	uint32_t u32Pfs = R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS;

	/* Enable writing on PFS */
	vPinAccessEnable();

	/* Clear PMR, ISEL, ASEL and PDR bits */
	u32Pfs &= ~(IO_PFS_PMR_MSK | IO_PFS_ISEL_MSK | IO_PFS_ASEL_MSK| IO_PFS_PDR_MSK); 

	/* Set pin direction */
	u32Pfs |= (eDirection << IO_PFS_PDR_BIT);

	/* Enable internal pull up resistor if pin is set in input*/
	if(eDirection == IO_DIR_INPUT)
	{
		u32Pfs |= (ePull << IO_PFS_PCR_BIT);
	}

	R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS = u32Pfs; 
}

#if !defined(UNUSEDFUNCTION)

/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 * @param      ePull            : enable internal pull up , this take two value PULL_UP and PULL_NONE
 */

/*Unused function */
static void vPinDirInput(eIoPortPin_t ePin, ePullUp_t ePull) UNUSED_FUNCTION;

static void vPinDirInput(eIoPortPin_t ePin, ePullUp_t ePull)
{
	vPinCfg(ePin, IO_DIR_INPUT, ePull);
}

#endif


#if !defined(UNUSEDFUNCTION)

/**
 * @brief      configure the pin as Input or output and enable pull up
 * 
 * @param      ePin             : corresponding pin
 */
/*Unused function */
static void vPinDirOutput(eIoPortPin_t ePin) UNUSED_FUNCTION;
static void vPinDirOutput(eIoPortPin_t ePin)
{
	vPinCfg(ePin, IO_DIR_OUTPUT, PULL_NONE);
}

#endif

/**
 * @brief      This function return the state of the 
 * 
 * @param      ePin             : corresponding pin
 */
static bool bPinRead(eIoPortPin_t ePin)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

	uint32_t u32Pfs = R_PFS->PORT[u16Pin >> IO_PORT_PIN_OFFSET].PIN[u16Pin & IO_PORT_PIN_MSK].PmnPFS;

	return (IO_LEVEL_HIGH == ((u32Pfs & IO_PFS_PIDR_MSK) >> IO_PFS_PIDR_BIT)); 
}

/**
 * 
 * @brief enable kint interrupt 
 * 
 * @param eDetectionSense  sense direction of signal , FALLING_EDGE and RISING_EDGE 
 */
static void vKintIntEnable(eIoDetectionSense_t eDetectionSense) 
{                                                    
	/* Initialization of registers */
	uint8_t u8Krctl = 0;  
	uint8_t u8Sense = eDetectionSense & IO_SENSE_DETECTION_MSk;

	/* Enable KINT featured */
	u8Krctl  |= (1 << IO_KINT_KRTCL_KRMD_BIT);

	/* Choose edge */   
	u8Krctl |= u8Sense << IO_KINT_KRTCL_KREG_BIT;      

    /* store the value in the registers */
	KINT->KRCTL = u8Krctl;
	KINT->KRF   = 0;

	/* et priority of NVIC Key interrupt */
	NVIC_SetPriority((IRQn_Type)IO_KINT_CHANNEL, IO_KINT_PRIORITY);  

    /* Enable NVIC key interrupt   */
	NVIC_EnableIRQ((IRQn_Type)IO_KINT_CHANNEL);  
	
    /* 	select IRQ source interrupt */
	R_ICU->IELSR[IO_KINT_CHANNEL] = IO_KINT_IELSR_MSK;   
}

/**
 * @brief This function initialize kint feature
 *
 * @param u8Pin   corresponding pin
 * @param ePullUp : set this parameter to enable internal pull up resistor or nicht
 * @param pfvCbk  user callback
 */
static void vKintPinEnable(uint8_t  u8Pin,  
					       ePullUp_t ePullUp,
					       cbkFunc_t vFunCbk)
{
	// Initializatio of register and registration of call back function
	uint32_t        u32Pfs = 0;
	static uint8_t  u8Krm  = 0;
	vKintFunCbk[u8Pin] = vFunCbk;

	// clear ASEL, ISEL abd PODR bits 
	u32Pfs    &= ~(IO_PFS_ISEL_MSK | IO_PFS_ASEL_MSK | IO_PFS_PODR_MSK);   

	// choose pin P100 for GPIO interrupt                                 
	u32Pfs    |=  IO_KINT_PSEL_MSK; 

	// pin of PORT1 is configured as alternate function for Kint feature                          
	u32Pfs    |=  IO_PFS_PMR_MSK; 

	// pin of PORT1 is configured as Input                  
	u32Pfs    &= ~IO_PFS_PDR_MSK;  

	// enable detection of signal on pin 'u8Pin' of PORT1       
	u8Krm     |= (uint8_t)(1U << u8Pin);   

    // enable internal pull-up resistor
	u32Pfs    |= ePullUp << IO_PFS_PCR_BIT;                        

    // store value in the registers 
	R_PFS->PORT[1].PIN[u8Pin].PmnPFS = u32Pfs;  
	KINT->KRM  = u8Krm;                                                       
}

/**
 * @brief This function uninitialize kint feature on selected pin
 *
 * @param u8Pin   corresponding pin
 */
static void vKintPinDisable(uint8_t  u8Pin)
{
	// Initialization of register and registration of call back function
	uint32_t        u32Pfs = 0;
	static uint8_t  u8Krm  = 0;
	bool bFunCbkDefined = false;

	// pin of PORT1 is configured as GPIO                         
	u32Pfs    &=  ~IO_PFS_PMR_MSK; 

	// pin of PORT1 is configured as Input                  
	u32Pfs    &= ~IO_PFS_PDR_MSK;  

	// disable detection of signal on pin 'u8Pin' of PORT1       
	u8Krm     &= (uint8_t)~(1U << u8Pin);                         

    // store value in the registers 
	R_PFS->PORT[1].PIN[u8Pin].PmnPFS = u32Pfs;  
	KINT->KRM  = u8Krm;   

    // remove callback
	vKintFunCbk[u8Pin] = NULL_PTR; 
    
	// check if another callback functions defined
	for(uint8_t u8I= 0; u8I < IO_INT_PIN_MAX; u8I++)
	{
		if(vKintFunCbk[u8I] != NULL_PTR)
		{
			bFunCbkDefined = true;
			break;
		}
	}

	if(bFunCbkDefined == FALSE)
	{  
		/* Enable NVIC key interrupt   */
		NVIC_DisableIRQ((IRQn_Type)IO_KINT_CHANNEL);  

		/* 	select IRQ source interrupt */
		R_ICU->IELSR[IO_KINT_CHANNEL] = IO_RESET; 
	}                     
}

/**
 * @brief This function uninitialize kint feature on pin P100
 */
static void vKintP100Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P100 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                  
}
/**
 * @brief This function uninitialize kint feature on pin P101
 */
static void vKintP101Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P101 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                  
}
/**
 * @brief This function uninitialize kint feature on pin P102
 */
static void vKintP102Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P102 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                   
}
/**
 * @brief This function uninitialize kint feature on pin P103
 */
static void vKintP103Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P103 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                  
}
/**
 * @brief This function uninitialize kint feature on pin P104
 */
static void vKintP104Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P104 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                    
}
/**
 * @brief This function uninitialize kint feature on pin P105
 */
static void vKintP105Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P105 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                  
}
/**
 * @brief This function uninitialize kint feature on pin P106
 */
static void vKintP106Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P106 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                  
}
/**
 * @brief This function uninitialize kint feature on pin P107
 */
static void vKintP107Disable(void)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)P107 - 1; 

	vKintPinDisable(u16Pin & IO_PORT_PIN_MSK);                                                    
}

/**
 * @brief This function initialize kint feature
 * 
 * @param ePin   corresponding pin
 * @param eDetectionSense  sense direction of signal , FALLING_EDGE and RISING_EDGE 
 * @param ePullUp : set this parameter to enable internal pull up resistor or nicht
 * @param vFunCbk  user callback
 */
static void vKintInit(eIoPortPin_t ePin,  
					  eIoDetectionSense_t eDetectionSense, 
					  ePullUp_t ePullUp,
					  cbkFunc_t vFunCbk)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)ePin - 1; 

    /* Compute the corresponding port */
	uint8_t u8Port = (uint8_t)(u16Pin >> IO_PORT_PIN_OFFSET);

	if((u8Port == IO_PORT_1) && (vFunCbk != NULL_PTR))
    {
        vPinAccessEnable();                               // enable writing on gpio pins
        switch(ePin)
		{
			case P100:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P100 for key interrupt                            
			  break;
			case P101:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P101 for key interrupt   
			  break;
			case P102:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P102 for key interrupt   
			  break;
			case P103:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P103 for key interrupt   
			  break;
			case P104:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P104 for key interrupt   
			  break;
			case P105:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P105 for key interrupt   
			  break;
			case P106:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P106 for key interrupt   
			  break;
			case P107:
              vKintPinEnable((u16Pin & IO_PORT_PIN_MSK), ePullUp, vFunCbk);     // set pin P107 for key interrupt   
			  break;
            default:
			  // do nothing
			  break;
		}
		vKintIntEnable(eDetectionSense);                   // enable key interrupt
	}
}

/**
 * @brief This function initialize kint feature on pin P100
 */
static void vKintP100Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P100, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P101
 */
static void vKintP101Init( eIoDetectionSense_t eDetectionSense, 
							ePullUp_t          ePullUp,
							cbkFunc_t          vFunCbk)
{
   vKintInit(P101, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P102
 */
static void vKintP102Init( eIoDetectionSense_t eDetectionSense, 
							ePullUp_t          ePullUp,
							cbkFunc_t          vFunCbk)
{
   vKintInit(P102, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P103
 */
static void vKintP103Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P103, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P104
 */
static void vKintP104Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P104, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P105
 */
static void vKintP105Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P105, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P106
 */
static void vKintP106Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P106, eDetectionSense, ePullUp, vFunCbk);
}
/**
 * @brief This function initialize kint feature on pin P107
 */
static void vKintP107Init( eIoDetectionSense_t eDetectionSense, 
					       ePullUp_t           ePullUp,
					       cbkFunc_t           vFunCbk)
{
   vKintInit(P107, eDetectionSense, ePullUp, vFunCbk);
}
					  

/**
 * @brief This function uninitialize kint feature on selected pin
 * 
 * @param IntObj            :  interrupt pin object

 */
static void vKintUnInit(sIntIo_t*   IntObj)
{
	/* compute the correct pin number  */
	uint16_t  u16Pin = (uint16_t)IntObj->ePin - 1; 

    /* compute the corresponding port */
	uint8_t u8Port = (uint8_t)(u16Pin >> IO_PORT_PIN_OFFSET);

	if((u8Port == IO_PORT_1) && (IntObj->vFunCbk != NULL_PTR))
    {
        vPinAccessEnable();                               // enable writing on gpio pins
        switch(IntObj->ePin)
		{
			case P100:
              IntObj->pfvUnRegFuncbk = vKintP100Disable;     // disable key interrupt on pin P100                          
			  break;
			case P101:
              IntObj->pfvUnRegFuncbk = vKintP101Disable;     // disable key interrupt on pin P101                          
			  break;
			case P102:
              IntObj->pfvUnRegFuncbk = vKintP102Disable;     // disable key interrupt on pin P102                          
			  break;
			case P103:
              IntObj->pfvUnRegFuncbk = vKintP103Disable;     // disable key interrupt on pin P103                          
			  break;
			case P104:
              IntObj->pfvUnRegFuncbk = vKintP104Disable;     // disable key interrupt on pin P104                          
			  break;
			case P105:
              IntObj->pfvUnRegFuncbk = vKintP105Disable;     // disable key interrupt on pin P105                          
			  break;
			case P106:
              IntObj->pfvUnRegFuncbk = vKintP106Disable;     // disable key interrupt on pin P106                          
			  break;
			case P107:
              IntObj->pfvUnRegFuncbk = vKintP107Disable;     // disable key interrupt on pin P107                          
			  break;
            default:
			  // do nothing
			  break;
		}
	}
}

/**
 * @brief key interrupt handler
 */
static void vKintHandler(void)
{
	for(uint8_t u8Flag = IO_RESET ; u8Flag < IO_INT_PIN_MAX; u8Flag++)
	{
		if((vKintFunCbk[u8Flag] != NULL_PTR) && (KINT->KRF & (1 << u8Flag)))
		{
			vKintFunCbk[u8Flag]();                                  // call registered function
			R_ICU->IELSR[IO_KINT_CHANNEL] &= ~IO_IELSR_IR_MSK;      // Clear interrupt flag
			KINT->KRF &= (uint8_t)(~(1 << u8Flag));                 // Clear kint flag
		}
	}

	NVIC_ClearPendingIRQ(IO_KINT_CHANNEL);
}

/** @brief       This function enable IRQ0 interrupt on pin P400
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ0Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ0_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense  << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P400PFS = u32Pfs;
		ICU->IRQCR0  = u8IRQCR;

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ0_CHANNEL, IO_IRQ0_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ0_CHANNEL);
        
		/* Enable interrupt IRQ0 */
		R_ICU->IELSR[IO_IRQ0_CHANNEL] = IO_IRQ0_IELSR_MSK; 
    }
}

/** @brief       This function disable IRQ0 interrupt on pin P400
  * @return      none
 **/
static void vIRQ0Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ0_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P400PFS = u32Pfs;
	ICU->IRQCR0  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ0_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ0_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ0 interrupt is generated in the event of a change of state of pins "P400" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ0InterruptHandler(void)
{
	if((R_ICU->IELSR[IO_IRQ0_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ0_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ0_INDEX]();
		R_ICU->IELSR[IO_IRQ0_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ0_CHANNEL);
	}
}

/** @brief       This function enable IRQ1 interrupt on pin P205
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ1Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ1_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P205PFS = u32Pfs;
		ICU->IRQCR1  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ1_CHANNEL, IO_IRQ1_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ1_CHANNEL);
        
		/* Enable interrupt IRQ1 */
		R_ICU->IELSR[IO_IRQ1_CHANNEL] = IO_IRQ1_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ1interrupt on pin P205
  * @return      none
 **/
static void vIRQ1Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ1_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &=(uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P205PFS = u32Pfs;
	ICU->IRQCR1  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ1_CHANNEL);
	
	/* Enable interrupt IRQ1 */
	R_ICU->IELSR[IO_IRQ1_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ1 interrupt is generated in the event of a change of state of pins "P205" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ1InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ1_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ1_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ1_INDEX]();
		R_ICU->IELSR[IO_IRQ1_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ1_CHANNEL);
	}
}

/** @brief       This function enable IRQ1 interrupt on pin P002
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ2Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ2_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense  << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P002PFS = u32Pfs;
		ICU->IRQCR2  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ2_CHANNEL, IO_IRQ2_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ2_CHANNEL);
        
		/* Enable interrupt IRQ2 */
		R_ICU->IELSR[IO_IRQ2_CHANNEL] = IO_IRQ2_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ2 interrupt on pin P002
  * @return      none
 **/
static void vIRQ2Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ2_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P002PFS = u32Pfs;
	ICU->IRQCR2  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ2_CHANNEL);
	
	/* Enable interrupt IRQ2 */
	R_ICU->IELSR[IO_IRQ2_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ2 interrupt is generated in the event of a change of state of pins "P002" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ2InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ2_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ2_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ2_INDEX]();
		R_ICU->IELSR[IO_IRQ2_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ2_CHANNEL);
	}
}

/** @brief       This function enable IRQ3 interrupt on pin P004
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ3Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ3_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P004PFS = u32Pfs;
		ICU->IRQCR3  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ3_CHANNEL, IO_IRQ3_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ3_CHANNEL);
        
		/* Enable interrupt IRQ3 */
		R_ICU->IELSR[IO_IRQ3_CHANNEL] = IO_IRQ3_IELSR_MSK;
    }
}

/** @brief       IRQ3 interrupt is generated in the event of a change of state of pins "P004" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ3InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ3_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ3_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ3_INDEX]();
		R_ICU->IELSR[IO_IRQ3_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ3_CHANNEL);
	}
}

/** @brief       This function disable IRQ0 interrupt on pin P004
  * @return      none
 **/
static void vIRQ3Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ3_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P004PFS = u32Pfs;
	ICU->IRQCR3  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ3_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ3_CHANNEL] = IO_RESET; 		
}

/** @brief       This function enable IRQ4 interrupt on pin P402
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ4Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ4_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P402PFS = u32Pfs;
		ICU->IRQCR4  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ4_CHANNEL, IO_IRQ4_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ4_CHANNEL);
        
		/* Enable interrupt IRQ4 */
		R_ICU->IELSR[IO_IRQ4_CHANNEL] = IO_IRQ4_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ0 interrupt on pin P402
  * @return      none
 **/
static void vIRQ4Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ4_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P402PFS = u32Pfs;
	ICU->IRQCR4  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ4_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ4_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ4 interrupt is generated in the event of a change of state of pins "P402" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ4InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ4_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ4_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ4_INDEX]();
		R_ICU->IELSR[IO_IRQ4_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ4_CHANNEL); 
	}
}

/** @brief       This function enable IRQ5 interrupt on pin P401
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ5Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ5_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P401PFS = u32Pfs;
		ICU->IRQCR5  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ5_CHANNEL, IO_IRQ5_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ5_CHANNEL);
        
		/* Enable interrupt IRQ5 */
		R_ICU->IELSR[IO_IRQ5_CHANNEL] = IO_IRQ5_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ0 interrupt on pin P401
  * @return      none
 **/
static void vIRQ5Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ5_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P401PFS = u32Pfs;
	ICU->IRQCR5  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ5_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ5_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ5 interrupt is generated in the event of a change of state of pins "P401" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ5InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ5_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ5_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ5_INDEX]();
		R_ICU->IELSR[IO_IRQ5_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ5_CHANNEL);
	}
}

/** @brief       This function enable IRQ6 interrupt on pin P000
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ6Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ6_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge, rising edge, low level or rising and falling edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P000PFS = u32Pfs;
		ICU->IRQCR6  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ6_CHANNEL, IO_IRQ6_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ6_CHANNEL);
        
		/* Enable interrupt IRQ5 */
		R_ICU->IELSR[IO_IRQ6_CHANNEL] = IO_IRQ6_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ0 interrupt on pin P000
  * @return      none
 **/
static void vIRQ6Disable(void)
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ6_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P000PFS = u32Pfs;
	ICU->IRQCR6  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ6_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ6_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ6 interrupt is generated in the event of a change of state of pins "P000" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ6InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ6_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ6_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ6_INDEX]();
		R_ICU->IELSR[IO_IRQ6_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ6_CHANNEL);
	}
}

/** @brief       This function enable IRQ7 interrupt on pin P001
  * @param       eDetectionSense : it allows to select on which edge the signal will be detected (RISING_EDGE or FALLING_EDGE)
  * @param       ePullUp         : specifies whether to use internal pull up resistors or not
  * @param       vFunCbk         : the function called in the interrupt routine 
  * @return      none
 **/
static void vIRQ7Init(eIoDetectionSense_t eDetectionSense, ePullUp_t ePullUp, cbkFunc_t vFunCbk)
{
	if(vFunCbk != NULL_PTR)
	{
		uint32_t u32Pfs = 0;
		uint8_t u8IRQCR = 0;
		/* Store call back fucntion */
		vIRQFunCbk[IO_IRQ7_INDEX] = vFunCbk;

		/* Enable writing on PFS register */
		vPinAccessEnable();

		/* Wait 2 cycles before reading the port */
		PFS->PRWCNTR |= IO_PRWCNTR_WAIT_MSK; 

		/* Assignation of Interrupt IRQ on pin P400 */
        u32Pfs  |= IO_PSEL_IRQ_MSK;

		/* Allow P400 pin to use as IRQ intput*/
		u32Pfs  |= IO_PFS_ISEL_MSK;

		/* Configution of pin to alternative function */
		u32Pfs  |= IO_PFS_PMR_MSK;

		/* Enable internal pull up resistor */
		u32Pfs  |= (uint32_t)(ePullUp << IO_PFS_PCR_BIT);

		/* configuration of sense detection : falling edge oder rising edge */
		u8IRQCR |= eDetectionSense << IO_IRQCR_IRQMD_BIT;   

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FCLKSEL_MSK;

		/* Enable digital filter */
		u8IRQCR |= IO_IRQCR_FLTEN_MSK; 

		PFS->P001PFS = u32Pfs;
		ICU->IRQCR7  = u8IRQCR; 

		/* Enable and set NVIC interrupt priority*/
		NVIC_SetPriority(IO_IRQ7_CHANNEL, IO_IRQ7_PRIORITY);
		NVIC_EnableIRQ(IO_IRQ7_CHANNEL);
        
		/* Enable interrupt IRQ5 */
		R_ICU->IELSR[IO_IRQ7_CHANNEL] = IO_IRQ7_IELSR_MSK;
    }
}

/** @brief       This function disable IRQ0 interrupt on pin P400
  * @return      none
 **/
static void vIRQ7Disable(void) 
{
	uint32_t u32Pfs = 0;
	uint8_t u8IRQCR = 0;
	/* Store call back fucntion */
	vIRQFunCbk[IO_IRQ7_INDEX] = NULL_PTR;

	/* Enable writing on PFS register */
	vPinAccessEnable();

	/* Wait 1 cycles before reading the port */
	PFS->PRWCNTR |= 1 << IO_PRWCNTR_WAIT_BIT; 

	/* Assignation of Interrupt IRQ on pin P400 */
	u32Pfs  &= (uint32_t)(~IO_PSEL_IRQ_MSK);

	/* Allow P400 pin to use as IRQ intput*/
	u32Pfs  &= ~IO_PFS_ISEL_MSK;

	/* Configution of pin as GPIO*/
	u32Pfs  &= ~IO_PFS_PMR_MSK; 

	PFS->P001PFS = u32Pfs;
	ICU->IRQCR7  = u8IRQCR;

	/* Disable and set NVIC interrupt priority*/
	NVIC_DisableIRQ(IO_IRQ7_CHANNEL);
	
	/* Enable interrupt IRQ0 */
	R_ICU->IELSR[IO_IRQ7_CHANNEL] = IO_RESET; 		
}

/** @brief       IRQ7 interrupt is generated in the event of a change of state of pins "P001" of the microcontroller
  * @param [IN]  none
  * @param [OUT] none
  * @return      none
 **/
static void vIRQ7InterruptHandler(void)
{
	if ((R_ICU->IELSR[IO_IRQ7_CHANNEL] & IO_IELSR_IR_MSK) && (vIRQFunCbk[IO_IRQ7_INDEX] != NULL_PTR))
	{
		vIRQFunCbk[IO_IRQ7_INDEX]();
		R_ICU->IELSR[IO_IRQ7_CHANNEL] &= ~IO_IELSR_IR_MSK; 
		NVIC_ClearPendingIRQ(IO_IRQ7_CHANNEL);
	}
}

/*===================================================================================================================
 *                    P O R T 0 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/

/************************************************************
 *  set the direction of port0
*************************************************************/
static void vPort0Dirset(uint16_t u16PortMsk)
{
	PORT0->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port0
*************************************************************/
static uint16_t u16Port0Dirget(void)
{
	return PORT0->PDR;
}

/************************************************************
 *  write on port0
*************************************************************/
static void vPort0Write(uint16_t u16PortMsk)
{
	PORT0->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port0
*************************************************************/
static void vPort0Toggle(void)
{
	PORT0->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port0
*************************************************************/
static uint16_t u16Port0Read(void)
{
	return PORT0->PIDR;
}

/************************************************************
 *  set pins of port0
*************************************************************/

/* set pin P000 to high */
// static void vSetPin000(void)
// {
// 	vPinSet(P000);
// }


/* set pin P001 to high */
// static void vSetPin001(void)
// {
// 	vPinSet(P001);
// }


/* set pin P002 to high */
// static void vSetPin002(void)
// {
	
// 	vPinSet(P002);
// }


/* set pin P003 to high */
// static void vSetPin003(void)
// {
	
// 	vPinSet(P003);
// }


/* set pin P004 to high */
// static void vSetPin004(void)
// {
// 	vPinSet(P004);
// }


/* set pin P010 to high */
// static void vSetPin010(void)
// {
// 	vPinSet(P010);
// }


/* set pin P011 to high */
// static void vSetPin011(void)
// {
// 	vPinSet(P011);
// }


/* set pin P012 to high */
// static void vSetPin012(void)
// {

// 	vPinSet(P012);
// }

/* set pin P013 to high */
// static void vSetPin013(void)
// {
	
// 	vPinSet(P013);
// }


/* set pin P014 to high */
// static void vSetPin014(void)
// {

// 	vPinSet(P014);
// }


/* set pin P015 to high */
// static void vSetPin015(void)
// {
// 	vPinSet(P015);
// }

/************************************************************
 *  clear pins of port0
*************************************************************/
/* Clear pin P000   */
// static void vClearPin000(void)
// {
	
// 	vPinClear(P000);
// }
/* Clear pin P001   */
// static void vClearPin001(void)
// {
// 	vPinClear(P001);
// }
/* Clear pin P002   */
// static void vClearPin002(void)
// {
	
// 	vPinClear(P002);
// }
/* Clear pin P003   */
// static void vClearPin003(void)
// {

// 	vPinClear(P003);
// }
/* Clear pin P004   */
// static void vClearPin004(void)
// {

// 	vPinClear(P004);
// }
/* Clear pin P010   */
// static void vClearPin010(void)
// {
// 	vPinClear(P010);
// }
/* Clear pin P011   */
// static void vClearPin011(void)
// {
// 	vPinClear(P011);
// }
/* Clear pin P012   */
// static void vClearPin012(void)
// {

// 	vPinClear(P012);
// }
/* Clear pin P013   */
// static void vClearPin013(void)
// {

// 	vPinClear(P013);
// }
/* Clear pin P014   */
// static void vClearPin014(void)
// {
// 	vPinClear(P014);
// }
/* Clear pin P015   */
// static void vClearPin015(void)
// {

// 	vPinClear(P015);
// }

/************************************************************
 *  Toggle pins of port0
*************************************************************/
/* Toggle pin P000   */
// static void vTogglePin000(void)
// {
	
// 	vPinToggle(P000);
// }
/* Toggle pin P001   */
// static void vTogglePin001(void)
// {
// 	vPinToggle(P001);
// }
/* Toggle pin P002   */
// static void vTogglePin002(void)
// {

// 	vPinToggle(P002);
// }
/* Toggle pin P003   */
// static void vTogglePin003(void)
// {
	
// 	vPinToggle(P003);
// }
/* Toggle pin P004   */
// static void vTogglePin004(void)
// {
	
// 	vPinToggle(P004);
// }
/* Toggle pin P010   */
// static void vTogglePin010(void)
// {
// 	vPinToggle(P010);
// }
/* Toggle pin P011   */
// static void vTogglePin011(void)
// {
// 	vPinToggle(P011);
// }
/* Toggle pin P012   */
// static void vTogglePin012(void)
// {
// 	vPinToggle(P012);
// }
/* Toggle pin P013   */
// static void vTogglePin013(void)
// {
// 	vPinToggle(P013);
// }
/* Toggle pin P014   */
// static void vTogglePin014(void)
// {
// 	vPinToggle(P014);
// }
/* Toggle pin P015   */
// static void vTogglePin015(void)
// {
// 	vPinToggle(P015);
// }

/************************************************************
 *  GetLevel pins of port0
*************************************************************/
/* GetLevel pin P000   */
// static bool bReadPin000(void)
// {
// 	return bPinRead(P000);
// }
/* GetLevel pin P001   */
// static bool bReadPin001(void)
// {
// 	return bPinRead(P001);
// }
/* GetLevel pin P002   */
// static bool bReadPin002(void)
// {
// 	return bPinRead(P002);
// }
/* GetLevel pin P003   */
// static bool bReadPin003(void)
// {
// 	return bPinRead(P003);
// }
/* GetLevel pin P004   */
// static bool bReadPin004(void)
// {
// 	return bPinRead(P004);
// }
/* GetLevel pin P010   */
// static bool bReadPin010(void)
// {
// 	return bPinRead(P010);
// }
/* GetLevel pin P011   */
// static bool bReadPin011(void)
// {
// 	return bPinRead(P011);
// }
/* GetLevel pin P012   */
// static bool bReadPin012(void)
// {
// 	return bPinRead(P012);
// }
/* GetLevel pin P013   */
// static bool bReadPin013(void)
// {
// 	return bPinRead(P013);
// }
/* GetLevel pin P014   */
// static bool bReadPin014(void)
// {
// 	return bPinRead(P014);
// }
/* GetLevel pin P015   */
// static bool bReadPin015(void)
// {
// 	return bPinRead(P015);
// }

/*===================================================================================================================
 *                    P O R T 0 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

 /*===================================================================================================================
 *                    P O R T 1 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/
/************************************************************
 *  set the direction of port1
*************************************************************/
static void vPort1Dirset(uint16_t u16PortMsk)
{
	PORT1->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port1
*************************************************************/
static uint16_t u16Port1Dirget(void)
{
	return PORT1->PDR;
}

/************************************************************
 *  write on port1
*************************************************************/
static void vPort1Write(uint16_t u16PortMsk)
{
	PORT1->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port1
*************************************************************/
static void vPort1Toggle(void)
{
	PORT1->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port1
*************************************************************/
static uint16_t u16Port1Read(void)
{
	return PORT1->PIDR;
}


/************************************************************
 *  set pins of port1
*************************************************************/
/* set pin P100 to high */
// static void vSetPin100(void)
// {
// 	vPinSet(P100);
// }
/* set pin P101 to high */
// static void vSetPin101(void)
// {
// 	vPinSet(P101);
// }
/* set pin P102 to high */
// static void vSetPin102(void)
// {
	
// 	vPinSet(P102);
// }
/* set pin P103 to high */
// static void vSetPin103(void)
// {
// 	vPinSet(P103);
// }
/* set pin P104 to high */
// static void vSetPin104(void)
// {
// 	vPinSet(P104);
// }
/* set pin P100 to high */
// static void vSetPin105(void)
// {
// 	vPinSet(P105);
// }
/* set pin P106 to high */
// static void vSetPin106(void)
// {
	
// 	vPinSet(P106);
// }
/* set pin P107 to high */
// static void vSetPin107(void)
// {
// 	vPinSet(P107);
// }
/* set pin P108 to high */
// static void vSetPin108(void)
// {
// 	vPinSet(P108);
// }
/* set pin P109 to high */
// static void vSetPin109(void)
// {
// 	vPinSet(P109);
// }
/* set pin P110 to high */
// static void vSetPin110(void)
// {
// 	vPinSet(P110);
// }
/* set pin P111 to high */
// static void vSetPin111(void)
// {
// 	vPinSet(P111);
// }
/* set pin P112 to high */
// static void vSetPin112(void)
// {
// 	vPinSet(P112);
// }
/* set pin P113 to high */
// static void vSetPin113(void)
// {
// 	vPinSet(P113);
// }

/************************************************************
 *  Clear pins of port1
*************************************************************/
/* Clear pin P100   */
// static void vClearPin100(void)
// {

// 	vPinClear(P100);
// }
/* Clear pin P101   */
// static void vClearPin101(void)
// {
// 	vPinClear(P101);
// }
/* Clear pin P102   */
// static void vClearPin102(void)
// {
// 	vPinClear(P102);
// }
/* Clear pin P103   */
// static void vClearPin103(void)
// {
// 	vPinClear(P103);
// }
/* Clear pin P104   */
// static void vClearPin104(void)
// {
// 	vPinClear(P104);
// }
/* Clear pin P100   */
// static void vClearPin105(void)
// {
// 	vPinClear(P105);
// }
/* Clear pin P106   */
// static void vClearPin106(void)
// {
// 	vPinClear(P106);
// }
/* Clear pin P107   */
// static void vClearPin107(void)
// {
// 	vPinClear(P107);
// }
/* Clear pin P108   */
// static void vClearPin108(void)
// {
// 	vPinClear(P108);
// }
/* Clear pin P109   */
// static void vClearPin109(void)
// {
// 	vPinClear(P109);
// }
/* Clear pin P110   */
// static void vClearPin110(void)
// {
// 	vPinClear(P110);
// }
/* Clear pin P111   */
// static void vClearPin111(void)
// {
// 	vPinClear(P111);
// }
/* Clear pin P112   */
// static void vClearPin112(void)
// {
// 	vPinClear(P112);
// }
/* Clear pin P113   */
// static void vClearPin113(void)
// {
// 	vPinClear(P113);
// }

/************************************************************
 *  Toggle pins of port1
*************************************************************/
/* Toggle pin P100  */
// static void vTogglePin100(void)
// {
// 	vPinToggle(P100);
// }
/* Toggle pin P101  */
// static void vTogglePin101(void)
// {
// 	vPinToggle(P101);
// }
/* Toggle pin P102  */
// static void vTogglePin102(void)
// {
// 	vPinToggle(P102);
// }
/* Toggle pin P103  */
// static void vTogglePin103(void)
// {
// 	vPinToggle(P103);
// }
/* Toggle pin P104  */
// static void vTogglePin104(void)
// {
// 	vPinToggle(P104);
// }
/* Toggle pin P105  */
// static void vTogglePin105(void)
// {
// 	vPinToggle(P105);
// }
/* Toggle pin P106  */
// static void vTogglePin106(void)
// {
// 	vPinToggle(P106);
// }
/* Toggle pin P107  */
// static void vTogglePin107(void)
// {
// 	vPinToggle(P107);
// }
/* Toggle pin P108  */
// static void vTogglePin108(void)
// {
// 	vPinToggle(P108);
// }
/* Toggle pin P109  */
// static void vTogglePin109(void)
// {

// 	vPinToggle(P109);
// }
/* Toggle pin P110  */
// static void vTogglePin110(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin110);

// 	vPinToggle(P110);
// }
/* Toggle pin P111  */
// static void vTogglePin111(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin111);

// 	vPinToggle(P111);
// }
/* Toggle pin P112  */
// static void vTogglePin112(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin112);

// 	vPinToggle(P112);
// }
/* Toggle pin P113  */
// static void vTogglePin113(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin113);

// 	vPinToggle(P113);
// }

/************************************************************
 *  Get level of pins of port1
*************************************************************/
/* Get level of pin P100  */
// static bool bReadPin100(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin100);

// 	return bPinRead(P100);
// }
/* Get level of pin P101  */
// static bool bReadPin101(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin101);

// 	return bPinRead(P101);
// }
/* Get level of pin P102  */
// static bool bReadPin102(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin102);

// 	return bPinRead(P102);
// }
/* Get level of pin P103  */
// static bool bReadPin103(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin103);

// 	return bPinRead(P103);
// }
/* Get level of pin P104  */
// static bool bReadPin104(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin104);

// 	return bPinRead(P104);
// }
/* Get level of pin P100  */
// static bool bReadPin105(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin105);

// 	return bPinRead(P105);
// }
/* Get level of pin P106  */
// static bool bReadPin106(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin106);

// 	return bPinRead(P106);
// }
/* Get level of pin P107  */
// static bool bReadPin107(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin107);

// 	return bPinRead(P107);
// }
/* Get level of pin P108  */
// static bool bReadPin108(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin108);

// 	return bPinRead(P108);
// }
/* Get level of pin P109  */
// static bool bReadPin109(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin109);

// 	return bPinRead(P109);
// }
/* Get level of pin P110  */
// static bool bReadPin110(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin110);

// 	return bPinRead(P110);
// }
/* Get level of pin P111  */
// static bool bReadPin111(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin111);

// 	return bPinRead(P111);
// }
/* Get level of pin P112  */
// static bool bReadPin112(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin112);

// 	return bPinRead(P112);
// }
/* Get level of pin P113  */
// static bool bReadPin113(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin113);

// 	return bPinRead(P113);
// }



/*===================================================================================================================
 *                    P O R T 1 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

 /*===================================================================================================================
 *                    P O R T 2 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/

/************************************************************
 *  set the direction of port2
*************************************************************/
static void vPort2Dirset(uint16_t u16PortMsk)
{
	PORT2->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port2
*************************************************************/
static uint16_t u16Port2Dirget(void)
{
	return PORT2->PDR;
}

/************************************************************
 *  write on port2
*************************************************************/
static void vPort2Write(uint16_t u16PortMsk)
{
	PORT2->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port2
*************************************************************/
static void vPort2Toggle(void)
{
	PORT2->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port2
*************************************************************/
static uint16_t u16Port2Read(void)
{
	return PORT2->PIDR;
}


/************************************************************
 *  set pins of PORT2
*************************************************************/
/* set pin P200 to high */
// static void vSetPin200(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin200);

// 	vPinSet(P200);
// }
/* set pin P201 to high */
// static void vSetPin201(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin201);

// 	vPinSet(P201);
// }
/* set pin P204 to high */
// static void vSetPin204(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin204);

// 	vPinSet(P204);
// }
/* set pin P200 to high */
// static void vSetPin205(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin205);

// 	vPinSet(P205);
// }
/* set pin P206 to high */
// static void vSetPin206(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin206);

// 	vPinSet(P206);
// }
/* set pin P207 to high */
// static void vSetPin207(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin207);

// 	vPinSet(P207);
// }
/* set pin P208 to high */
// static void vSetPin208(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin208);

// 	vPinSet(P208);
// }
// /* set pin P210 to high */
// static void vSetPin212(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin212);

// 	vPinSet(P212);
// }
/* set pin P211 to high */
// static void vSetPin213(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin213);

// 	vPinSet(P213);
// }
/* set pin P212 to high */
// static void vSetPin214(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin214);

// 	vPinSet(P214);
// }
/* set pin P213 to high */
// static void vSetPin215(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin215);

// 	vPinSet(P215);
// }

/************************************************************
 *  Clear pins of port2
*************************************************************/
/* Clear pin P200   */
// static void vClearPin200(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin200);

// 	vPinClear(P200);
// }
/* Clear pin P201   */
// static void vClearPin201(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin201);

// 	vPinClear(P201);
// }
/* Clear pin P204   */
// static void vClearPin204(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin204);

// 	vPinClear(P204);
// }
/* Clear pin P200   */
// static void vClearPin205(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin205);

// 	vPinClear(P205);
// }
/* Clear pin P206   */
// static void vClearPin206(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin206);

// 	vPinClear(P206);
// }
/* Clear pin P207   */
// static void vClearPin207(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin207);

// 	vPinClear(P207);
// }
/* Clear pin P208   */
// static void vClearPin208(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin208);

// 	vPinClear(P208);
// }
/* Clear pin P210   */
// static void vClearPin212(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin212);

// 	vPinClear(P212);
// }
/* Clear pin P211   */
// static void vClearPin213(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin213);

// 	vPinClear(P213);
// }
/* Clear pin P212   */
// static void vClearPin214(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin214);

// 	vPinClear(P214);
// }
/* Clear pin P213   */
// static void vClearPin215(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin215);

// 	vPinClear(P215);
// }

/************************************************************
 *  Toggle pins of port2
*************************************************************/
/* Toggle pin P200  */
// static void vTogglePin200(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin200);

// 	vPinToggle(P200);
// }
/* Toggle pin P201  */
// static void vTogglePin201(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin201);

// 	vPinToggle(P201);
// }
/* Toggle pin P204  */
// static void vTogglePin204(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin204);

// 	vPinToggle(P204);
// }
/* Toggle pin P205  */
// static void vTogglePin205(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin205);

// 	vPinToggle(P205);
// }
/* Toggle pin P206  */
// static void vTogglePin206(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin206);

// 	vPinToggle(P206);
// }
/* Toggle pin P207  */
// static void vTogglePin207(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin207);

// 	vPinToggle(P207);
// }
/* Toggle pin P208  */
// static void vTogglePin208(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin208);

// 	vPinToggle(P208);
// }
/* Toggle pin P210  */
// static void vTogglePin212(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin212);

// 	vPinToggle(P212);
// }
/* Toggle pin P211  */
// static void vTogglePin213(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin213);

// 	vPinToggle(P213);
// }
/* Toggle pin P212  */
// static void vTogglePin214(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin214);

// 	vPinToggle(P214);
// }
/* Toggle pin P213  */
// static void vTogglePin215(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin215);

// 	vPinToggle(P215);
// }

/************************************************************
 *  Get level of pins of port2
*************************************************************/
/* Get level of pin P100  */
// static bool bReadPin200(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin200);

// 	return bPinRead(P200);
// }
/* Get level of pin P201  */
// static bool bReadPin201(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin201);

// 	return bPinRead(P201);
// }
/* Get level of pin P204  */
// static bool bReadPin204(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin204);

// 	return bPinRead(P204);
// }
/* Get level of pin P200  */
// static bool bReadPin205(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin205);

// 	return bPinRead(P205);
// }
/* Get level of pin P206  */
// static bool bReadPin206(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin206);

// 	return bPinRead(P206);
// }
/* Get level of pin P207  */
// static bool bReadPin207(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin207);

// 	return bPinRead(P207);
// }
/* Get level of pin P208  */
// static bool bReadPin208(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin208);

// 	return bPinRead(P208);
// }
/* Get level of pin P212  */
// static bool bReadPin212(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin212);

// 	return bPinRead(P212);
// }
/* Get level of pin P213  */
// static bool bReadPin213(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin213);

// 	return bPinRead(P213);
// }
/* Get level of pin P214  */
// static bool bReadPin214(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin214);

// 	return bPinRead(P214);
// }
/* Get level of pin P215  */
// static bool bReadPin215(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin215);

// 	return bPinRead(P215);
// }

/*===================================================================================================================
 *                    P O R T 2 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/


  /*===================================================================================================================
 *                    P O R T 3 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/
/************************************************************
 *  set the direction of port3
*************************************************************/
static void vPort3Dirset(uint16_t u16PortMsk)
{
	PORT3->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port3
*************************************************************/
static uint16_t u16Port3Dirget(void)
{
	return PORT3->PDR;
}

/************************************************************
 *  write on port3
*************************************************************/
static void vPort3Write(uint16_t u16PortMsk)
{
	PORT3->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port3
*************************************************************/
static void vPort3Toggle(void)
{
	PORT3->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port3
*************************************************************/
static uint16_t u16Port3Read(void)
{
	return PORT3->PIDR;
}


/************************************************************
 *  set pins of PORT3
*************************************************************/
/* set pin P200 to high */
// static void vSetPin300(void)
// {	
// 	/* Unused function*/
// 	UNUSED(vSetPin300);

// 	vPinSet(P300);
// }
/* set pin P301 to high */
static void vSetPin301(void)
{
	vPinSet(P301);
}
/* set pin P302 to high */
// static void vSetPin302(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin302);

// 	vPinSet(P302);
// }
/* set pin P303 to high */
// static void vSetPin303(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin303);

// 	vPinSet(P303);
// }
/* set pin P304 to high */
// static void vSetPin304(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin304);

// 	vPinSet(P304);
// }

/************************************************************
 *  Clear pins of port3
*************************************************************/
/* Clear pin P300   */
// static void vClearPin300(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin300);

// 	vPinClear(P300);
// }
/* Clear pin P301   */
static void vClearPin301(void)
{
	vPinClear(P301);
}
/* Clear pin P302   */
// static void vClearPin302(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin302);

// 	vPinClear(P302);
// }
/* Clear pin P303   */
// static void vClearPin303(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin303);

// 	vPinClear(P303);
// }
/* Clear pin P304   */
// static void vClearPin304(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin304);

// 	vPinClear(P304);
// }

/************************************************************
 *  Toggle pins of port3
*************************************************************/
/* Toggle pin P300  */
// static void vTogglePin300(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin300);

// 	vPinToggle(P300);
// }
/* Toggle pin P301  */
static void vTogglePin301(void)
{
	vPinToggle(P301);
}
/* Toggle pin P302  */
// static void vTogglePin302(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin302);

// 	vPinToggle(P302);
// }
/* Toggle pin P303  */
// static void vTogglePin303(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin303);

// 	vPinToggle(P303);
// }
/* Toggle pin P304  */
// static void vTogglePin304(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin304);

// 	vPinToggle(P304);
// }

/************************************************************
 *  Get level of pins of port3
*************************************************************/
/* Get level of pin P300  */
// static bool bReadPin300(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin300);

// 	return bPinRead(P300);
// }

/* Get level of pin P301  */
static bool bReadPin301(void)
{
	return bPinRead(P301);
}

/* Get level of pin P302  */
// static bool bReadPin302(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin302);

// 	return bPinRead(P302);
// }
/* Get level of pin P303  */
// static bool bReadPin303(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin303);

// 	return bPinRead(P303);
// }
/* Get level of pin P304  */
// static bool bReadPin304(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin304);

// 	return bPinRead(P304);
// }

/*===================================================================================================================
 *                    P O R T 3 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

  /*===================================================================================================================
 *                    P O R T 4 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/

/************************************************************
 *  set the direction of port4
*************************************************************/
static void vPort4Dirset(uint16_t u16PortMsk)
{
	PORT4->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port4
*************************************************************/
static uint16_t u16Port4Dirget(void)
{
	return PORT4->PDR;
}

/************************************************************
 *  write on port4
*************************************************************/
static void vPort4Write(uint16_t u16PortMsk)
{
	PORT4->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port4
*************************************************************/
static void vPort4Toggle(void)
{
	PORT4->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port4
*************************************************************/
static uint16_t u16Port4Read(void)
{
	return PORT4->PIDR;
}


/************************************************************
 *  set pins of port4
*************************************************************/
/* set pin P100 to high */
// static void vSetPin400(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin400);

// 	vPinSet(P400);
// }
/* set pin P401 to high */
// static void vSetPin401(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin401);

// 	vPinSet(P401);
// }
/* set pin P402 to high */
// static void vSetPin402(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin402);

// 	vPinSet(P402);
// }
/* set pin P403 to high */
// static void vSetPin403(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin403);

// 	vPinSet(P403);
// }
/* set pin P407 to high */
// static void vSetPin407(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin407);

// 	vPinSet(P407);
// }
/* set pin P408 to high */
// static void vSetPin408(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin408);

// 	vPinSet(P408);
// }
/* set pin P409 to high */
// static void vSetPin409(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin409);

// 	vPinSet(P409);
// }
/* set pin P410 to high */
// static void vSetPin410(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin410);

// 	vPinSet(P410);
// }
/* set pin P411 to high */
// static void vSetPin411(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin411);

// 	vPinSet(P411);
// }

/************************************************************
 *  Clear pins of port4
*************************************************************/
/* Clear pin P400   */
// static void vClearPin400(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin400);

// 	vPinClear(P400);
// }
/* Clear pin P401   */
// static void vClearPin401(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin401);

// 	vPinClear(P401);
// }
/* Clear pin P402   */
// static void vClearPin402(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin402);

// 	vPinClear(P402);
// }
/* Clear pin P403   */
// static void vClearPin403(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin403);

// 	vPinClear(P403);
// }
/* Clear pin P407   */
// static void vClearPin407(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin407);

// 	vPinClear(P407);
// }
/* Clear pin P408   */
// static void vClearPin408(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin408);

// 	vPinClear(P408);
// }
/* Clear pin P409   */
// static void vClearPin409(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin409);

// 	vPinClear(P409);
// }
/* Clear pin P410   */
// static void vClearPin410(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin410);

// 	vPinClear(P410);
// }
/* Clear pin P411   */
// static void vClearPin411(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin411);

// 	vPinClear(P411);
// }

/************************************************************
 *  Toggle pins of port4
*************************************************************/
/* Toggle pin P400  */
// static void vTogglePin400(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin400);

// 	vPinToggle(P400);
// }
/* Toggle pin P401  */
// static void vTogglePin401(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin401);

// 	vPinToggle(P401);
// }
/* Toggle pin P402  */
// static void vTogglePin402(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin402);

// 	vPinToggle(P402);
// }
/* Toggle pin P403  */
// static void vTogglePin403(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin403);

// 	vPinToggle(P403);
// }
/* Toggle pin P407  */
// static void vTogglePin407(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin407);

// 	vPinToggle(P407);
// }
/* Toggle pin P408  */
// static void vTogglePin408(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin408);

// 	vPinToggle(P408);
// }
/* Toggle pin P409  */
// static void vTogglePin409(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin409);

// 	vPinToggle(P409);
// }
/* Toggle pin P410  */
// static void vTogglePin410(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin410);

// 	vPinToggle(P410);
// }
/* Toggle pin P411  */
// static void vTogglePin411(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin411);

// 	vPinToggle(P411);
// }

/************************************************************
 *  Get level of pins of port4
*************************************************************/
/* Get level of pin P400  */
// static bool bReadPin400(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin400);

// 	return bPinRead(P400);
// }
/* Get level of pin P401  */
// static bool bReadPin401(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin401);

// 	return bPinRead(P401);
// }
/* Get level of pin P402  */
// static bool bReadPin402(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin402);

// 	return bPinRead(P402);
// }
/* Get level of pin P403  */
// static bool bReadPin403(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin403);

// 	return bPinRead(P403);
// }
/* Get level of pin P407  */
// static bool bReadPin407(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin407);

// 	return bPinRead(P407);
// }
/* Get level of pin P408  */
// static bool bReadPin408(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin408);

// 	return bPinRead(P408);
// }
/* Get level of pin P409  */
// static bool bReadPin409(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin409);

// 	return bPinRead(P409);
// }
/* Get level of pin P440  */
// static bool bReadPin410(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin410);

// 	return bPinRead(P410);
// }
/* Get level of pin P411  */
// static bool bReadPin411(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin411);

// 	return bPinRead(P411);
// }

/*===================================================================================================================
 *                    P O R T 4 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

/*===================================================================================================================
 *                    P O R T 5 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/

/************************************************************
 *  set the direction of port5
*************************************************************/
static void vPort5Dirset(uint16_t u16PortMsk)
{
	PORT5->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port5
*************************************************************/
static uint16_t u16Port5Dirget(void)
{
	return PORT5->PDR;
}

/************************************************************
 *  write on port5
*************************************************************/
static void vPort5Write(uint16_t u16PortMsk)
{
	PORT5->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port5
*************************************************************/
static void vPort5Toggle(void)
{
	PORT5->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port5
*************************************************************/
static uint16_t u16Port5Read(void)
{
	return PORT5->PIDR;
}


/************************************************************
 *  set pins of PORT5
*************************************************************/
/* set pin P500 to high */
// static void vSetPin500(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin500);

// 	vPinSet(P500);
// }
/* set pin P501 to high */
// static void vSetPin501(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin501);

// 	vPinSet(P501);
// }
/* set pin P502 to high */
static void vSetPin502(void)
{
	vPinSet(P502);
}

/************************************************************
 *  Clear pins of port5
*************************************************************/
/* Clear pin P500   */
// static void vClearPin500(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin500);

// 	vPinClear(P500);
// }
/* Clear pin P501   */
// static void vClearPin501(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin501);

// 	vPinClear(P501);
// }
/* Clear pin P502   */
static void vClearPin502(void)
{
	vPinClear(P502);
}

/************************************************************
 *  Toggle pins of port5
*************************************************************/
/* Toggle pin P500  */
// static void vTogglePin500(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin500);

// 	vPinToggle(P500);
// }
/* Toggle pin P501  */
// static void vTogglePin501(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin501);

// 	vPinToggle(P501);
// }
/* Toggle pin P502  */
static void vTogglePin502(void)
{
	vPinToggle(P502);
}

/************************************************************
 *  Get level of pins of port5
*************************************************************/
/* Get level of pin P500  */
// static bool bReadPin500(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin500);

// 	return bPinRead(P500);
// }
/* Get level of pin P501  */
// static bool bReadPin501(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin501);

// 	return bPinRead(P501);
// }
/* Get level of pin P502  */
static bool bReadPin502(void)
{
	return bPinRead(P502);
}

/*===================================================================================================================
 *                    P O R T 5 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

    /*===================================================================================================================
 *                    P O R T 9 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N                             *                                                                                                          *
 ==================================================================================================================*/
/************************************************************
 *  set the direction of port9
*************************************************************/
static void vPort9Dirset(uint16_t u16PortMsk)
{
	PORT9->PDR = u16PortMsk;
}

/************************************************************
 *  get the direction of port9
*************************************************************/
static uint16_t u16Port9Dirget(void)
{
	return PORT9->PDR;
}

/************************************************************
 *  write on port9
*************************************************************/
static void vPort9Write(uint16_t u16PortMsk)
{
	PORT9->PODR = u16PortMsk;
}

/************************************************************
 *  toggle port9
*************************************************************/
static void vPort9Toggle(void)
{
	PORT9->PODR ^= IO_PORT_TOGGLE_MSK;
}

/************************************************************
 *  read port9
*************************************************************/
static uint16_t u16Port9Read(void)
{
	return PORT9->PIDR;
}


/************************************************************
 *  set pins of PORT9
*************************************************************/
/* set pin P913 to high */
// static void vSetPin913(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin913);

// 	vPinSet(P913);
// }
/* set pin P914 to high */
// static void vSetPin914(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin914);

// 	vPinSet(P914);
// }
/* set pin P915 to high */
// static void vSetPin915(void)
// {
// 	/* Unused function*/
// 	UNUSED(vSetPin915);

// 	vPinSet(P915);
// }

/************************************************************
 *  Clear pins of port9
*************************************************************/
/* Clear pin P913   */
// static void vClearPin913(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin913);

// 	vPinClear(P913);
// }
/* Clear pin P914   */
// static void vClearPin914(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin914);

// 	vPinClear(P914);
// }
/* Clear pin P915   */
// static void vClearPin915(void)
// {
// 	/* Unused function*/
// 	UNUSED(vClearPin915);

// 	vPinClear(P915);
// }

/************************************************************
 *  Toggle pins of port9
*************************************************************/
/* Toggle pin P913  */
// static void vTogglePin913(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin913);

// 	vPinToggle(P913);
// }
/* Toggle pin P914  */
// static void vTogglePin914(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin914);

// 	vPinToggle(P914);
// }
/* Toggle pin P915  */
// static void vTogglePin915(void)
// {
// 	/* Unused function*/
// 	UNUSED(vTogglePin915);

// 	vPinToggle(P915);
// }

/************************************************************
 *  Get level of pins of port9
*************************************************************/
/* Get level of pin P913  */
// static bool bReadPin913(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin913);

// 	return bPinRead(P913);
// }
/* Get level of pin P914  */
// static bool bReadPin914(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin914);

// 	return bPinRead(P914);
// }
/* Get level of pin P915  */
// static bool bReadPin915(void)
// {
// 	/* Unused function*/
// 	UNUSED(bReadPin915);

// 	return bPinRead(P915);
// }

/*===================================================================================================================
 *                    P O R T 9 / B A S I S  F U N C T I O N  I M P L E M E N T A T I O N  E N D                      *                                                                                                          *
 ==================================================================================================================*/

  /*===================================================================================================================
 *                    S E T  B A S I S  P O R T S  F U N C T I O N S                     *                                                                                                          *
 ==================================================================================================================*/
 static void vSetPortFunc(sPortIo_t*  psPortObj)
 {
    switch (psPortObj->ePort)
	{
       case IO_PORT_0:
	       psPortObj->pfu16PortRead   = u16Port0Read;
		   psPortObj->pfu16PortDirGet = u16Port0Dirget;
		   psPortObj->pfvPortDirSet   = vPort0Dirset;
		   psPortObj->pfvPortToggle   = vPort0Toggle;
		   psPortObj->pfvPortWrite    = vPort0Write; 
		   break;

       case IO_PORT_1:
	       psPortObj->pfu16PortRead   = u16Port1Read;
		   psPortObj->pfu16PortDirGet = u16Port1Dirget;
		   psPortObj->pfvPortDirSet   = vPort1Dirset;
		   psPortObj->pfvPortToggle   = vPort1Toggle;
		   psPortObj->pfvPortWrite    = vPort1Write; 
		   break;
		   
       case IO_PORT_2:
	       psPortObj->pfu16PortRead   = u16Port2Read;
		   psPortObj->pfu16PortDirGet = u16Port2Dirget;
		   psPortObj->pfvPortDirSet   = vPort2Dirset;
		   psPortObj->pfvPortToggle   = vPort2Toggle;
		   psPortObj->pfvPortWrite    = vPort2Write; 
		   break;
		   
       case IO_PORT_3:
	       psPortObj->pfu16PortRead   = u16Port3Read;
		   psPortObj->pfu16PortDirGet = u16Port3Dirget;
		   psPortObj->pfvPortDirSet   = vPort3Dirset;
		   psPortObj->pfvPortToggle   = vPort3Toggle;
		   psPortObj->pfvPortWrite    = vPort3Write; 
		   break;
		   
       case IO_PORT_4:
	       psPortObj->pfu16PortRead   = u16Port4Read;
		   psPortObj->pfu16PortDirGet = u16Port4Dirget;
		   psPortObj->pfvPortDirSet   = vPort4Dirset;
		   psPortObj->pfvPortToggle   = vPort4Toggle;
		   psPortObj->pfvPortWrite    = vPort4Write; 
		   break;
		   
       case IO_PORT_5:
	       psPortObj->pfu16PortRead   = u16Port5Read;
		   psPortObj->pfu16PortDirGet = u16Port5Dirget;
		   psPortObj->pfvPortDirSet   = vPort5Dirset;
		   psPortObj->pfvPortToggle   = vPort5Toggle;
		   psPortObj->pfvPortWrite    = vPort5Write; 
		   break;
		   
       case IO_PORT_9:
	       psPortObj->pfu16PortRead   = u16Port9Read;
		   psPortObj->pfu16PortDirGet = u16Port9Dirget;
		   psPortObj->pfvPortDirSet   = vPort9Dirset;
		   psPortObj->pfvPortToggle   = vPort9Toggle;
		   psPortObj->pfvPortWrite    = vPort9Write; 
		   break;

	   default : 
	       // do nothing
	       break;
	}
 }

 /*===================================================================================================================
 *                    S E T  B A S I S  P I N S  F U N C T I O N S                     *                                                                                                          *
 ==================================================================================================================*/
 static void vSetPinFunc(sDio_t*  psDigIO)
 {
	/* configure the pin as Input or output */
    vPinCfg(psDigIO->ePin, psDigIO->eDirection, psDigIO->ePullUp); 

	/* set pin functions */
	switch(psDigIO->ePin)
	{
		// case P000  :
		//   psDigIO->pfvLevelOn   = vSetPin000;
		//   psDigIO->pfvLevelOff  = vClearPin000;
		//   psDigIO->pfvToggle    = vTogglePin000;
		//   psDigIO->pfbGetLevel  = bReadPin000;
		//   break;

		// case P001  :
		//   psDigIO->pfvLevelOn   = vSetPin001;
		//   psDigIO->pfvLevelOff  = vClearPin001;
		//   psDigIO->pfvToggle    = vTogglePin001;
		//   psDigIO->pfbGetLevel  = bReadPin001;
		//   break;

		// case P002  :
		//   psDigIO->pfvLevelOn   = vSetPin002;
		//   psDigIO->pfvLevelOff  = vClearPin002;
		//   psDigIO->pfvToggle    = vTogglePin002;
		//   psDigIO->pfbGetLevel  = bReadPin002;
		//   break;

		// case P003  :
		//   psDigIO->pfvLevelOn   = vSetPin003;
		//   psDigIO->pfvLevelOff  = vClearPin003;
		//   psDigIO->pfvToggle    = vTogglePin003;
		//   psDigIO->pfbGetLevel  = bReadPin003;
		//   break;

		// case P004  :
		//   psDigIO->pfvLevelOn   = vSetPin004;
		//   psDigIO->pfvLevelOff  = vClearPin004;
		//   psDigIO->pfvToggle    = vTogglePin004;
		//   psDigIO->pfbGetLevel  = bReadPin004;
		//   break;

		// case P010  :
		//   psDigIO->pfvLevelOn   = vSetPin010;
		//   psDigIO->pfvLevelOff  = vClearPin010;
		//   psDigIO->pfvToggle    = vTogglePin010;
		//   psDigIO->pfbGetLevel  = bReadPin010;
		//   break;

		// case P011  :
		//   psDigIO->pfvLevelOn   = vSetPin011;
		//   psDigIO->pfvLevelOff  = vClearPin011;
		//   psDigIO->pfvToggle    = vTogglePin011;
		//   psDigIO->pfbGetLevel  = bReadPin011;
		//   break;

		// case P012  :
		//   psDigIO->pfvLevelOn   = vSetPin012;
		//   psDigIO->pfvLevelOff  = vClearPin012;
		//   psDigIO->pfvToggle    = vTogglePin012;
		//   psDigIO->pfbGetLevel  = bReadPin012;
		//   break;

		// case P013  :
		//   psDigIO->pfvLevelOn   = vSetPin013;
		//   psDigIO->pfvLevelOff  = vClearPin013;
		//   psDigIO->pfvToggle    = vTogglePin013;
		//   psDigIO->pfbGetLevel  = bReadPin013;
		//   break;

		// case P014  :
		//   psDigIO->pfvLevelOn   = vSetPin014;
		//   psDigIO->pfvLevelOff  = vClearPin014;
		//   psDigIO->pfvToggle    = vTogglePin014;
		//   psDigIO->pfbGetLevel  = bReadPin014;
		//   break;

		// case P015  :
		//   psDigIO->pfvLevelOn   = vSetPin015;
		//   psDigIO->pfvLevelOff  = vClearPin015;
		//   psDigIO->pfvToggle    = vTogglePin015;
		//   psDigIO->pfbGetLevel  = bReadPin015;
		//   break;

		// case P100  :
		//   psDigIO->pfvLevelOn   = vSetPin100;
		//   psDigIO->pfvLevelOff  = vClearPin100;
		//   psDigIO->pfvToggle    = vTogglePin100;
		//   psDigIO->pfbGetLevel  = bReadPin100;
		//   break;

		// case P101  :
		//   psDigIO->pfvLevelOn   = vSetPin101;
		//   psDigIO->pfvLevelOff  = vClearPin101;
		//   psDigIO->pfvToggle    = vTogglePin101;
		//   psDigIO->pfbGetLevel  = bReadPin101;
		//   break;

		// case P102  :
		//   psDigIO->pfvLevelOn   = vSetPin102;
		//   psDigIO->pfvLevelOff  = vClearPin102;
		//   psDigIO->pfvToggle    = vTogglePin102;
		//   psDigIO->pfbGetLevel  = bReadPin102;
		//   break;
		  
		// case P103  :
		//   psDigIO->pfvLevelOn   = vSetPin103;
		//   psDigIO->pfvLevelOff  = vClearPin103;
		//   psDigIO->pfvToggle    = vTogglePin103;
		//   psDigIO->pfbGetLevel  = bReadPin103;
		//   break;
		  
		// case P104  :
		//   psDigIO->pfvLevelOn   = vSetPin104;
		//   psDigIO->pfvLevelOff  = vClearPin104;
		//   psDigIO->pfvToggle    = vTogglePin104;
		//   psDigIO->pfbGetLevel  = bReadPin104;
		//   break;
		  
		// case P105  :
		//   psDigIO->pfvLevelOn   = vSetPin105;
		//   psDigIO->pfvLevelOff  = vClearPin105;
		//   psDigIO->pfvToggle    = vTogglePin105;
		//   psDigIO->pfbGetLevel  = bReadPin105;
		//   break;
		  
		// case P106  :
		//   psDigIO->pfvLevelOn   = vSetPin106;
		//   psDigIO->pfvLevelOff  = vClearPin106;
		//   psDigIO->pfvToggle    = vTogglePin106;
		//   psDigIO->pfbGetLevel  = bReadPin106;
		//   break;
		  
		// case P107  :
		//   psDigIO->pfvLevelOn   = vSetPin107;
		//   psDigIO->pfvLevelOff  = vClearPin107;
		//   psDigIO->pfvToggle    = vTogglePin107;
		//   psDigIO->pfbGetLevel  = bReadPin107;
		//   break;
		  
		// case P108  :
		//   psDigIO->pfvLevelOn   = vSetPin108;
		//   psDigIO->pfvLevelOff  = vClearPin108;
		//   psDigIO->pfvToggle    = vTogglePin108;
		//   psDigIO->pfbGetLevel  = bReadPin108;
		//   break;
		  
		// case P109  :
		//   psDigIO->pfvLevelOn   = vSetPin109;
		//   psDigIO->pfvLevelOff  = vClearPin109;
		//   psDigIO->pfvToggle    = vTogglePin109;
		//   psDigIO->pfbGetLevel  = bReadPin109;
		//   break;
		  
		// case P110  :
		//   psDigIO->pfvLevelOn   = vSetPin110;
		//   psDigIO->pfvLevelOff  = vClearPin110;
		//   psDigIO->pfvToggle    = vTogglePin110;
		//   psDigIO->pfbGetLevel  = bReadPin110;
		//   break;
		  
		// case P111  :
		//   psDigIO->pfvLevelOn   = vSetPin111;
		//   psDigIO->pfvLevelOff  = vClearPin111;
		//   psDigIO->pfvToggle    = vTogglePin111;
		//   psDigIO->pfbGetLevel  = bReadPin111;
		//   break;
		  
		// case P112  :
		//   psDigIO->pfvLevelOn   = vSetPin112;
		//   psDigIO->pfvLevelOff  = vClearPin112;
		//   psDigIO->pfvToggle    = vTogglePin112;
		//   psDigIO->pfbGetLevel  = bReadPin112;
		//   break;
		  
		// case P113  :
		//   psDigIO->pfvLevelOn   = vSetPin113;
		//   psDigIO->pfvLevelOff  = vClearPin113;
		//   psDigIO->pfvToggle    = vTogglePin113;
		//   psDigIO->pfbGetLevel  = bReadPin113;
		//   break;
		  
		// case P200  :
		//   psDigIO->pfvLevelOn   = vSetPin200;
		//   psDigIO->pfvLevelOff  = vClearPin200;
		//   psDigIO->pfvToggle    = vTogglePin200;
		//   psDigIO->pfbGetLevel  = bReadPin200;
		//   break;

		// case P201  :
		//   psDigIO->pfvLevelOn   = vSetPin201;
		//   psDigIO->pfvLevelOff  = vClearPin201;
		//   psDigIO->pfvToggle    = vTogglePin201;
		//   psDigIO->pfbGetLevel  = bReadPin201;
		//   break;
		  
		// case P204  :
		//   psDigIO->pfvLevelOn   = vSetPin204;
		//   psDigIO->pfvLevelOff  = vClearPin204;
		//   psDigIO->pfvToggle    = vTogglePin204;
		//   psDigIO->pfbGetLevel  = bReadPin204;
		//   break;
		  
		// case P205  :
		//   psDigIO->pfvLevelOn   = vSetPin205;
		//   psDigIO->pfvLevelOff  = vClearPin205;
		//   psDigIO->pfvToggle    = vTogglePin205;
		//   psDigIO->pfbGetLevel  = bReadPin205;
		//   break;
		  
		// case P206  :
		//   psDigIO->pfvLevelOn   = vSetPin206;
		//   psDigIO->pfvLevelOff  = vClearPin206;
		//   psDigIO->pfvToggle    = vTogglePin206;
		//   psDigIO->pfbGetLevel  = bReadPin206;
		//   break;
		  
		// case P207  :
		//   psDigIO->pfvLevelOn   = vSetPin207;
		//   psDigIO->pfvLevelOff  = vClearPin207;
		//   psDigIO->pfvToggle    = vTogglePin207;
		//   psDigIO->pfbGetLevel  = bReadPin207;
		//   break;
		  
		// case P208  :
		//   psDigIO->pfvLevelOn   = vSetPin208;
		//   psDigIO->pfvLevelOff  = vClearPin208;
		//   psDigIO->pfvToggle    = vTogglePin208;
		//   psDigIO->pfbGetLevel  = bReadPin208;
		//   break;
		  
		// case P212  :
		//   psDigIO->pfvLevelOn   = vSetPin212;
		//   psDigIO->pfvLevelOff  = vClearPin212;
		//   psDigIO->pfvToggle    = vTogglePin212;
		//   psDigIO->pfbGetLevel  = bReadPin212;
		//   break;
		  
		// case P213  :
		//   psDigIO->pfvLevelOn   = vSetPin213;
		//   psDigIO->pfvLevelOff  = vClearPin213;
		//   psDigIO->pfvToggle    = vTogglePin213;
		//   psDigIO->pfbGetLevel  = bReadPin213;
		//   break;
		  
		// case P214  :
		//   psDigIO->pfvLevelOn   = vSetPin214;
		//   psDigIO->pfvLevelOff  = vClearPin214;
		//   psDigIO->pfvToggle    = vTogglePin214;
		//   psDigIO->pfbGetLevel  = bReadPin214;
		//   break;
		  
		// case P215  :
		//   psDigIO->pfvLevelOn   = vSetPin215;
		//   psDigIO->pfvLevelOff  = vClearPin215;
		//   psDigIO->pfvToggle    = vTogglePin215;
		//   psDigIO->pfbGetLevel  = bReadPin215;
		//   break;

		// case P300  :
		//   psDigIO->pfvLevelOn   = vSetPin300;
		//   psDigIO->pfvLevelOff  = vClearPin300;
		//   psDigIO->pfvToggle    = vTogglePin300;
		//   psDigIO->pfbGetLevel  = bReadPin300;
		//   break;
		  
		case P301  :
		  psDigIO->pfvLevelOn   = vSetPin301;
		  psDigIO->pfvLevelOff  = vClearPin301;
		  psDigIO->pfvToggle    = vTogglePin301;
		  psDigIO->pfbGetLevel  = bReadPin301;
		  break;
		  
		// case P302  :
		//   psDigIO->pfvLevelOn   = vSetPin302;
		//   psDigIO->pfvLevelOff  = vClearPin302;
		//   psDigIO->pfvToggle    = vTogglePin302;
		//   psDigIO->pfbGetLevel  = bReadPin302;
		//   break;
		  
		// case P303  :
		//   psDigIO->pfvLevelOn   = vSetPin303;
		//   psDigIO->pfvLevelOff  = vClearPin303;
		//   psDigIO->pfvToggle    = vTogglePin303;
		//   psDigIO->pfbGetLevel  = bReadPin303;
		//   break;
		  
		// case P304  :
		//   psDigIO->pfvLevelOn   = vSetPin304;
		//   psDigIO->pfvLevelOff  = vClearPin304;
		//   psDigIO->pfvToggle    = vTogglePin304;
		//   psDigIO->pfbGetLevel  = bReadPin304;
		//   break;

		// case P400  :
		//   psDigIO->pfvLevelOn   = vSetPin400;
		//   psDigIO->pfvLevelOff  = vClearPin400;
		//   psDigIO->pfvToggle    = vTogglePin400;
		//   psDigIO->pfbGetLevel  = bReadPin400;
		//   break;
		  
		// case P401  :
		//   psDigIO->pfvLevelOn   = vSetPin401;
		//   psDigIO->pfvLevelOff  = vClearPin401;
		//   psDigIO->pfvToggle    = vTogglePin401;
		//   psDigIO->pfbGetLevel  = bReadPin401;
		//   break;
		  
		// case P402  :
		//   psDigIO->pfvLevelOn   = vSetPin402;
		//   psDigIO->pfvLevelOff  = vClearPin402;
		//   psDigIO->pfvToggle    = vTogglePin402;
		//   psDigIO->pfbGetLevel  = bReadPin402;
		//   break;
		  
		// case P403  :
		//   psDigIO->pfvLevelOn   = vSetPin403;
		//   psDigIO->pfvLevelOff  = vClearPin403;
		//   psDigIO->pfvToggle    = vTogglePin403;
		//   psDigIO->pfbGetLevel  = bReadPin403;
		//   break;
		  
		// case P407  :
		//   psDigIO->pfvLevelOn   = vSetPin407;
		//   psDigIO->pfvLevelOff  = vClearPin407;
		//   psDigIO->pfvToggle    = vTogglePin407;
		//   psDigIO->pfbGetLevel  = bReadPin407;
		//   break;
		  
		// case P408  :
		//   psDigIO->pfvLevelOn   = vSetPin408;
		//   psDigIO->pfvLevelOff  = vClearPin408;
		//   psDigIO->pfvToggle    = vTogglePin408;
		//   psDigIO->pfbGetLevel  = bReadPin408;
		//   break;
		  
		// case P409  :
		//   psDigIO->pfvLevelOn   = vSetPin409;
		//   psDigIO->pfvLevelOff  = vClearPin409;
		//   psDigIO->pfvToggle    = vTogglePin409;
		//   psDigIO->pfbGetLevel  = bReadPin409;
		//   break;
		  
		// case P410  :
		//   psDigIO->pfvLevelOn   = vSetPin410;
		//   psDigIO->pfvLevelOff  = vClearPin410;
		//   psDigIO->pfvToggle    = vTogglePin410;
		//   psDigIO->pfbGetLevel  = bReadPin410;
		//   break;
		  
		// case P411  :
		//   psDigIO->pfvLevelOn   = vSetPin411;
		//   psDigIO->pfvLevelOff  = vClearPin411;
		//   psDigIO->pfvToggle    = vTogglePin411;
		//   psDigIO->pfbGetLevel  = bReadPin411;
		//   break;

		// case P500  :
		//   psDigIO->pfvLevelOn   = vSetPin500;
		//   psDigIO->pfvLevelOff  = vClearPin500;
		//   psDigIO->pfvToggle    = vTogglePin500;
		//   psDigIO->pfbGetLevel  = bReadPin500;
		//   break;
		  
		// case P501  :
		//   psDigIO->pfvLevelOn   = vSetPin501;
		//   psDigIO->pfvLevelOff  = vClearPin501;
		//   psDigIO->pfvToggle    = vTogglePin501;
		//   psDigIO->pfbGetLevel  = bReadPin501;
		//   break;
		  
		case P502  :
		  psDigIO->pfvLevelOn   = vSetPin502;
		  psDigIO->pfvLevelOff  = vClearPin502;
		  psDigIO->pfvToggle    = vTogglePin502;
		  psDigIO->pfbGetLevel  = bReadPin502;
		  break;

		// case P913  :
		//   psDigIO->pfvLevelOn   = vSetPin913;
		//   psDigIO->pfvLevelOff  = vClearPin913;
		//   psDigIO->pfvToggle    = vTogglePin913;
		//   psDigIO->pfbGetLevel  = bReadPin913;
		//   break;
		  
		// case P914  :
		//   psDigIO->pfvLevelOn   = vSetPin914;
		//   psDigIO->pfvLevelOff  = vClearPin914;
		//   psDigIO->pfvToggle    = vTogglePin914;
		//   psDigIO->pfbGetLevel  = bReadPin914;
		//   break;
		  
		// case P915  :
		//   psDigIO->pfvLevelOn   = vSetPin915;
		//   psDigIO->pfvLevelOff  = vClearPin915;
		//   psDigIO->pfvToggle    = vTogglePin915;
		//   psDigIO->pfbGetLevel  = bReadPin915;
		//   break;
		  
	    default :
		   break;
	}
 }
                       
                             
/********************************************************************************************************************
 *                                                                                                                  *
 *                    P U B L I C    F U N C T I O N    I M P L E M E N T A T I O N S                               *
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
			 ePullUp_t        ePullUp)
{ 
  psDigIO->ePin       = ePin;
  psDigIO->eDirection = eDirection;
  psDigIO->ePullUp    = ePullUp;
  psDigIO->pfvSetFunc = vSetPinFunc; 

  /* Set basis pins functions */ 
  vSetPinFunc(psDigIO);
}

/**
 * @brief Initialize a port
 * 
 * @param psPortObj         : Port object
 * @param ePort             : corresponding port
 * @param u16PortDirection  : set the direction of each pin of port . 
 */
void vInitPort(sPortIo_t* psPortObj, ioPort_t ePort, uint16_t u16PortDirection)
{
	psPortObj->ePort            = ePort;
	psPortObj->u16PortDirection = u16PortDirection;

    /* Initialization of port */
	switch(ePort)
	{
		case IO_PORT_0 : 
		  PORT0->PDR  = u16PortDirection;
		  break;

		case IO_PORT_1 : 
		  PORT1->PDR  = u16PortDirection;
		  break;

		case IO_PORT_2 : 
		  PORT2->PDR  = u16PortDirection;
		  break;

		case IO_PORT_3 : 
		  PORT3->PDR  = u16PortDirection;
		  break;

		case IO_PORT_4 : 
		  PORT4->PDR  = u16PortDirection;
		  break;

		case IO_PORT_5 : 
		  PORT5->PDR  = u16PortDirection;
		  break;

		case IO_PORT_9 :
		  PORT9->PDR  = u16PortDirection; 
		  break;
		
	    default :
		  // do nothing 
		  break;
	}
    /* set basis port functions */
	vSetPortFunc(psPortObj);
}

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
 */
void vIOSetInterrupt(  sIntIo_t*           IntObj, 
                       eIoPortPin_t        ePin)
{
	IntObj->ePin = ePin;

	vKintUnInit(IntObj);
	switch (ePin)
	{
		case P100:
			IntObj->pfvRegFunCbk = vKintP100Init;
			break;

		case P101:
			IntObj->pfvRegFunCbk = vKintP101Init;
			break;

		case P102:
			IntObj->pfvRegFunCbk = vKintP102Init;
			break;

		case P103:
			IntObj->pfvRegFunCbk = vKintP103Init;
			break;

		case P104:
			IntObj->pfvRegFunCbk = vKintP104Init;
			break;

		case P105:
			IntObj->pfvRegFunCbk = vKintP105Init;
			break;

		case P106:
			IntObj->pfvRegFunCbk = vKintP106Init;
			break;

		case P107:
			IntObj->pfvRegFunCbk = vKintP107Init;
			break;

		case P000:
			IntObj->pfvRegFunCbk = vIRQ6Init ;
			IntObj->pfvUnRegFuncbk = vIRQ6Disable;
			break;

		case P001:
			IntObj->pfvRegFunCbk = vIRQ7Init ;
			IntObj->pfvUnRegFuncbk = vIRQ7Disable;
			
			break;

		case P002:
			IntObj->pfvRegFunCbk = vIRQ2Init ;
			IntObj->pfvUnRegFuncbk = vIRQ2Disable;

			break;

		case P004:
			IntObj->pfvRegFunCbk = vIRQ3Init ;
			IntObj->pfvUnRegFuncbk = vIRQ3Disable;

			break;

		case P205:
			IntObj->pfvRegFunCbk = vIRQ1Init ;
			IntObj->pfvUnRegFuncbk = vIRQ1Disable;

			break;

		case P400:
			IntObj->pfvRegFunCbk = vIRQ0Init ;
			IntObj->pfvUnRegFuncbk = vIRQ0Disable;

			break;

		case P401:
			IntObj->pfvRegFunCbk = vIRQ5Init ;
			IntObj->pfvUnRegFuncbk = vIRQ5Disable;

			break;

		case P402:
			IntObj->pfvRegFunCbk = vIRQ4Init ;
			IntObj->pfvUnRegFuncbk = vIRQ4Disable;

			break;
			
		default:
			// do nothing
			break;
	}	
}

/** @brief       GPIO interrupt is generated in the event of a change of state of the following pins :
  *               ->PORT0 : P000, P001, P002 and P004 
  *               -> PORT1 : P100, P101, P102, P103, P104, P105, P106, P107 
  *               -> PORT2 : P205 
  *               -> PORT4 : P400, P401, P402 
 **/
void vIOInterruptHandler(void)
{
	vIRQ0InterruptHandler();
	vIRQ1InterruptHandler();
	vIRQ2InterruptHandler();
	vIRQ3InterruptHandler();
	vIRQ4InterruptHandler();
	vIRQ5InterruptHandler();
	vIRQ6InterruptHandler();
	vIRQ7InterruptHandler();
	vKintHandler();
}

/********************************************************************************************************************
 *                                                                                                                  *
 *                                          E N D   OF  M O D U L E                                                 *
 *                                                                                                                  *
 *******************************************************************************************************************/

/************************ Copyright (C) 2026 Trecspe.  All rights reserved. ****/
