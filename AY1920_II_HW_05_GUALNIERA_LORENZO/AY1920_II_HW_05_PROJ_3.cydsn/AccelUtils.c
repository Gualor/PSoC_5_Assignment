/* ========================================
 *
 * This file contains utility functions to
 * process and convert raw LIS3DH inertial
 * measurements data.
 *
 * MinMaxScaler:
 * Convert accelerometer axis value to a new scale
 * defined by its minimum and maximum values.
 * 
 * RightAdjustVal:
 * Merge 2-bit lower and 8-bit higher registers into 
 * a single signed 16-bit right adjusted integer.
 * 
 * LoadAxesData:
 * Given 3-axes measurements data, header and tail,
 * pack the data in a 112-bit data buffer divided
 * in 8-bit chunks of data.
 *
 * UnpackAxisData:
 * Given a 32-bit axis value, unpack the data into
 * four 8-bit values and place them in four consecutive
 * addresses pointed by dataPtr.
 *
 * ========================================
*/


/* Include project dependencies. */
#include "AccelUtils.h"


/* Return a 16-bit integer converted into a new scale defined by a min and max values. */
float MinMaxScaler(float num, float oldMin, float oldMax, float newMin, float newMax)
{
    /* Offset num to be positive. */
    float posNum = num - oldMin; 
    
    /* Current full scale range. */
    float oldScale = oldMax - oldMin;
    
    /* Target full scale range. */
    float newScale = newMax - newMin;
    
    /* Return number converted into the new scale. */
    return (float)(posNum * (newScale/oldScale) + newMin);
}


/* Merge lower and higher registers into a 16-bit right adjusted integer. */
int16_t RightAdjustVal(uint8_t *data, bool lowerFirst, uint8_t adjustShift)
{
    /* If data is ordered with lower address data first. */
    if (lowerFirst == true)
    {
        return (int16_t)((data[0] | (data[1] << 8))) >> adjustShift;
    }
    /* If data is ordered with higher address data first. */
    else
    {
        return (int16_t)(((data[0] << 8) | data[1])) >> adjustShift;
    }
}


/* Load axes data into a 112-bit data buffer organized as follows: 
 *
 * DATA = [         HEADER        |  8-bit
          | X_1 | X_2 | X_3 | X_4 | 32-bit
          | Y_1 | Y_2 | Y_3 | Y_4 | 32-bit
          | Z_1 | Z_2 | Z_3 | Z_4 | 32-bit
          |          TAIL         ]  8-bit 
 */
void LoadAxesData(uint8_t *data, int32_t x, int32_t y, int32_t z, uint8_t header, uint8_t tail)
{
    /* Define axis vector to loop over. */
    int32_t axisVect[3] = {x, y, z};
    
    /* Load header and tail values into the buffer. */
    data[0] = header;
    data[13] = tail;
    
    /* Load axes values in the corresponding addresses in the buffer. */
    for (uint8_t i=0; i<3; i++)
    {
        /* Unpack 32-bit data into 4 separate 8-bit unsigned variables. */
        UnpackAxisData(axisVect[i], &data[1+i*4]);
    }
}


/* Unpack 32-bit val into 4 successive 8-bit addresses pointed by dataPtr. */
 void UnpackAxisData(int32_t val, uint8_t *dataPtr)
{
    /* Shift and mask byte depending on position. */
    for (uint8_t i=0; i<4; i++)
    {
        /* Increment data pointer and assign new value. */
        *(dataPtr+i) = (uint8_t)((val >> 8*i) & 0xFF);
    }
}


/* [] END OF FILE */
