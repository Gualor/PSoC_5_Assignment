/* ========================================
 *
 * This header file has the purpose of setting
 * up the environment for the accelerometer
 * interrupt service routine:
 * 
 * -> ISR project dependencies;
 * -> ISR useful constants;
 * -> ISR global variables;
 * -> ISR function prototype;
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
    
    /* Header and tail for data buffer:
     * (0x70-0xF0)=112-bit message length. */
    #define DATA_BUFFER_HEADER 0x70
    #define DATA_BUFFER_TAIL 0xF0
    
    /* Data buffer to store message to be sent over UART. */
    uint8_t dataBuffer[14];
    
    /* Temporary data buffer to store low and high data registers. */
    uint8_t tempBuffer[2];
    
    /* Syncronize data transmission:
     * -> true: new data is available;
     * -> false: wait for new data to be read; */
    volatile bool packetReadyFlag;
        
    /* Store status register reading. */
    uint8 statusReg;
    
    /* Store I2C communication error. */
    ErrorCode error;
        
    /* Custom ISR prototype. */
    CY_ISR_PROTO(ISR_ACC_CUSTOM);
    
#endif

    
/* [] END OF FILE */
