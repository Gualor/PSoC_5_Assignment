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


#ifndef ACCEL_UTILS_H
    
    /* Header guard. */
    #define ACCEL_UTILS_H
    
    /* Include project dependencies. */
    #include "project.h"
    #include "stdbool.h"
    
    /* Function prototypes. */
    int16_t MinMaxScaler(int16_t num, int16_t oldMin, int16_t oldMax, int16_t newMin, int16_t newMax);
    int16_t RightAdjustVal(uint8_t *data, bool lowerFirst, uint8_t adjustShift);
    void LoadAxesData(uint8_t *data, int16_t x, int16_t y, int16_t z, uint8_t header, uint8_t tail);
    void UnpackAxisData(int16_t val, uint8_t *data);
    
#endif


/* [] END OF FILE */
