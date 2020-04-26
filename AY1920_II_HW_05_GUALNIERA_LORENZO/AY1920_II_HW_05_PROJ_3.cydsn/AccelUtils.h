/* ========================================
 *
 * This header file is used to define utility
 * function prototypes regarding the processing
 * and data conversion of the LIS3DH inertial
 * measurements raw data.
 *
 * ========================================
*/


#ifndef ACCEL_UTILS_H
    
    /* Header guard. */
    #define ACCEL_UTILS_H
    
    /* Include project dependencies. */
    #include "project.h"
    #include "stdbool.h"
    
    /* Gravitational acceleration physic constant. */
    #define G_ACCELERATION 9.80665
    
    /* LIS3DH inertial measurements raw scale. */
    #define LIS3DH_RAW_FSR 2048
    
    /* LIS3DH m/s^2 conversion scale. */
    #define LIS3DH_4G_FSR 4*G_ACCELERATION
    
    /* Return a 16-bit integer converted into a new scale defined by a min and max values. */
    float MinMaxScaler(float num, float oldMin, float oldMax, float newMin, float newMax);
    
    /* Merge lower and higher registers into a 16-bit right adjusted integer. */
    int16_t RightAdjustVal(uint8_t *data, bool lowerFirst, uint8_t adjustShift);
    
    /* Load axes data into a 112-bit data buffer organized as follows: 
     * DATA = [         HEADER        |  8-bit
              | X_1 | X_2 | X_3 | X_4 | 32-bit
              | Y_1 | Y_2 | Y_3 | Y_4 | 32-bit
              | Z_1 | Z_2 | Z_3 | Z_4 | 32-bit
              |          TAIL         ]  8-bit */
    void LoadAxesData(uint8_t *data, float x, float y, float z, uint8_t header, uint8_t tail);
    
    /* Unpack float val into 4 successive 8-bit addresses pointed by dataPtr. */
    void UnpackAxisData(float val, uint8_t *dataPtr);
    
#endif


/* [] END OF FILE */
