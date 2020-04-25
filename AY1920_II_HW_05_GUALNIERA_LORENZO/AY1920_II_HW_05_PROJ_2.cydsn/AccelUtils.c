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
