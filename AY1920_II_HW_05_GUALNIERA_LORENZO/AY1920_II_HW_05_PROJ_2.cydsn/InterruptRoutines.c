/* ========================================
 *
 * In this file a custom interrupt is defined.
 * The purpose of this ISR is to handle LIS3DH
 * data retrieval, processing and transmission.
 * The ISR is sincronized with the data rate
 * of the accelerometer and is triggered by a
 * timer every 10ms (100Hz).
 *
 * -> Data retrieval (I2C): 
 * Readings of inertial measurements is archived 
 * using I2C communication. First the status 
 * register is read to check for new available data,
 * then low and high registers of the axis are
 * retrieved and stored in a temporary uint8 buffer.
 *
 * -> Data processing:
 * Low and high registers are merged together, then right
 * adjusted and stored in a signed 16-bit integer variable.
 * Being the measurement a signed 10-bit value, it ranges
 * from -512 to 511, representing an FSR of +-2g units. 
 * The value is then converted to a new scale of +-2000mg 
 * without losing data precision.
 *
 * -> Data transmission (UART):
 * All 3 axes processed measurements are divided in chunks
 * of 8-bit data each and placed in a buffer as follows:
 * 
 * [ HEADER | X_LOW | X_HIGH | Y_LOW | Y_HIGH | Z_LOW | Z_HIGH | TAIL ]
 *
 * for a total length of 64 bit to be send every 10ms, giving 
 * us a baudrate (or bitrate in this case) of 6400. To ensure 
 * a stable and reliable communication over UART, the data 
 * buffer is transmitted with a baudrate of 9600.
 *
 * ========================================
*/


/* Include project dependencies. */
#include "InterruptRoutines.h"


/* Custom ISR function to read, process and transmit LIS3DH inertial measurements data. */
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
        xAxis = MinMaxScaler(xAxis, -512, 512, -2000, 2000); // Convert value in mg units
        
        /* 
         * Read Y axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Y_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t yAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data
        yAxis = MinMaxScaler(yAxis, -512, 512, -2000, 2000); // Convert value in mg units
        
        /* 
         * Read Z axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Z_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int16_t zAxis = RightAdjustVal(tempBuffer, true, 6); // Merge Y axis low and high registers data
        zAxis = MinMaxScaler(zAxis, -512, 512, -2000, 2000); // Convert value in mg units
         
        /* 
         * Load and send 64-bit message containing all axes data over UART communication. 
         */
        LoadAxesData(dataBuffer, xAxis, yAxis, zAxis, DATA_BUFFER_HEADER, DATA_BUFFER_TAIL);
        UART_Debug_PutArray(dataBuffer, 8);
    }
}


/* [] END OF FILE */
