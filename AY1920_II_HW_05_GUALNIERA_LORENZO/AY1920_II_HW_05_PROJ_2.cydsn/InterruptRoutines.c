/* ========================================
 *
 * MINMAXSCALER:
 * Convert read accelerometer axis value into +- 2000mG scale.
 * NB: The variable is a signed 10-bit integer, which means it ranges
 * from -512 to 511 (1024 values total, including zero) but in order to
 * line up the zeros in the two scales a max values of 512 has been adopted.
 *
 * ========================================
*/


/* Include project dependencies. */
#include "InterruptRoutines.h"


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
         * Read X axis values over I2C communication and process the data. 
         */ 
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t xAxis = RightAdjustVal(tempBuffer, true, 6); // Merge X axis low and high registers data
        xAxis = MinMaxScaler(xAxis, -512, 512, -2000, 2000); // Convert value in mG units
        
        /* 
         * Read Y axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Y_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t yAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data
        yAxis = MinMaxScaler(yAxis, -512, 512, -2000, 2000); // Convert value in mG units
        
        /* 
         * Read Z axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Z_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t zAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data
        zAxis = MinMaxScaler(zAxis, -512, 512, -2000, 2000); // Convert value in mG units
         
        /* 
         * Load and send 64-bit message containing all axes data over UART communication. 
         */
        LoadAxesData(dataBuffer, xAxis, yAxis, zAxis, DATA_BUFFER_HEADER, DATA_BUFFER_TAIL);
        UART_Debug_PutArray(dataBuffer, 8);
    }
}


/* [] END OF FILE */
