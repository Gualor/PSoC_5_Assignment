/* ========================================
 *
 * In this file a custom interrupt is defined.
 * The purpose of this ISR is to handle LIS3DH
 * data retrieval, processing and packing.
 * The ISR is syncronized with the data rate
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
 * Being the measurement a signed 12-bit value, it ranges
 * from -2048 to 2047, representing an FSR of +-4g units. 
 * The value is then converted in um/s^2 units 
 * (10^-6 * m/s^2) without losing data precision.
 *
 * -> Data packing:
 * All 3 axes processed measurements are divided in 4 chunks
 * of 8-bit data each and placed in a buffer as follows:
 * 
 * DATA = [         HEADER        |  8-bit
 *        | X_1 | X_2 | X_3 | X_4 | 32-bit
 *        | Y_1 | Y_2 | Y_3 | Y_4 | 32-bit
 *        | Z_1 | Z_2 | Z_3 | Z_4 | 32-bit
 *        |          TAIL         ]  8-bit 
 *
 * for a total length of 112 bit of new data available 
 * for UART transmission every 10ms.
 *
 * ========================================
*/


/* Include project dependencies. */
#include "InterruptRoutines.h"


/* Custom ISR function to read, process and pack LIS3DH inertial measurements data. */
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
        int32_t xAxis = RightAdjustVal(tempBuffer, true, 4); // Merge X axis low and high registers data
        xAxis = MinMaxScaler(xAxis, -ACC_RAW_SCALE, ACC_RAW_SCALE, -ACC_UMS2_SCALE, ACC_UMS2_SCALE); // Convert value in mm/s^2 units
        
        /* 
         * Read Y axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Y_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int32_t yAxis = RightAdjustVal(tempBuffer, true, 4); // Merge Y axis low and high registers data
        yAxis = MinMaxScaler(yAxis, -ACC_RAW_SCALE, ACC_RAW_SCALE, -ACC_UMS2_SCALE, ACC_UMS2_SCALE); // Convert value in mm/s^2 units
        
        /* 
         * Read Z axis values over I2C communication and process the data. 
         */
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_Z_L, 2, &tempBuffer[0]);
        if (error == ERROR) return; // If error occurs return from the function
        int32_t zAxis = RightAdjustVal(tempBuffer, true, 4); // Merge Z axis low and high registers data
        zAxis = MinMaxScaler(zAxis, -ACC_RAW_SCALE, ACC_RAW_SCALE, -ACC_UMS2_SCALE, ACC_UMS2_SCALE); // Convert value in mm/s^2 units
        
        /* 
         * Load 112-bit message containing all axes data to be send in main function over UART comm. 
         */
        LoadAxesData(dataBuffer, xAxis, yAxis, zAxis, DATA_BUFFER_HEADER, DATA_BUFFER_TAIL);
        packetReadyFlag = true; // New data ready for transmission
    }
}


/* [] END OF FILE */
