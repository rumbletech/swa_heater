
/// \file

/**
 * @file
 * Author : Mohamed Yousry Mohamed RASAHAD .
 * Date : 7/2/2020
 * File : pic_tim1.c
 * 
 * Description : This File Contains Implementation of TIMER1/TIMER2/7SEG DISPLAY Initialization Functions
 * that set interrupt rates for TIM1/TIM2 , That Handle Many tasks in the Project [Electric Heater].
 */



/* Include TIM1 Header file */
#include "../incl/pic_tim1.h"



/** This Function Initializes TIMER1 So that it is Set to use no scalers at all , operate at FOSC /4 , which is 8MHZ /4 
  About 2MHZ , then a count of 0XFFFF , gets us at 32ms per Overflow which should be good ,
  for scanning the buttons , and prevent bouncing issues, as well as 3 of those overflows get us at 99 ms , which should be a good time 
 to start a conversion , given that conversion will take 11 cycles of its own , that should add up to 
 100ms per conversion  */


void TIM1_Init ( void )
{
    
    // Clear TIM1 Interrupt     
    PIR1 &= ~ ( 1 << _PIR1_TMR1IF_POSITION );
    // Enable Interrupt 
    PIE1 |= ( 1 << _PIE1_TMR1IE_POSITION );
    // Clear Counter 
    TMR1L = 0 ;
    TMR1H = 0 ;
    //Config
    T1CON = (( TIMER1_IN_SCALER << _T1CON_T1CKPS0_POSITION ) |
            ( TIMER1_SRC << _T1CON_TMR1CS_POSITION ) |
            ( TIMER1_SYNCH << _T1CON_T1INSYNC_POSITION ) |
            ( TIMER1_OSCEN << _T1CON_T1OSCEN_POSITION )|
            ( 1 << _T1CON_TMR1ON_POSITION )) ;
    
}



/** This Function Sets Up Timer2 In Timer Mode to Interrupt at compare Match , The Calculation is as follows 
 * Timer Per Compare = OUT_SCALER * 255 * ( IN_SCALER )/ (FOSC/4) 
 * which Approximates to something 8ms , which gives 120 HZ refresh , or 60 Scan rate per Digit .
 */
static void TIMER2_SETUP_60HZ ( void )
{
    //CLEAR INT FLAGS 
    PIR1 &= ~ ( 1 << _PIR1_TMR2IF_POSITION );
    //Enable Interrupts 
    PIE1 |= ( 1 << _PIE1_TMR2IE_POSITION );
    //Set Compare Match Value 
    PR2 = TIMER2_COMPARE_VAL ;
    //Start Timer 
    T2CON = (( TIMER2_OUT_SCALER << _T2CON_TOUTPS0_POSITION )| ( TIMER2_IN_SCALER << _T2CON_T2CKPS0_POSITION ) | 
            ( 1 << _T2CON_TMR2ON_POSITION ) );
    

}


/**
 * This Function Initializes the 2 DIGIT Segments and Their Respective Ports as well as initialize 
 * TIMER2 and its interrupts at a specified rate to be able to scan the digits .
 */

void DisplayInit( void )
{
    
 /* Initialize Pins */
    
    SEG_TRIS = 0 ; 
    DIS4_TRIS &= ~ ( 1 << DIS4_PIN );
    DIS3_TRIS &= ~ ( 1 << DIS3_PIN );
    DISABLE_SEG();
    
 /* Initialize Refresh Timer */
    
    TIMER2_SETUP_60HZ(); 
    
 /* Done */   
    
 return 0 ;
 
}


