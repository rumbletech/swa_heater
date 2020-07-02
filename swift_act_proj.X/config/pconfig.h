
/// \file
/**
 * @file
 * Author : Mohamed Yousry Mohamed Rashad .
 * Date : 6/29/2020 
 * File : pconfig.h
 * This is a Configuration file for the project 
 * it will include port pin mapping definitions . 
 * General defines and macros .
 * Application specific constants and so on . */


/* Prevent Recursive Inclusion */
#ifndef PCONFIG_TOKEN_H
#define	PCONFIG_TOKEN_H 1UL



/**@brief XTAL FREQ DEFINITION FOR DELAY RELATED FUNCTIONS as Well as for Calculating Peripheral Clocks in some Init Functions */
#define _XTAL_FREQ 8000000UL 

//Include XC.h which will include the target register definition header files .
#include <xc.h>  
//Some Headers we might need 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// Drivers Section
#include "../Drivers/incl/pic_adc.h"
#include "../Drivers/incl/Seg_Dis.h"
#include "../Drivers/incl/pic_tim1.h"
#include "../Drivers/incl/pic_i2c.h"
#include "../Drivers/incl/eep.h"
/* GLOBAL INT */
/**@brief THIS MACRO ENABLES PERIPHERAL INTERRUPT BIT */
#define PI_EN() INTCON |= ( 1 << _INTCON_PEIE_POSITION )
/**@brief THIS MACRO ENABLES GLOBAL INTERRUPTS */
#define GI_EN() INTCON |= ( 1 << _INTCON_GIE_POSITION ) 
/**@brief THIS MACRO DISABLES GLOBAL INTERRUPTS */
#define GI_DIS() INTCON &= ~ ( 1 <<  _INTCON_GIE_POSITION )
/**@brief THIS MACRO CLEARS PERIPHERAL INTERRUPTS */
#define INT_CLEAR() PIR1 = 0 
/**@brief TURNS ON HEATER LED */
#define HEAT_LED_ON() HEAT_LED_PORT|= ( 1 << HEAT_LED_PIN )
/**@brief TURNS OFF HEATER LED */
#define HEAT_LED_OFF() HEAT_LED_PORT &= ~ ( 1 << HEAT_LED_PIN )
/**@brief CONFIGURES HEATER LED PIN */
#define HEAT_LED_SETUP() HEAT_LED_TRIS&= ~ ( 1 << HEAT_LED_PIN ); HEAT_LED_PORT&= ~ ( 1 << HEAT_LED_PIN )
/**@brief TURNS ON HEATER */
#define HEATER_ON()   HEATER_PORT |= ( 1 << HEATER_PIN )
/**@brief TURNS OFF HEATER */
#define HEATER_OFF()  HEATER_PORT &= ~( 1 << HEATER_PIN )
/**@brief TURNS ON COOLER */
#define COOLER_ON()     COOLER_PORT |= ( 1 << COOLER_PIN )
/**@brief TURNS OFF COOLER */
#define COOLER_OFF()    COOLER_PORT &= ~( 1 << COOLER_PIN )
/* Genios Board Defines */

/**@brief DIS4 , ENABLE PIN NUMBER FOR SEGMENT NUMBER 4 */
#define DIS4_PIN  5
/**@brief DIS4 , ENABLE PIN PORT FOR SEGMENT NUMBER 4 */
#define DIS4_PORT PORTA
/**@brief DIS4 , ENABLE PIN TRIS FOR SEGMENT NUMBER 4 */
#define DIS4_TRIS TRISA


/**@brief DIS4 , ENABLE PIN NUMBER FOR SEGMENT NUMBER 3 */
#define DIS3_PIN  4
/**@brief DIS4 , ENABLE PIN PORT FOR SEGMENT NUMBER 3 */
#define DIS3_PORT PORTA
/**@brief DIS4 , ENABLE PIN TRIS FOR SEGMENT NUMBER 3 */
#define DIS3_TRIS TRISA


/**@brief 7 SEGMENT DATA PORT */
#define SEG_PORT PORTD
/**@brief 7 SEGMENT DATA TRIS */
#define SEG_TRIS TRISD

/**@brief LED SEG-A PIN NUMBER */
#define SEGA_PIN 0
/**@brief LED SEG-B PIN NUMBER */
#define SEGB_PIN 1
/**@brief LED SEG-C PIN NUMBER */
#define SEGC_PIN 2
/**@brief LED SEG-D PIN NUMBER */
#define SEGD_PIN 3
/**@brief LED SEG-E PIN NUMBER */
#define SEGE_PIN 4
/**@brief LED SEG-F PIN NUMBER */
#define SEGF_PIN 5
/**@brief LED SEG-G PIN NUMBER */
#define SEGG_PIN 6
/**@brief LED SEG-P PIN NUMBER */
#define SEGP_PIN 7 

/**@brief TEMPERATURE SENSOR PORT */
#define TEMP_PORT PORTA
/**@brief TEMPERATURE SENSOR PIN NUMBER */
#define TEMP_PIN 2 
/**@brief TEMPERATURE SENSOR TRIS */
#define TEMP_TRIS TRISA

/**@brief INCREMENT BUTTON PORT */
#define INC_BUTTON_PORT PORTB
/**@brief INCREMENT BUTTON PIN NUMBER */
#define INC_BUTTON_PIN 4
/**@brief INCREMENT BUTTON TRIS */
#define INC_BUTTON_TRIS TRISB

/**@brief DECREMENT BUTTON PORT */
#define DEC_BUTTON_PORT PORTB
/**@brief DECREMENT BUTTON PIN NUMBER */
#define DEC_BUTTON_PIN 5
/**@brief DECREMENT BUTTON TRIS */
#define DEC_BUTTON_TRIS TRISB

/**@brief ON/OFF BUTTON PORT */
#define ONF_BUTTON_PORT PORTB
/**@brief ON/OFF BUTTON PIN NUMBER */
#define ONF_BUTTON_PIN 3
/**@brief ON/OFF BUTTON TRIS */
#define ONF_BUTTON_TRIS TRISB


/**@brief HEATER LED PORT */
#define HEAT_LED_PORT PORTB
/**@brief HEATER LED PIN NUMBER */
#define HEAT_LED_PIN 7 
/**@brief HEATER LED TRIS */
#define HEAT_LED_TRIS TRISB

/**@brief COOLER PORT */
#define COOLER_PORT PORTC
/**@brief COOLER TRIS */
#define COOLER_TRIS TRISC
/**@brief COOLER PIN NUMBER */
#define COOLER_PIN  2

/**@brief HEATER PORT */
#define HEATER_PORT PORTC
/**@brief HEATER TRIS */
#define HEATER_TRIS TRISC
/**@brief HEATER PIN NUMBER */
#define HEATER_PIN  5

// VALUES OF SOME STATES USED
#define ON_STATE  1
#define OFF_STATE 0 
#define NORMAL_MODE 1
#define TEMP_SETTING_MODE 2
//VALUES OF SOME TASKS
#define PWR_OFF 1
#define PWR_ON  2


/* Constants */
/**@brief POSTSCALER VALUE FOR THE WATCHDOG 2 */
#define WDT_POSTSCALER 0B100 
/**@brief TIMER2 COMPARE MATCH VALUE  */
#define TIMER2_COMPARE_VAL 0XFF 
/**@brief OUTSCALER FOR THE TIMER2 CLOCK SOURCE */
#define TIMER2_OUT_SCALER 0B0100
/**@brief IN SCALER FOR THE TIMER2 CLOCK SOURCE */
#define TIMER2_IN_SCALER 0B11 
/**@brief IN SCALER FOR THE TIMER1 CLOCK SOURCE */
#define TIMER1_IN_SCALER 0B00 
/**@brief TIMER1 SYNCH BIT FIELD */
#define TIMER1_SYNCH 1 
/**@brief TIMER1 SOURCE BIT FIELD */
#define TIMER1_SRC 0
/**@brief TIMER1 OSCEN BIT FIELD */
#define TIMER1_OSCEN 1 
/**@brief MAX ALLOWED TEMP */
#define MAX_TEMP 75
/**@brief MIN ALLOWED TEMP */
#define MIN_TEMP 35
/**@brief TEMPERATURE STEP PER ++ ,-- */
#define STEP_TEMP 5                        

/* CONFIGURATION BITS  , MODIFY PRAGMA , #define is placed there for doxygen */
/**@brief Oscillator Selection bits (HS oscillator) */
#define configFOSC
#pragma config FOSC = HS 
/**@brief Watchdog Timer Enable bit (WDT enabled) */
#define configWDTE
#pragma config WDTE = ON 
/**@brief Power-up Timer Enable bit (PWRT disabled) */
#define configPWRTE
#pragma config PWRTE = OFF 
/**@brief Brown-out Reset Enable bit (BOR enabled) */
#define configBOREN
#pragma config BOREN = ON 
/**@brief Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming) */
#define configLVP
#pragma config LVP = OFF 
/**@brief Data EEPROM Memory Code Protection bit (Data EEPROM code protection off) */
#define configCPD
#pragma config CPD = OFF 
/**@brief Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control) */
#define configWRT
#pragma config WRT = OFF 
/**@brief Flash Program Memory Code Protection bit (Code protection off) */
#define configCP
#pragma config CP = OFF 


/* END CONFIGURATION */

/**@brief IF DEFINED IT WILL ALLOW ASSERTION OF PARAMETERS PASSED TO INIT FUNCTIONS , INIT FUNCTION RETURN -1 ON FAIL
  * IF UNDEFINED NO ASSERTION IS TAKES PLACE AND INIT FUNCTIONS RETURN 0 */
#define DEBUG_MODE 1 

/**@brief DEVICE STATE ON/OFF*/
extern volatile uint8_t device_state ;  
/**@brief DESIRED TEMPERATURE THE USER SETS */
extern volatile uint8_t desired_temp ; 
/**@brief AVERAGE TEMPERATURE CALCULATED */
extern volatile uint16_t average_temp ; 
/**@brief HEATER STATE ON/OFF */
extern volatile uint8_t heater_state ; 
/**@brief COOLER STATE ON/OFF */
extern volatile uint8_t cooler_state ;  
/**@brief SEGMENT VALUE DISPALYED BY THE 7 SEGMENTS */
extern volatile uint8_t Seg_Val ;       
/**@brief DISPLAY STATE ON/OFF */
extern volatile uint8_t display_state  ;
/**@brief CURRENT TAKS POWER ON / POWER OFF */
extern volatile uint8_t Current_Task ;  
/**@brief DISPLAY MODE , TEMPERATURE SETTING MODE / NORMAL MODE */
extern volatile uint8_t display_mode  ; 

//if C++ is used , some functions that need C Linkage is defined here 
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif	/* PCONFIG_TOKEN_H */

