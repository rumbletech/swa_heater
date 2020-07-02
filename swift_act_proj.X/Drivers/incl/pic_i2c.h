/// \file

/** @file 
 * File:   pic_i2c.h
 * Author: Mohamed Yousry Mohamed Rashad
 * 
 * This File Contains the Prototypes for the routines in pic_i2c.c , it also defines some types used to
 * initialize the i2c peripheral.
 * Created on June 30, 2020, 5:15 PM
 */




/*Prevent Recursive Inclusion */
#ifndef PIC_I2C_TOKEN
#define	PIC_I2C_TOKEN 1UL

/*Include Main Driver and Config Header */
#include "../../config/pconfig.h"

/// This Enum , defines the different modes of I2C that you can set in the PIC Microcontroller.
typedef enum 
{
    I2C_MODE_SLAVE_ADDR10_INTEN            = 0B1111 , ///< I2C Slave with 10 bit Address and Interrupts Enabled
    I2C_MODE_SLAVE_ADDR7_INTEN             = 0B1110 , ///< I2C Slave with 7 bit Address and Interrupts Enabled
    I2C_MODE_MASTER_FIRMWARE_CONTROLLED    = 0B1011 , ///< I2C Master , this Mode requires the user to define his own I2C Functions , the hardware only helps by detecting bus activity 
    I2C_MODE_MASTER_HARDWARE_CONTROLLED    = 0B1000 , ///< I2C Master , Hardware Controls the actual bus transfers , and user generates conditions like start,stop,etc .
    I2C_MODE_SLAVE_ADDR10                  = 0B0111 , ///< Slave Mode with 10 bit address and no interrupts enabled.
    I2C_MODE_SLAVE_ADDR7                   = 0B0110 , ///< Slave Mode with 7 bit address and no interrupts enabled.
    
    
} I2C_MODE_ET ; 

/// This Struct is used to initialize the I2C Module , by passing a pointer to a struct of this type to the init function .

typedef struct {
    
    I2C_MODE_ET I2C_mode   ; ///< I2C Mode Used .
    
    uint8_t     sla7_addr  ; ///< Slave Mode 7-Bit Addresss (ignored if I2C_mode is Master Mode ).
    
    uint16_t    sla10_addr ; ///< Slave Mode 10-Bit Addresss (ignored if I2C_mode is Master Mode ).
    
    uint32_t    I2C_freq   ; ///< I2C Baud Rate(Shouldn't Exceed 1MHZ) ( ignored if I2C_mode is Slave Mode or Firmware Mode ).
    
    uint8_t     I2C_Int_Enable ;///< Set it to anything but zero to enable Interrupts of MSSP Module during init , zero to disable.
    

} I2C_Config_S , * I2C_Config_SP ;



/**@brief : Initializes I2C Module , Using a Pointer to a Configuration Struct */
int8_t I2C_Init ( I2C_Config_S* i2ch );
/**@brief : Blocks until the i2c bus is idle again .*/
void I2C_Halt ( void );
/**@brief : Sends a Start Condition */
void I2C_Start ( void );
/**@brief : Sends a Stop Condition */
void I2C_Stop ( void );
/**@brief : Sends a Repeated Start Condition */
void I2C_Restart ( void );
/**@brief : Transmits a Byte and returns received ack bit */
int8_t I2C_Transmit( uint8_t bval );
/**@brief : Receives a byte via I2C and returns ACK in Response */
uint8_t I2C_Receive_ACK ( void );
/**@brief : Receives a byte via I2C and returns NACK in Response */
uint8_t I2C_Receive_NACK ( void );



/* C linkage , for cpp */
#ifdef	__cplusplus
extern "C" {
#endif

   
#ifdef	__cplusplus
}
#endif

#endif	/* PIC_I2C_TOKEN */

