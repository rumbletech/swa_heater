

/// \file

/* 
 * File:   eep.h
 * Author: Mohamed Yousry Mohamed Rashad
 * This File Contains 24C04 EEPROM read and write function prototypes as well as some related defines.
 * notice : not all the modes of the 24C04 are implemented or defined , only basic routines , that satisfy
 * the needs of the electric heater project .
 * 
 * Created on June 30, 2020, 8:31 PM
 */



#ifndef EEP_TOKEN
#define	EEP_TOKEN 1UL

/* Include Main Header File */
#include "../../config/pconfig.h"

#define HARDWIRED_ADDRESS 0B00 // A1 , A2 PINS ARE Connected to Ground on the Genios Board
#define DEVICE_ADDRESS (0B10100000 | ( HARDWIRED_ADDRESS << 2 )) //DEVICE ADDRESS
#define DEVICE_WRITE 0 // I2C WRITE = 0
#define DEVICE_READ 1  // I2C READ  = 1

/** @brief This Function Writes a single byte to an address in the address space of the eeprom */
int8_t eepByteWrite( uint8_t bval , uint16_t Addr );
/**@brief This Function Reads a byte from an address in the address space of the eeprom */
int16_t eepByteRead( uint16_t Addr );


/* C Linkage for CPLULUS Functions if we are using cpp , in which we are not */
#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* END EEP_TOKEN */

