

/// \file

/**
 * @file
 * Author : Mohamed Yousry Mohamed Rashad
 * File : eep.c
 * Date : 7/2/2020
 * 
 * Description : This File Contains EEPWRITE AND EEPREAD Function Implementation for the 24C04 4K BITS
 * CAPACITY EEPROM , it is not compatible with other types , only these 2 functions are implemented as
 * it is only needed to write and read a few bytes , from the eeprom , so burst read/write methods
 * are ignored .
 * 
 * This File Uses pic_i2c.c Functions .
 * 
 */
/* Include Associated Header file */
#include "../incl/eep.h"



/**
 *  This Function Writes a single byte to some address in the address space , of the eeprom .
 * @param bval : byte to be written to the eeprom .
 * @param Addr : eeprom memory address , to write to, notice ( only first 9 bits are relevant ) due to eeprom capacity .
 * @return Returns 0 if Operation was successful , returns -1 if the device returned NACK a request .
 */
int8_t eepByteWrite( uint8_t bval , uint16_t Addr )
{
    uint8_t error_check = 0 ;
    //Start 
    I2C_Start();
    //Send Device Address
    error_check += I2C_Transmit( DEVICE_ADDRESS | DEVICE_WRITE |( (uint8_t)(( Addr >> 7 )&2 ) ));
    error_check += I2C_Transmit( (uint8_t) Addr );
    error_check += I2C_Transmit( bval );
    //STOP 
    I2C_Stop();
    if ( !error_check )
    {
        return 0 ;
    }
    
    return -1 ; 
}


/**
 *  This Function Reads a single byte from some address in the address space , of the eeprom .
 * @param Addr : eeprom memory address , to read from, notice ( only first 9 bits are relevant ) due to eeprom capacity .
 * @return Returns the read byte if Operation was successful , returns -1 if the device returned NACK a request .
 */

 int16_t eepByteRead( uint16_t Addr )
 {
     
     uint8_t error_check = 0 ;
     //Start
     I2C_Start();
     //Dummy Write 
     error_check += I2C_Transmit( DEVICE_ADDRESS | DEVICE_WRITE |( (uint8_t)(( Addr >> 7 )&2 ) ));
     error_check += I2C_Transmit( (uint8_t) Addr );
     //Restart 
     I2C_Restart();
     //Send Read
     error_check += I2C_Transmit( DEVICE_ADDRESS | DEVICE_READ |( (uint8_t)(( Addr >> 7 )&2 ) ));
     //Read Byte
     uint8_t temp ;
     temp = I2C_Receive_NACK();
     //STOP
     I2C_Stop();
     
     if ( !error_check )
     {
         
         return temp ;
     }

     return -1  ;
     
 }
