
/// \file
/*!
 * @file
 *  Author : Mohamed Yousry Mohamed Rashad
 *  Date : 7/2/2020
 *  This File , Contains I2C Communication Routines for the PIC16F877A ,
 * It contains the Implementations for :
 * -# an Init Function ,
 * -# a Master Transmit Function ,
 * -# a Master Receive with ACK Function , 
 * -# a Master Receive with NACK Function ,
 * 
 *  This routines here are mainly used by the 24C04 EEPROM Functions in eep.c
 *  This Driver Doesn't Implement Slave Mode or Firmware mode as they are not required by the electric heater project . 
 *  File_Name : pic_i2c.c
 *  Related_Header : pic_i2c.h  
 
 */

/* Include Related Header file which links to the main header */
#include "../incl/pic_i2c.h"





/**
 * @brief This Function Initializes the I2C Module within the PIC16F877A , 
 * @param i2ch : Pointer to an I2C Configuration Struct used to Initialize the I2C Module 
 * @return  returns 0 if successful returns -1 if there is an assertion problem if DEBUG_MODE is defined
 */

int8_t I2C_Init ( I2C_Config_S* i2ch )
{
#ifdef DEBUG_MODE
    /* Asssert Params Passed to Init */
    if ( !((i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR10_INTEN )||
          (i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR7_INTEN  )||
          (i2ch->I2C_mode == I2C_MODE_MASTER_FIRMWARE_CONTROLLED  )||
          (i2ch->I2C_mode == I2C_MODE_MASTER_HARDWARE_CONTROLLED  )||
          (i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR10  )||
          (i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR7  ) ) || (i2ch->I2C_freq > 1000000UL ) || ( i2ch->sla7_addr > 127 ) ){
        return -1 ;
    }
    
           
#endif
    
    
    if ( i2ch->I2C_Int_Enable )
    {
        /* Clear Interrupt Flag */
        PIR1 &= ~ ( 1 << _PIR1_SSPIF_POSITION );
        
        /* Set Interrupt */
        PIE1 |= ( 1 << _PIE1_SSPIE_POSITION );  
    }

    /* Set Baudrate or Address if in slave mode */
    
    if ( i2ch->I2C_mode == I2C_MODE_MASTER_HARDWARE_CONTROLLED )
    {
        /* Write Clock Val */
        SSPADD = (( (_XTAL_FREQ / 4 )/( i2ch->I2C_freq ) ) -1 );
        
    }
    else if ( i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR7_INTEN || 
              i2ch->I2C_mode == I2C_MODE_SLAVE_ADDR7    )
    {
        SSPADD = i2ch->sla7_addr ; 
    }
    
    /* SDA , SCL LINES ARE INPUTS */
    TRISC3 = 1 ;
    TRISC4 = 1 ; 
    /* WRITE CONTROL REG */
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPCON = (( i2ch->I2C_mode << _SSPCON_SSPM0_POSITION )|(  1 << _SSPCON_SSPEN_POSITION )) ;
    
    return 0 ; 
    
}

/**
 * This Function is used to Block(halt) execution until the i2c bus is idle .
 * Functions using the I2C Module for Transmit/Receive Should Call this Function Before taking an action
 * on the bus to ensure that the bus is idle beforehand.
 * This function is blocking.
 */
void I2C_Halt ( void )
{
    while ( (SSPSTAT&( 1 << _SSPSTAT_READ_WRITE_POSITION)) || ( SSPCON2 & (_SSPCON2_ACKEN_MASK | _SSPCON2_SEN_MASK | _SSPCON2_RSEN_MASK | _SSPCON2_RCEN_MASK | _SSPCON2_PEN_MASK)) );
}

/** This Function will send a start condition on the i2c bus , it uses I2C_Halt() 
 * This function is blocking.*/

 void I2C_Start ( void )
{
    I2C_Halt();
    SSPCON2 |= ( 1 << _SSPCON2_SEN_POSITION );

    
}
/** This Function will send a stop condition on the i2c bus , it uses I2C_Halt() 
 * This function is blocking.*/
 void I2C_Stop ( void )
{
        I2C_Halt();
        SSPCON2 |= ( 1 << _SSPCON2_PEN_POSITION );

 
}

/** This Function will send a repeated start condition on the i2c bus , it uses I2C_Halt() 
 * This function is blocking.*/
 void I2C_Restart ( void )
{       
        I2C_Halt();
        SSPCON2 |= ( 1 << _SSPCON2_RSEN_POSITION );

    
}

 /**
  * This Function Transmits a single byte on the I2C Bus , it uses I2C_Halt() so it is blocking .
  * @param bval : byte to be transmitted on the I2C Bus .
  * @return returns 1 if the device returned NAK , returns 0 if device responded with ack .
  */
int8_t I2C_Transmit( uint8_t bval )
{
    I2C_Halt();
    SSPBUF = bval ;
    

    if ( SSPCON2 & ( 1 << _SSPCON2_ACKSTAT_POSITION ) )
    {
        return 1 ; //NAK 
    }
        return 0 ; //DEVICE AKED 
 
}

/**
 *  This Function performs a (Master Receive) Operation and gets a byte from the I2C Bus , it returns an
 * ACK(ACKNOWLEDGE) as a response to the byte received .
 * This Function uses I2C_Halt() so it is blocking .
 * @return returns the byte received from the I2C Bus . 
 */

uint8_t I2C_Receive_ACK ( void )
{   
    uint8_t temp ;
    I2C_Halt();
    //Enable Reception 
    SSPCON2 |= ( 1 << _SSPCON2_RCEN_POSITION );
    // Wait until it finishes
    I2C_Halt();
    temp = SSPBUF ;
    I2C_Halt();
    //Send Ack
    SSPCON2&= ~( 1 << _SSPCON2_ACKDT_POSITION );
    SSPCON2 |= ( 1 << _SSPCON2_ACKEN_POSITION );
    while ( SSPCON2 & ( 1 <<  _SSPCON2_ACKEN_POSITION)) ;
    
    return SSPBUF ; 
    
}
        
        
/**
 *  This Function performs a (Master Receive) Operation and gets a byte from the I2C Bus , it returns a
 * NACK( NOT ACKNOWLEDGE) as a response to the byte received .
 * This Function uses I2C_Halt() so it is blocking .
 * @return returns the byte received from the I2C Bus . 
 */        
        
        
uint8_t I2C_Receive_NACK ( void )
{
    
    uint8_t temp ;
    I2C_Halt();
    //Enable Reception 
    SSPCON2 |= ( 1 << _SSPCON2_RCEN_POSITION );
    // Wait until it finishes
    I2C_Halt();
    temp = SSPBUF ; 
    I2C_Halt();
    //Send Ack
    SSPCON2 |= ( 1 << _SSPCON2_ACKDT_POSITION );
    SSPCON2 |= ( 1 << _SSPCON2_ACKEN_POSITION );
    return temp ; 
}
