/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#ifndef INTERRUPT_ROUTINES_H
    
    /* Header guard. */
    #define INTERRUPT_ROUTINES_H
    
    /* Include project dependencies. */
    #include "project.h"
    #include "I2C_Interface.h"
    #include "AccelUtils.h"
    
    /* Header and tail for data buffer.
     * (0xA0-0xE0)=64 message bit length. */
    #define DATA_BUFFER_HEADER 0xA0
    #define DATA_BUFFER_TAIL 0xE0
    
    /* Data buffer to store message to be sent over UART. */
    uint8_t dataBuffer[8];
    
    /* Temporary data buffer to store low and high data registers. */
    uint8_t tempBuffer[2];
        
    /* Store status register reading. */
    uint8 statusReg;
    
    /* Store I2C communication error. */
    ErrorCode error;
        
    /* Custom ISR prototype. */
    CY_ISR_PROTO(ISR_ACC_CUSTOM);
    
#endif

    
/* [] END OF FILE */
