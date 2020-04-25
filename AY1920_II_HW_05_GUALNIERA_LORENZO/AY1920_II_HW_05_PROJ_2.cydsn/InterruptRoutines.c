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

/* Include project dependencies. */
#include "InterruptRoutines.h"


/* Store status register reading. */
uint8 statusReg;

/* Store I2C communication error. */
ErrorCode error;


/* Custom ISR function to read LIS3DH data with I2C and send
 * it over UART communication with 64-bit messages. */
CY_ISR(ISR_ACC_CUSTOM)
{
    /* Bring interrupt line low. */
    ISR_Timer_ReadStatusRegister();

    /* Read accelerometer status register. */
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &statusReg);
    if (error == ERROR) return; // If error occurs return from the function
    
    /* If 3-axes accelerometer data is ready for reading. */
    if ((statusReg & LIS3DH_DATA_READY_MASK) == LIS3DH_DATA_READY_MASK)
    {
        /* 
         * TODO: read x,y,z values, process data, send data over uart
         */ 
        
    }
}


/* [] END OF FILE */
