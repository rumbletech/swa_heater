/// \file

/**
 * @file 
 * File:   pic_tim1.h
 * Author: Mohamed Yousry Mohamed 
 *
 * This File contains TIMER1 and TIMER2 , Project Specific Initialization functions Prototypes ,for the electric heater project .
 * -TIMER1 :
 * -#Detecting Push Button Presses and Setting States Based on The Button Preesed .
 * -#Starting ADC Conversions .
 * -#Timing of Other Signals.
 * -# a Debounce time of 32 ms is Chosen to poll the buttons , and other timing is generated by multiple TIMER1 Interrupts .
 * -TIMER2 :
 * -#Handling Scanning of 7 Segment display Digits.
 * -#Since there are TWO Segments , Each will be Scanned at 60HZ , that means that TIMER2 Run at Approximately 120HZ.
 * Created on June 30, 2020, 3:36 AM
 */




/* Prevent Recursive Inclusion During Build */
#ifndef PIC_TIM1_TOKEN
#define	PIC_TIM1_TOKEN 1UL

/* Include Main Header File */
#include "../../config/pconfig.h"

/**@brief Selects FIRST DIGIT of the Display by enabling its line */
#define SELECT_FIRST_DIGIT() DIS4_PORT |= ( 1 << DIS4_PIN ); \
                             DIS3_PORT &= ~( 1 << DIS3_PIN)

/**@brief Selects the SECOND Digit of the DISPLAY by enabling its line */
#define SELECT_SECOND_DIGIT() DIS4_PORT &= ~( 1 << DIS4_PIN ); \
                             DIS3_PORT |=  ( 1 << DIS3_PIN )

 /**@brief Disables the SEGMENT Driver by Disabling TIMER2 and Clearing Segment Lines */                            
#define DISABLE_SEG()        T2CON&= ~ ( 1 << _T2CON_TMR2ON_POSITION );\
                             DIS4_PORT &= ~( 1 << DIS4_PIN ); \
                             DIS3_PORT &= ~ ( 1 << DIS3_PIN )

/**@brief RE-ENABLES TIMER2 To Restart the scanning */
#define ENABLE_SEG()         T2CON |= ( 1 << _T2CON_TMR2ON_POSITION )  

/*@brief Disables segment lines */
#define SELECT_OFF()         DIS4_PORT &= ~( 1 << DIS4_PIN ); \
                             DIS3_PORT &= ~ ( 1 << DIS3_PIN )

/**@brief DISABLES TIM1 By turning it off */
#define DISABLE_TIM1()      T1CON &= ~ ( 1 << _T1CON_TMR1ON_POSITION ) 

/**@brief ENABLES TIM1 BY TURNING IT ON */
#define ENABLE_TIM1()       T1CON |= ( 1 << _T1CON_TMR1ON_POSITION )
                            
/**@brief WRITES A VALUE TO THE SEGMENT PORT ,ACTUAL SEGMENT LINES ABCDEFGH AND DOT */
#define WRITE_DIGIT(ARG)        SEG_PORT = ARG ; 

/**@brief initialization routine for TIMER1 */
void TIM1_Init ( void );
/**@brief initialization routine for the SEGMENT Interface ( TIMER2 is Initialized ) and Ports are Configured .*/
void DisplayInit ( void ) ;

/* For C++ usage , to get C linkage */
#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/*PIC_TIM1_TOKEN*/

