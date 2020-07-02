
/// \file


/**
 * @file
 * Author : Mohamed Yousry Mohamed Rashad
 * File : pic_adc.c
 * Date : 7/2/2020
 * 
 * This File Contains Basic Routines(Implementation) , that faciliate using the ADC Peripheral for the PIC Microcontroller,
 * Routines that do the following , get Interrupt flags , Enable/Disable Interrupts , Start Conversions , Initalization,
 * Channel Switching , etc .
 * 
 */

/* Include Header file for the module */
#include "../incl/pic_adc.h"

/**
 * This Function retrieves the interrupt flag of the ADC Module ( Set when conversion completes ).
 * @return returns non zero if the flag is set , returns zero if it is not set 
 */

uint8_t ADC_GetFlag ( void )
{
    return (PIR1 & ( 1 << _PIR1_ADIF_POSITION ) ) ;
    
 }

/**
 * This Function Clears , the Interrupt Flag Associated with the ADC Peripheral.
 */

void ADC_ClearFlag ( void )
{
    PIR1 &= ~ ( 1 << _PIR1_ADIF_POSITION );
}

/**
 * Enables the Interrupt related to the ADC Module .
 */
void ADC_EnableINT ( void )
{
    PIE1 |= ( 1 << _PIE1_ADIE_POSITION );
    
}

/**
 * Disables Interrupt related to the ADC Peripheral. 
 */
void ADC_DisableINT( void )
{
    PIE1 &= ~( 1 << _PIE1_ADIE_POSITION );
}



/**
 *  This Function Initiates a Conversion and doesn't return until the Conversion has finished .
 *  This Function is Blocking .
 * @return returns the result of the conversion ( only the first 10 bits are relevant ) . 
 */
uint16_t ADC_StartConv_B ( void )
{
    
    
    ADCON0 |= ( 1 << _ADCON0_GO_nDONE_POSITION );
    while ( ADCON0 & ( 1 <<_ADCON0_GO_nDONE_POSITION ));
    
    return ( ((uint16_t)ADRESL) | ( ((uint16_t)ADRESH) << 8 ) );

}

/**
 *  This Function Initiates a Conversion and  returns Immediately , it is up to the user to check 
 * if the operation has completed to get the result by either using an interrupt , or checking flags after some time .
 *  This Function is Non Blocking .
 * @return returns the result of the conversion ( only the first 10 bits are relevant ) . 
 */

void ADC_StartConv_NB( void )
{
    ADCON0 |= ( 1 << _ADCON0_GO_nDONE_POSITION );
}


/**
 * This Function Switches the Current channel of the adc module to the one specified in the parameter.
 * @param ch_num : channel number to switch to ( only valid numbers are from 0 to 7 ).
 */
void ADC_SelectCH ( uint8_t ch_num )
{   
    
    // Wait for ongoing Conversions to finish 
    while ( ADCON0 & ( 1 << _ADCON0_GO_nDONE_POSITION)); 
    //Disable ADC
    ADCON0 &= ~( 1 << _ADCON0_ADON_POSITION ); 
    //Clear Channel Field  
    ADCON0 &= ~( _ADCON0_CHS_MASK );
    ADCON0 |= ( ch_num << _ADCON0_CHS0_POSITION );
    //RE-ENABLE
    ADCON0 |= ( 1 << _ADCON0_ADON_POSITION ); 
    
}


/**
 *  This is a basic fill function , that initializes the ADC Perihperal using data provided in a configuration
 * structure , that is passed as a pointer .
 * @param config_s_ptr : a Pointer to an ADC_Config_S that Contains Initialization Information .
 * @return returns 0 if successful , returns -1 due to an assert error only if DEBUG_MODE is defined .
 */

int8_t ADC_Init ( ADC_Config_S * config_s_ptr )
{
    
#ifdef DEBUG_MODE 
    /*Assert Params */
    if ( (config_s_ptr->CH_sel > (ADC_NUM_CHANNELS -1 ) ) ||
            ( config_s_ptr->CKSEL_bf > 6 ) ||
            ( config_s_ptr->FMT_bf > 1 ) ||
            ( config_s_ptr->PCFG_bf > 15 ) )
    {
        return -1 ;
    }
    
#endif
    
   /* Write ADCON1 */ 
    
    ADCON1 = ( (config_s_ptr->FMT_bf << _ADCON1_ADFM_POSITION ) |
               (config_s_ptr->PCFG_bf << _ADCON1_PCFG_POSITION )|
               ((config_s_ptr->CKSEL_bf >> 2 ) << _ADCON1_ADCS2_POSITION) );
    
    
    /* Enable Interrupts for The Peripheral */
    
    if ( config_s_ptr->INT_enable )
    {
        // Clear Interrupt Flag
       ADC_ClearFlag();
       //Enable Interrupts 
        ADC_EnableINT();
    }
    /*Write ADCON0 */
   
    ADCON0 =  ( (config_s_ptr->CH_sel  << _ADCON0_CHS_POSITION ) |
                ((config_s_ptr->CKSEL_bf&4) << _ADCON0_ADCS0_POSITION) |
                ( 1 << _ADCON0_ADON_POSITION ) );
    
    
    /* Start Conversion Process if required and Interrupt is enabled */
    
    if ( config_s_ptr->INT_enable && config_s_ptr->convStart_Sel )
    {
        ADC_StartConv_NB();
    }
    
    return 0 ;
    

}






