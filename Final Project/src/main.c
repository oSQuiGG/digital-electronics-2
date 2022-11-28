
/* INCLUDES ...............................................
*/
#include <lcd.h>            // Peter Fleury's LCD library
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
#include <uart.h>


/*Leds definitions*/
#define LED1 PB3


/*Rotary encoder definitions*/
#define outputA PB0         //Arduino pinout for CLK 
#define outputB PB1         //Arduino pinout for DT
#define outputSwitchEnc PB2 //Arduino pinout for encoder button


/*Analog Joystick definitions*/
#define outputSwitchJoy PC0  //arduino pin for the joystick button
#define outputAxisX PC1      //arduino pin for X axis joystick
#define outputAxisY PD2      //arduino pin for Y axis joystick


/*Variables (rotary encoder) definitions*/
static uint8_t EncSwitch = 0; //Initial value if encoder button is not pushed  
static uint8_t counter = 0; //Initial value of counter
static uint8_t aState;
static uint8_t aLastState;


/*Variables (analog joystick) definitions*/
static uint8_t xPosition = 0;
static uint8_t yPosition = 0;
static uint8_t JoySwitch = 0;



/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 **********************************************************************/


int main(void)
{
    // Initialize display
    lcd_init(LCD_DISP_ON);

    //Set the LED1 as output
    GPIO_mode_output(&DDRB, LED1);
    
    
    //Set the three pins of the rotary encoder as inputs
    GPIO_mode_input_pullup(&DDRD, outputA);
    GPIO_mode_input_pullup(&DDRD, outputB);
    GPIO_mode_input_pullup(&DDRD, outputSwitchEnc);


    //set the three pins of the analog joystick as inputs
    GPIO_mode_input_pullup(&DDRB, xPosition);
    GPIO_mode_input_pullup(&DDRB, yPosition);
    GPIO_mode_input_pullup(&DDRB, JoySwitch);



    
    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    
    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 16 ms and enable overflow interrupt
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();

    
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}


ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);

    EncSwitch = GPIO_read(&PIND, outputSwitchEnc);
    
    if (EncSwitch == 0 )
    {
        GPIO_write_low(&PORTB, LED1);  //Turn OFF the LED if EncSwitch is pressed
        
        lcd_gotoxy(0,1);  
        lcd_puts("LED OFF");     //Write in LCD when 
    }
   
    else if (EncSwitch == 1 )
    {
        GPIO_write_high(&PORTB, LED1);  //Turn ON the LED if EncSwitch is pressed
        
        lcd_gotoxy(0,1);
        lcd_puts("LED ON");
    }


    aLastState =  GPIO_read(&PIND, outputA); //read value of output A and save it in variable aLastState

    char string[6]; // String for converted numbers by itoa()
    
    lcd_gotoxy(0,0);
    lcd_puts("Position: ");

    while(1)
    {
        aState = GPIO_read(&PIND, outputA); //read value of output A and save it in variable aState
        
        if (aState != aLastState){  //When a pulse is generated, this condition is true
            
            if(GPIO_read(&PIND, outputB) != aState) {  //condition to know the rotation of the encoder
                
                counter++;
            }

            else {
                
                counter--;
            }

            itoa(counter, string, 10),
            lcd_gotoxy(8,0);
            lcd_puts("       ");

            lcd_gotoxy(8,0);
            lcd_puts(string);
        
        }
        
        aLastState = aState;
    
    }

}


ISR(ADC_vect)
{
    static uint8_t no_of_overflows = 0;
    static uint8_t tenthsX = 0;  // Tenths of a second for AxisX
    static uint8_t tenthsY = 0;  // Tenths of a second for AxisY

    
    char stringX[2];             // String for converted numbers by itoa()
    char stringY[2];             // String for converted numbers by itoa()
    
    
    static uint8_t secsX = 0;  // seconds AxisX
    static uint8_t secsY = 0;  // seconds AxisY

    
    xPosition = GPIO_read(&DDRB, outputAxisX);
    yPosition = GPIO_read(&DDRB, outputAxisY);
    JoySwitch = GPIO_read(&DDRB, outputSwitchJoy);


    


    // Select input channel ADC0 (voltage divider pin)
    /*
    ADMUX = ADMUX & ~( 1<<MUX3 | 1<<MUX2 | 1<<MUX0 | 1<<MUX1);
    ADCSRA |= (1<<ADSC);
    valueX = ADC;
    */
    
    no_of_overflows++;
    
    if(xPosition > 200)
    {
        
        if (no_of_overflows >=6)
        {
            // Do this every 6 x 16 ms = 100 ms
            no_of_overflows = 0;

            // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
            tenthsX++;
        
            if (tenthsX > 9)
            {
                tenthsX = 0;
                secsX++;
         
                // Display seconds
                itoa(secsX, stringX, 10);  // Convert decimal value to string
                lcd_gotoxy(9, 1);
                lcd_puts(stringX);
        
            }
      
        }
    
    }

    else if (yPosition > 200)
    {
    
        if (no_of_overflows >=6)
        {
            // Do this every 6 x 16 ms = 100 ms
            no_of_overflows = 0;

            // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
            tenthsY++;
        
            if (tenthsY > 9)
            {
                tenthsY = 0;
                secsY++;
         
                // Display seconds
                itoa(secsY, stringY, 10);  // Convert decimal value to string
                lcd_gotoxy(11, 1);
                lcd_puts(stringY);
        
            }
      
        }
  
    }

    else if(xPosition > 200 && yPosition > 200)
    {
        if (no_of_overflows >=6)
        {
            // Do this every 6 x 16 ms = 100 ms
            no_of_overflows = 0;

            // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
            tenthsY++;
            tenthsX++;
            
            if (tenthsY > 9)
            {
                tenthsY = 0;
                secsY++;
         
                // Display seconds
                itoa(secsY, stringY, 10);  // Convert decimal value to string
                lcd_gotoxy(11, 1);
                lcd_puts(stringY);
        
            }

            if (tenthsX > 9)
            {
                tenthsX = 0;
                secsX++;
         
                // Display seconds
                itoa(secsX, stringX, 10);  // Convert decimal value to string
                lcd_gotoxy(9, 1);
                lcd_puts(stringX);
        
            }
      
        }



    }
    

}













    










