


#include "../config/pconfig.h"


void system_startup ( void )
{   
    
    /* Setup Watch Dog timer at 500 ms Intervals , we need a Post Scaler of WDT_POSTCALER */
    //ASSIGN PRESCALER TO TIMER0
    OPTION_REG =  WDT_POSTSCALER ;
    // CLEAR PRESCALER
    TMR0 = 0 ;
    // SELECT WDT
    OPTION_REG = WDT_POSTSCALER | ( 1 << _OPTION_REG_PS_POSITION );
    //CLEAR WATCH DOG 
    CLRWDT();
    
    
    /* Peripheral Configuration Information */
     ADC_Config_S my_s = {
        
        .CH_sel = 2 , 
        .CKSEL_bf = ADC_CKSEL_FOSC_DIV32 ,
        .PCFG_bf  = ADC_PCFG_CR_50 ,
        .FMT_bf   = ADC_FMT_RADJ ,
        .INT_enable = 1 ,
        .convStart_Sel = 0 , 
    
    };
    
    I2C_Config_S my_i2c_s = {
      .I2C_Int_Enable = 0 , 
      .I2C_freq = 100000UL ,
      .I2C_mode = I2C_MODE_MASTER_HARDWARE_CONTROLLED ,
      .sla7_addr = 0 ,
      .sla10_addr = 0 ,
        
    };
    
    // Cooler and Heater Pins as OUTPUTS 
    PORTC &= ~ ( ( 1 << HEATER_PIN ) | (  1 << COOLER_PIN ) );
    TRISC &= ~ ( ( 1 << HEATER_PIN ) | (  1 << COOLER_PIN ) );
    
    // PORTB BUTTONS CONFIGURATION PINS 1,2,3
    ONF_BUTTON_TRIS |= ( 1 << ONF_BUTTON_PIN );
    INC_BUTTON_TRIS |= ( 1 << INC_BUTTON_PIN );
    DEC_BUTTON_TRIS |= ( 1 << DEC_BUTTON_PIN );
    // PORT A As Inputs 
    TRISA = 0XFF ;
    HEAT_LED_SETUP();
    //Initialize All Peripherals
    I2C_Init( &my_i2c_s );
    /* Fetch Desired Temp from EEPROM */
    //desired_temp = eepByteRead( 0x0000 );
    ADC_Init( &my_s );
    TIM1_Init();
    DisplayInit() ;
   // eepByteWrite( 1 , 0x0000 );
    //Enable Peripheral Interrupt 
    PI_EN();
    //Enable Global Interrupts 
    GI_EN();
    

}
    
    
    
    
void main(void) {
    
   
 system_startup();
 

 
    while ( 1 )
    {
       
       if ( Current_Task == PWR_ON )
        {   
           /* ENABLE ADC */
           ENABLE_ADC();
            /* ENABLE DISPLAY IN NORMAL MODE */
            display_state = ON_STATE ;
            device_state = ON_STATE ;
            display_mode = NORMAL_MODE ;
            ENABLE_SEG();
            /* READ LAST WRITTEN TEMP VALUE */
           uint8_t val = eepByteRead( 0X0000 );
           /* ASSERT THE VALUE IS IN RANGE */
           desired_temp = ( val >= 35 && val <= 75 ) ? ( val ) : ( 60 );
           Current_Task = 0 ;

            
        }
        else if ( Current_Task == PWR_OFF )
        {
            //Disable The Segment 
            display_state = OFF_STATE ; 
            DISABLE_SEG();
            /* DISABLE ADC */
            DISABLE_ADC();
            // CLEAR ALL PENDING INTERRUPTS
            INT_CLEAR();
            /* WRITE SAVED TEMPERATURE */
          eepByteWrite( desired_temp , 0x0000 );
           
            
            /* Turn off heater / or Cooler */
            if ( heater_state == ON_STATE )
            {
                HEATER_OFF();
                heater_state = OFF_STATE ;
            }
            if ( cooler_state == ON_STATE )
            {
                COOLER_OFF();
                cooler_state = OFF_STATE ;
            }
            
          HEAT_LED_OFF();
            device_state = OFF_STATE  ;
            Current_Task = 0 ;


            
            
        }
       CLRWDT();
    }
    return;
}
