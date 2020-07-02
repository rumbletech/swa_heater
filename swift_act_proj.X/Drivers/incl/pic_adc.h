
/// \file

/**
 * @file 
 * File:   pic_adc.h
 * Author: Mohamed Yousry Mohamed 
 *
 * Created on June 29, 2020, 6:57 PM
 * 
 * Description :
 * The File Includes ADC Module Definitions , Function Prototypes , and type definitions , for the PIC16F877A Microcontroller or similar Micro-controllers .
 * 
 */

/* Prevent Recursive Inclusion */
#ifndef PIC_ADC_TOKEN 
#define	PIC_ADC_TOKEN 1UL

/* Include Main Header File */
#include "../../config/pconfig.h"

/* Definitons from the Datasheet */

#define ADC_NUM_CHANNELS 8UL  //Number of ADC Channels 

/** This Enum Contains Clock Selection Options for the ADC Module */
typedef enum {
    
    ADC_CKSEL_FOSC_DIV2  = 0B000 , ///< FOSC DIVIDED BY 2 
    ADC_CKSEL_FOSC_DIV8  = 0B001 , ///< FOSC DIVIDED BY 8 
    ADC_CKSEL_FOSC_DIV32 = 0B010 , ///< FOSC DIVIDED BY 32 
    ADC_CKSEL_FOSC_RC    = 0B011 , ///< Driven by the Internal RC Oscillator
    ADC_CKSEL_FOSC_DIV4  = 0B100 , ///< FOSC DIVIDED BY 4 
    ADC_CKSEL_FOSC_DIV16 = 0B101 , ///< FOSC DIVIDED BY 16 
    ADC_CKSEL_FOSC_DIV64 = 0B110 , ///< FOSC DIVIDED BY 64
             
} ADC_CKSEL_ET ;


/** This Enum Contains Port Configuration is according to the analog in to reference ratio 
 * Reference pins are always AN3 for Positive and AN2 for Negative
 * A stands for Analog Pin , D for Digital , R for Reference Pin */

typedef enum {
    
    ADC_PCFG_CR_80 = 0B0000 , ///< Port Shape : AAAAAAAA 
    ADC_PCFG_CR_71 = 0B0001 , ///< Port Shape : AAAARAAA 
    ADC_PCFG_CR_50 = 0B0010 , ///< Port Shape : DDDAAAAA 
    ADC_PCFG_CR_41 = 0B0011 , ///< Port Shape : DDDARAAA           
    ADC_PCFG_CR_30 = 0B0100 , ///< Port Shape : DDDDADAA 
    ADC_PCFG_CR_21 = 0B0101 , ///< Port Shape : DDDDRDAA     
    ADC_PCFG_CR_00 = 0B0110 , ///< Port Shape : DDDDDDDD      
    ADC_PCFG_CR_62 = 0B1000 , ///< Port Shape : AAAARRAA 
    ADC_PCFG_CR_60 = 0B1001 , ///< Port Shape : DDAAAAAA 
    ADC_PCFG_CR_51 = 0B1010 , ///< Port Shape : DDAARAAA 
    ADC_PCFG_CR_42 = 0B1011 , ///< Port Shape : DDAARRAA 
    ADC_PCFG_CR_32 = 0B1100 , ///< Port Shape : DDDARRAA 
    ADC_PCFG_CR_22 = 0B1101 , ///< Port Shape : DDDDRRAA             
    ADC_PCFG_CR_10 = 0B1110 , ///< Port Shape : DDDDDDDA 
    ADC_PCFG_CR_12 = 0B1111 , ///< Port Shape : DDDDRRDA 

     
} ADC_PCFG_ET ;


/**@brief This Enum Contains Options for Right adjusted result format or left adjusted */
typedef enum {
    
    ADC_FMT_RADJ = 1 , ///< Conversion Result is Right Adjusted .
    ADC_FMT_LADJ = 0 , ///< Conversion Result is Left Adjusted .
    
    
} ADC_FMTSEL_ET ;



/**@brief This Struct  Contains Configuration Information for the ADC Module */

typedef struct {
    
    
   ADC_CKSEL_ET  CKSEL_bf ; ///< Clock Selection Option , one of ADC_CKSEL_ET Enum Values may be used .
   
   ADC_PCFG_ET   PCFG_bf  ; ///< Port Configuration Option , one of ADC_PCFG_ET Enum Values may be used.
   
   ADC_FMTSEL_ET FMT_bf   ; ///< Result Format Option , one of ADC_FMTSEL_ET Enum Values may be used
   
   uint8_t       CH_sel   ; ///< Channel to be selected , when init function is called with this struct.
   
   uint8_t       INT_enable ;  ///< if this field is non zero , interrupts are enabled , if it is zero it is ignored .
   
   uint8_t       convStart_Sel ; ///< if this field is non zero , a conversion is started following the init function , if it is zero it is ignored.
   
} ADC_Config_S , * ADC_Config_SP ;

/** Disables the ADC Module */
#define DISABLE_ADC() ADCON0 &= ~ ( 1 << _ADCON0_ADON_POSITION )
/** Enables the ADC Module */
#define ENABLE_ADC()  ADCON0 |= ( 1 << _ADCON0_ADON_POSITION  )
//Functions

/**@brief Gets the ADC Peripheral Flag bit */
uint8_t ADC_GetFlag ( void );
/**@brief Clears ADC Conversion Complete Flag */
void ADC_ClearFlag ( void );
/**@brief Enables ADC Interrupts  */
void ADC_EnableINT ( void );
/**@brief Disables ADC Interrupts */
void ADC_DisableINT( void );
/**@brief Initializes the ADC Peripheral using data contained in ADC_Config_S Struct passed by reference. */
int8_t ADC_Init ( ADC_Config_S * config_s_ptr ) ;
/**@brief Starts a Conversion and returns the result , this function is blocking. */
uint16_t ADC_StartConv_B ( void );
/**@brief Starts a Conversion and returns immediately  , this function is non blocking. */
void ADC_StartConv_NB( void );


/* C Linkage for CPP if needed */
#ifdef	__cplusplus
extern "C" {
#endif
    
/* CPP , C Linkage functions here */    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PIC_ADC_TOKEN */

