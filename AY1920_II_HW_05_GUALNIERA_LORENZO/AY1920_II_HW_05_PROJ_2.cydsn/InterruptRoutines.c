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
#include "AccelUtils.h"


/* Store status register reading. */
uint8 statusReg;

/* Store I2C communication error. */
ErrorCode error;

/* Data buffer to store message to be sent over UART. */
uint8_t dataBuffer[8];

/* Temporary data buffer to store low and high data registers. */
uint8_t tempBuffer[2];


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
         * TODO: Read X axis values over I2C communication and process the data. 
         */ 
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t xAxis = RightAdjustVal(tempBuffer, true, 6); // Merge X axis low and high registers data
        
        /* 
         * TODO: Read Y axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Y_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t yAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data    
        
        /* 
         * TODO: Read Z axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Z_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t zAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data
    }
}


/* [] END OF FILE */
