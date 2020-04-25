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


/* Include project dependecies. */
#include "AccelUtils.h"



/* Return a 16-bit integer converted into a new scale defined by a min and max values. */
int16_t MinMaxScaler(int16_t num, int16_t oldMin, int16_t oldMax, int16_t newMin, int16_t newMax)
{
    /* Offset num to be positive. */
    float posNum = num - oldMin; 
    
    /* Current full scale range. */
    float oldScale = oldMax - oldMin;
    
    /* Target full scale range. */
    float newScale = newMax - newMin;
    
    /* Return number converted into the new scale. */
    return (int16_t)(posNum * (newScale/oldScale) + newMin);
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


/* [] END OF FILE */
