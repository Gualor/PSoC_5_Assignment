/*******************************************************************************
* File Name: CLOCK_TIMER.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CLOCK_TIMER_H)
#define CY_CLOCK_CLOCK_TIMER_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void CLOCK_TIMER_Start(void) ;
void CLOCK_TIMER_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CLOCK_TIMER_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CLOCK_TIMER_StandbyPower(uint8 state) ;
void CLOCK_TIMER_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CLOCK_TIMER_GetDividerRegister(void) ;
void CLOCK_TIMER_SetModeRegister(uint8 modeBitMask) ;
void CLOCK_TIMER_ClearModeRegister(uint8 modeBitMask) ;
uint8 CLOCK_TIMER_GetModeRegister(void) ;
void CLOCK_TIMER_SetSourceRegister(uint8 clkSource) ;
uint8 CLOCK_TIMER_GetSourceRegister(void) ;
#if defined(CLOCK_TIMER__CFG3)
void CLOCK_TIMER_SetPhaseRegister(uint8 clkPhase) ;
uint8 CLOCK_TIMER_GetPhaseRegister(void) ;
#endif /* defined(CLOCK_TIMER__CFG3) */

#define CLOCK_TIMER_Enable()                       CLOCK_TIMER_Start()
#define CLOCK_TIMER_Disable()                      CLOCK_TIMER_Stop()
#define CLOCK_TIMER_SetDivider(clkDivider)         CLOCK_TIMER_SetDividerRegister(clkDivider, 1u)
#define CLOCK_TIMER_SetDividerValue(clkDivider)    CLOCK_TIMER_SetDividerRegister((clkDivider) - 1u, 1u)
#define CLOCK_TIMER_SetMode(clkMode)               CLOCK_TIMER_SetModeRegister(clkMode)
#define CLOCK_TIMER_SetSource(clkSource)           CLOCK_TIMER_SetSourceRegister(clkSource)
#if defined(CLOCK_TIMER__CFG3)
#define CLOCK_TIMER_SetPhase(clkPhase)             CLOCK_TIMER_SetPhaseRegister(clkPhase)
#define CLOCK_TIMER_SetPhaseValue(clkPhase)        CLOCK_TIMER_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CLOCK_TIMER__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CLOCK_TIMER_CLKEN              (* (reg8 *) CLOCK_TIMER__PM_ACT_CFG)
#define CLOCK_TIMER_CLKEN_PTR          ((reg8 *) CLOCK_TIMER__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CLOCK_TIMER_CLKSTBY            (* (reg8 *) CLOCK_TIMER__PM_STBY_CFG)
#define CLOCK_TIMER_CLKSTBY_PTR        ((reg8 *) CLOCK_TIMER__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CLOCK_TIMER_DIV_LSB            (* (reg8 *) CLOCK_TIMER__CFG0)
#define CLOCK_TIMER_DIV_LSB_PTR        ((reg8 *) CLOCK_TIMER__CFG0)
#define CLOCK_TIMER_DIV_PTR            ((reg16 *) CLOCK_TIMER__CFG0)

/* Clock MSB divider configuration register. */
#define CLOCK_TIMER_DIV_MSB            (* (reg8 *) CLOCK_TIMER__CFG1)
#define CLOCK_TIMER_DIV_MSB_PTR        ((reg8 *) CLOCK_TIMER__CFG1)

/* Mode and source configuration register */
#define CLOCK_TIMER_MOD_SRC            (* (reg8 *) CLOCK_TIMER__CFG2)
#define CLOCK_TIMER_MOD_SRC_PTR        ((reg8 *) CLOCK_TIMER__CFG2)

#if defined(CLOCK_TIMER__CFG3)
/* Analog clock phase configuration register */
#define CLOCK_TIMER_PHASE              (* (reg8 *) CLOCK_TIMER__CFG3)
#define CLOCK_TIMER_PHASE_PTR          ((reg8 *) CLOCK_TIMER__CFG3)
#endif /* defined(CLOCK_TIMER__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CLOCK_TIMER_CLKEN_MASK         CLOCK_TIMER__PM_ACT_MSK
#define CLOCK_TIMER_CLKSTBY_MASK       CLOCK_TIMER__PM_STBY_MSK

/* CFG2 field masks */
#define CLOCK_TIMER_SRC_SEL_MSK        CLOCK_TIMER__CFG2_SRC_SEL_MASK
#define CLOCK_TIMER_MODE_MASK          (~(CLOCK_TIMER_SRC_SEL_MSK))

#if defined(CLOCK_TIMER__CFG3)
/* CFG3 phase mask */
#define CLOCK_TIMER_PHASE_MASK         CLOCK_TIMER__CFG3_PHASE_DLY_MASK
#endif /* defined(CLOCK_TIMER__CFG3) */

#endif /* CY_CLOCK_CLOCK_TIMER_H */


/* [] END OF FILE */
