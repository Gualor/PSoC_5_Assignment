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
    
    /* Return a 16-bit integer converted into a new scale defined by a min and max values. */
    int16_t MinMaxScaler(int16_t num, int16_t oldMin, int16_t oldMax, int16_t newMin, int16_t newMax);
    
    /* Merge lower and higher registers into a 16-bit right adjusted integer. */
    int16_t RightAdjustVal(uint8_t *data, bool lowerFirst, uint8_t adjustShift);
    
    /* Load axes data into a 64-bit data buffer packed as follows: 
     * DATA = [ HEADER | X_LOW | X_HIGH | Y_LOW | Y_HIGH | Z_LOW | L_HIGH | TAIL ]. */
    void LoadAxesData(uint8_t *data, int16_t x, int16_t y, int16_t z, uint8_t header, uint8_t tail);
    
    /* Unpack 16-bit val into 2 successive 8-bit addresses pointed by dataPtr. */
    void UnpackAxisData(int16_t val, uint8_t *data);
    
#endif


/* [] END OF FILE */
