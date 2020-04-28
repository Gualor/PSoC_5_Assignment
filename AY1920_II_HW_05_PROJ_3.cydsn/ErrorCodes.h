/* ========================================
 *
 * Error codes definition.
 * This file contains several definition of 
 * error codes to be used throughout the 
 * project to be consisted with the written 
 * firmware.
 *
 * ========================================
*/


#ifndef __ERRORCODES_H
    
    /* Header guard. */
    #define __ERRORCODES_H
    
    /* ErrorCode
     * NO_ERROR -> 0
     * ERROR    -> 1 */
    typedef enum {
        NO_ERROR,   
        ERROR    
    } ErrorCode;

#endif


/* [] END OF FILE */
