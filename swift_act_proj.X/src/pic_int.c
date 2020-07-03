
/* This File Contains The Interrupt Function for the project */

/* Author : Mohamed Yousry Mohamed Rashad 
 * Date : 6/29/2020
 */

/* Include main application Header */
#include "../config/pconfig.h"



volatile uint8_t device_state = OFF_STATE ;
volatile uint8_t desired_temp = 60 ;
volatile uint16_t average_temp = MIN_TEMP ;
volatile uint8_t heater_state = OFF_STATE ;
volatile uint8_t cooler_state = OFF_STATE ;
volatile uint8_t Seg_Val = 0X60 ; 
volatile uint8_t display_state = OFF_STATE ;
volatile uint8_t display_mode = NORMAL_MODE ;
volatile uint8_t Current_Task = 0 ;



void WriteSegVal ( uint8_t newval )
{
    
    Seg_Val = (newval%10)|((newval/10) << 4 ) ; 
    
}



inline void TIMER2_IRQ_Handler( void )
{
    
    
    const uint8_t decode[10] = { 0B00111111 , 0B00000110 , 0B01011011  , 0B01001111 ,
                                 0B01100110 , 0B01101101 , 0B01111101  , 0B00000111 ,
                                 0B01111111 , 0B01101111 };
    
    static uint8_t digit = 0 ;

    
    if ( display_state == ON_STATE  && device_state == ON_STATE ){
    if ( !digit ){
    /* Select FIRST DIGIT ON DS4 */
    SELECT_FIRST_DIGIT();
    
    /* Write Val */
    
    WRITE_DIGIT( decode[Seg_Val&0X0F]);
    digit = 1 ;
    }
    else{
    
    /* Select Seoond Digit */
    SELECT_SECOND_DIGIT();
    
    /* Write Second Digit */
    WRITE_DIGIT( decode[Seg_Val>>4]);
    digit = 0 ; 

    }
    
    }
    else{
        
        SELECT_OFF();
    }


}




inline void TIMER1_IRQ_Handler( void )
{
    
    static uint8_t tim1_ovf_count = 0 ; 
    static uint8_t temp_reading_count = 0 ;
    static uint8_t last_clicked_button = 0 ;
    static uint8_t sig_blink_count = 0 ;
    static uint8_t sig_blink_toggle = 0 ;
    static uint8_t temp_enter_counter = 0 ;
    static uint8_t tst ;

    
    
    
    if ( !(ONF_BUTTON_PORT & ( 1 << last_clicked_button )) && last_clicked_button != 0  )
    {
        //Button is still held down or bouncing 
        //in any case we skip button polling for this cycle 
        // we continue polling when the button is unpressed or debouncing is gone
        // which should settle in 2 cycles max
    
    }
    else{
     //No Press , free to check    
     last_clicked_button = 0 ;
    /* Handle Button Press if any */
    if ( !(ONF_BUTTON_PORT & ( 1 << ONF_BUTTON_PIN )) )
    {
        if ( device_state == OFF_STATE )
        {
            Current_Task = PWR_ON ;
    

        }
        else{
            
            Current_Task = PWR_OFF ; 

        }           
        
        last_clicked_button = ONF_BUTTON_PIN ; 
        
    }
    else if ( !(INC_BUTTON_PORT & ( 1 << INC_BUTTON_PIN ) ) )
    {
        if (  device_state == ON_STATE )
        {
             if ( display_mode == NORMAL_MODE  )
            {
                display_mode = TEMP_SETTING_MODE;temp_enter_counter = 0 ;
                tst = desired_temp; 
            }
            else if ( display_mode == TEMP_SETTING_MODE && !(desired_temp + STEP_TEMP > MAX_TEMP ) )
            {
                tst += 5 ;
                temp_enter_counter = 0 ;
            }
         
        }
        
        last_clicked_button = INC_BUTTON_PIN; 
            
    
    }
    else if ( !(DEC_BUTTON_PORT & ( 1 << DEC_BUTTON_PIN ) ) )
    {
        
        if (   device_state == ON_STATE )
        {
            if ( display_mode == NORMAL_MODE  )
            {
                display_mode = TEMP_SETTING_MODE;temp_enter_counter = 0 ;
                tst = desired_temp ; 
                
            }
            else if ( display_mode == TEMP_SETTING_MODE && !(desired_temp - STEP_TEMP < MIN_TEMP ) )
            {
                tst -= 5 ;
                temp_enter_counter = 0 ;
            }
        }
        last_clicked_button = DEC_BUTTON_PIN;
        
        
    }
    }
    
       if ( ((++temp_enter_counter) >= 250 ) && display_mode == TEMP_SETTING_MODE )
    {
        display_mode = NORMAL_MODE ; 
        Current_Task = WRITE_EEP ; 
        desired_temp = tst ;
        if ( device_state == ON_STATE )
        {
            display_state = ON_STATE ; 
        }
        temp_enter_counter = 0 ; 
    }
    
    
    if ( device_state == ON_STATE && display_state == ON_STATE ) {
        if ( display_mode == NORMAL_MODE )
        {
            WriteSegVal( average_temp );
        }
        else if ( display_mode == TEMP_SETTING_MODE ){
         WriteSegVal( tst );   
        }
    }
    

    
    
    if ( (++sig_blink_count) >= 30  && display_mode == TEMP_SETTING_MODE )
    {
        if ( sig_blink_toggle == 0 )
        {
            display_state = OFF_STATE ; 
            sig_blink_toggle = 1 ;
        }
        else{
            display_state = ON_STATE ;
            sig_blink_toggle = 0 ; 
        }
        sig_blink_count = 0 ;
        
    
    }
    
   
   
    if ( ++tim1_ovf_count == 3 )
    {
        // Start Conversion 
        ADC_StartConv_NB();
        tim1_ovf_count = 0 ;
          
    }
    /* Check Temperature */
    
    
}


inline void ADC_IRQ_Handler ( void )
{
    static uint16_t temp_rsum = 0 ;
    static uint8_t temp_count = 0 ;
    static uint8_t heat_led_count = 0 ; 
    static uint8_t heat_led_toggle = 0 ; 
    
    temp_rsum += (( ((uint16_t)ADRESL) | ( ((uint16_t)ADRESH) << 8 ) )/2) ;
    temp_count++ ;
    
    if ( temp_count == 10 )
    {
        average_temp = temp_rsum / 10 ; 
        temp_count = 0 ; 
        temp_rsum = 0 ;
        
    }
    
    if ( device_state == ON_STATE ){
    if ( desired_temp > average_temp && (  desired_temp - average_temp  ) > 5 && heater_state == OFF_STATE && cooler_state == OFF_STATE ){
                // turn on Heater 
            HEATER_ON();heater_state = ON_STATE;heat_led_count= 0 ; 
            
        }
    else if ( desired_temp < average_temp && ( average_temp - desired_temp ) > 5 && cooler_state == OFF_STATE && heater_state == OFF_STATE )
        {
            //turn on cooler 
            COOLER_ON();cooler_state = ON_STATE;
        }
    else if ( average_temp > desired_temp && ( average_temp - desired_temp ) > 1 && heater_state == ON_STATE  )
    {
        HEATER_OFF();heater_state = OFF_STATE;
    }
    else if ( average_temp < desired_temp && ( desired_temp - average_temp) > 1 && cooler_state == ON_STATE) 
    {
       COOLER_OFF();cooler_state = OFF_STATE;
        
    }
    
    if ( heater_state == ON_STATE   )
    {
        if ( (++heat_led_count) >= 10 )
        {
            if ( !heat_led_toggle )
            {
                HEAT_LED_ON();
                heat_led_toggle =1 ; 
            }
            else{
                HEAT_LED_OFF();
                heat_led_toggle = 0 ; 
            }
            heat_led_count = 0 ;
            
        }
                
        
    }
    else if ( cooler_state == ON_STATE )
    {
     HEAT_LED_ON();   
        
    }
    else{
        HEAT_LED_OFF();
    }

    
    }
    
    
}

void __interrupt() ISR( void )
{
   
    /* Set First Priority to Refresh */
    
    if ( PIR1 & ( 1 << _PIR1_TMR2IF_POSITION ) )
    {   

        /* Timer 2 Routine */
        TIMER2_IRQ_Handler();
        /* Clear FLAG */
        PIR1&= ~ ( 1 << _PIR1_TMR2IF_POSITION );
        
    }
    else if ( PIR1 & ( 1 << _PIR1_TMR1IF_POSITION  ) )
    {   
        /* Clear FLAG */
        PIR1&= ~( 1 << _PIR1_TMR1IF_POSITION );
        TIMER1_IRQ_Handler();
        
    }
    else if ( PIR1 & ( 1 << _PIR1_ADIF_POSITION ))
    {
        /* Clear FLAG */
        PIR1&= ~( 1 << _PIR1_ADIF_POSITION );
        ADC_IRQ_Handler();
    }
    
   
    
    
    
    
    
    
    
}