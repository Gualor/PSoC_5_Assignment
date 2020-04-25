/** 
 * \file I2C_Interface.h
 * \brief Hardware specific I2C interface.
 *
 * This is an interface to the I2C peripheral. If you need to port 
 * this C-code to another platform, you could simply replace this
 * interface and still use the code.
 *
 * \author Davide Marzorati
 * \date September 12, 2019
*/

#ifndef I2C_Interface_H
    #define I2C_Interface_H
    
    #include "cytypes.h"
    #include "ErrorCodes.h"
    
    /* 7-bit I2C address of the slave device. */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /* Address of the WHO AM I register. */
    #define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

    /* Address of the Status register. */
    #define LIS3DH_STATUS_REG 0x27

    /* Address of the Control register 1. */
    #define LIS3DH_CTRL_REG1 0x20
    
    /* Address of the Control register 4. */
    #define LIS3DH_CTRL_REG4 0x23
   
    /////////////////todo
    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80

    /////////////////todo
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x57

    /////////////////todo
    #define LIS3DH_OUT_X_L 0x28
    
    /////////////////todo
    #define LIS3DH_OUT_Y_L 0x2A
    
    /////////////////todo
    #define LIS3DH_OUT_Z_L 0x2C
    
    /////////////////todo
    #define LIS3DH_DATA_READY_MASK 0x08 //TODO: 00001000
    
    /** \brief Start the I2C peripheral.
    *   
    *   This function starts the I2C peripheral so that it is ready to work.
    */
    ErrorCode I2C_Peripheral_Start(void);
    
    /** \brief Stop the I2C peripheral.
    *   
    *   This function stops the I2C peripheral from working.
    */
    ErrorCode I2C_Peripheral_Stop(void);
    
    /**
    *   \brief Read one byte over I2C.
    *   
    *   This function performs a complete reading operation over I2C from a single
    *   register.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the register to be read.
    *   \param data Pointer to a variable where the byte will be saved.
    */
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    
    /** 
    *   \brief Read multiple bytes over I2C.
    *   
    *   This function performs a complete reading operation over I2C from multiple
    *   registers.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the first register to be read.
    *   \param register_count Number of registers we want to read.
    *   \param data Pointer to an array where data will be saved.
    */
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data);
    /** 
    *   \brief Write a byte over I2C.
    *   
    *   This function performs a complete writing operation over I2C to a single 
    *   register.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the register to be written.
    *   \param data Data to be written
    */
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t data);
    
    /** 
    *   \brief Write multiple bytes over I2C.
    *   
    *   This function performs a complete writing operation over I2C to multiple
    *   registers
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the first register to be written.
    *   \param register_count Number of registers that need to be written.
    *   \param data Array of data to be written
    */
    ErrorCode I2C_Peripheral_WriteRegisterMulti(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data);
    
    /**
    *   \brief Check if device is connected over I2C.
    *
    *   This function checks if a device is connected over the I2C lines.
    *   \param device_address I2C address of the device to be checked.
    *   \retval Returns true (>0) if device is connected.
    */
    uint8_t I2C_Peripheral_IsDeviceConnected(uint8_t device_address);
    
#endif // I2C_Interface_H
/* [] END OF FILE */
