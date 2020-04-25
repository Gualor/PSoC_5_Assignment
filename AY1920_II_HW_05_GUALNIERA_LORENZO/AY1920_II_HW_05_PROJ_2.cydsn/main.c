/*
 * In this file the main function is defined.
 * The purpose of the main is to setup peripherals
 * to ensure the correct functioning of the accelerometer
 * and properly retrieve/send inertial measurements data.
 *
 * PSoC setup:
 * -> Enable global interrupts;
 * -> Start I2C module;
 * -> Start UART module;
 * -> Start ISR timer;
 * -> Start accelerometer ISR;
 *
 * LIS3DH setup:
 * -> Scan devices connected to I2C bus;
 * -> Read status register;
 * -> Setup control register 1;
 * -> Setup control register 4;
 */

/* Include project dependencies. */
#include "stdio.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"


/* Main function. */
int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 

    /* Start I2C module. */
    I2C_Peripheral_Start();
    
    /* Start UART module. */
    UART_Debug_Start();
    
    /* The boot procedure takes 5ms after power-up. */
    CyDelay(5); 
    
    /* Check which devices are present on the I2C bus. */
    char message[50];
    for (int i = 0 ; i < 128; i++)
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            /* Print out the address in hex format. */
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_Debug_PutString(message); 
        }  
    }

    /* Read WHO_AM_I register. */
    uint8_t who_am_i_reg;
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_WHO_AM_I_REG_ADDR, 
                                                  &who_am_i_reg);
    if (error == NO_ERROR)
    {
        sprintf(message, "WHO_AM_I: 0x%02X [Expected: 0x33]\r\n", who_am_i_reg);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm\r\n");   
    }
    
    /* Read STATUS_REG register. */
    uint8_t status_register; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
    if (error == NO_ERROR)
    {
        sprintf(message, "STATUS_REG: 0x%02X\r\n", status_register);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read STATUS_REG\r\n");   
    }
    
    /* Read CTRL_REG1 register. */
    uint8_t ctrl_reg1; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg1);
    if (error == NO_ERROR)
    {
        sprintf(message, "CTRL_REG1 1: 0x%02X\r\n", ctrl_reg1);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read CTRL_REG1\r\n");   
    }
    
    /* 
     * Setup CTRL_REG1 register:
     * ODR[3:0] = 0101 -> Data rate 100Hz,
     * LPen     = 0    -> Normal mode,
     * Zen      = 1    -> Z-axis enable,
     * Yen      = 1    -> Y-axis enable,
     * Xen      = 1    -> X-axis enable. 
     */ 
    UART_Debug_PutString("\r\nWriting new values..\r\n");
    if (ctrl_reg1 != LIS3DH_NORMAL_MODE_CTRL_REG1)
    {
        ctrl_reg1 = LIS3DH_NORMAL_MODE_CTRL_REG1;
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG1,
                                             ctrl_reg1);   
        if (error == NO_ERROR)
        {
            sprintf(message, "CTRL_REG1 successfully written as: 0x%02X\r\n", ctrl_reg1);
            UART_Debug_PutString(message); 
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to set CTRL_REG1\r\n");   
        }
    }
    
    /* Read CTRL_REG4 register. */
    uint8_t ctrl_reg4;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    if (error == NO_ERROR)
    {
        sprintf(message, "CTRL_REG4: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read CTRL_REG4 4\r\n");   
    }
    
    /* 
     * Setup CTRL_REG4 register:
     * BDU     = 1  -> Block data update until MSB and LSB reading,
     * BLE     = 0  -> Data LSB at lower address,
     * FS[1:0] = 00 -> Full scale +-2g, 
     * HR      = 0  -> high-resolution disabled,
     * ST[1:0] = 00 -> Self-test disabled,
     * SIM     = 0  -> SPI 4-wire interface.
     */ 
    UART_Debug_PutString("\r\nWriting new values..\r\n");
    if (ctrl_reg4 != LIS3DH_CTRL_REG4_BDU_ACTIVE)
    {
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG4,
                                             ctrl_reg4);
        if (error == NO_ERROR)
        {
            sprintf(message, "CTRL_REG4 successfully written as: 0x%02X\r\n", ctrl_reg4);
            UART_Debug_PutString(message); 
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to read CTRL_REG4 4\r\n");   
        }
    }
    
    /* Wait 5ms after setup completion. */
    CyDelay(5);
    
    /* Start ISR timer, trigger interrupt every 10ms. */ 
    ISR_Timer_Start();
    
    /* Enable accelerometer custom interrupt. */
    ISR_Acc_StartEx(ISR_ACC_CUSTOM);
    
    /* Setup complete, do nothing. */
    for(;;)
    {
        
    }
    
    return 0;
}


/* [] END OF FILE */
