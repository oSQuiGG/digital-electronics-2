
/* INCLUDES ...............................................
*/
#include <lcd.h>            // Peter Fleury's LCD library
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions



/*Leds definitions*/
#define LED1 PC0


/*Rotary encoder definitions*/
#define outputA PB2        //Arduino pinout for CLK 
#define outputB PB3         //Arduino pinout for DT
#define outputSwitchEnc PB5 //Arduino pinout for encoder button


/*Analog Joystick definitions*/
#define outputSwitchJoy PD2  //arduino pin for the joystick button
#define outputAxisX PC1      //arduino pin for X axis joystick
#define outputAxisY PC2      //arduino pin for Y axis joystick


/*Variables (rotary encoder) definitions*/
uint8_t EncSwitch = 0; //Initial value if encoder button is not pushed  
uint8_t counter = 0; //Initial value of counter
uint8_t aState;
uint8_t aLastState;

uint16_t value = 0;





/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 **********************************************************************/


int main(void)
{
    // Initialize display
    lcd_init(LCD_DISP_ON);

    //Set the LED1 as output
    GPIO_mode_output(&DDRC, LED1);
    
    
    //Set the three pins of the rotary encoder as inputs
    GPIO_mode_input_pullup(&DDRB, outputA);
    GPIO_mode_input_pullup(&DDRB, outputB);
    GPIO_mode_input_pullup(&DDRB, outputSwitchEnc);


    


   
    
   
    
    
    


    aLastState =  GPIO_read(&PINB, outputA); //read value of output A and save it in variable aLastState

    char string[6]; // String for converted numbers by itoa()
                
    
    while(1)
    {
         EncSwitch = GPIO_read(&PINB, outputSwitchEnc);
    
    
    if(EncSwitch == 0 )
    {
        GPIO_write_low(&PORTC, LED1);  //Turn OFF the LED if EncSwitch is pressed
        
        lcd_gotoxy(0,0);  
        lcd_puts("LED OFF");     //Write in LCD when 
    }
   
    else if (EncSwitch == 1 )
    {
        GPIO_write_high(&PORTC, LED1);  //Turn ON the LED if EncSwitch is pressed
        
        lcd_gotoxy(0,0);
        lcd_puts("LED  ON");
    }
        aState = GPIO_read(&PINB, outputA); //read value of output A and save it in variable aState
        
        
        if (aState != aLastState){  //When a pulse is generated, this condition is true
            
            if(GPIO_read(&PINB, outputB) != aState) {  //condition to know the rotation of the encoder
                
                counter++;
                

            }

            else {
                
                counter--;
                
            }
            
            
                lcd_gotoxy(9,0);
                lcd_puts("Pos: ");

                itoa(counter, string, 10),
                lcd_gotoxy(13,0);
                lcd_puts("      ");
                lcd_gotoxy(13,0);
                lcd_puts(string);
            
        
        }
      
        
        aLastState = aState;
    
    }


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
    TIM1_overflow_16ms();
    TIM1_overflow_interrupt_enable();

    
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

    // make conversion every 100ms
    
    static uint8_t no_of_overflows = 0;
    
    no_of_overflows++;
        if (no_of_overflows >= 6){ // Do this every 6 x 16 ms = 100 ms
            if(value==0){
                ADMUX = ADMUX & ~ ( 1<<MUX0); //set first channel
                value++; //increase value to switch conversion channel
            }
            else{
                ADMUX = ADMUX | ( 1<<MUX0); //set second conversion channel
                value--; //decrease value to switch conversion channel

}
            no_of_overflows = 0;
            ADCSRA = ADCSRA | (1<<ADSC); // Start ADC conversion
        }
}

ISR(ADC_vect)
{
    uint16_t value=0; //value to switch ADC channel
    uint16_t Xposition;
    uint16_t Yposition;
    
    
    char stringX[4];             // String for converted numbers by itoa()
    char stringY[4];             // String for converted numbers by itoa()
    
    uint8_t tenthsX = 0;
    uint8_t tenthsY = 0;
    uint8_t secsX = 0;  // seconds AxisX
    uint8_t secsY = 0;  // seconds AxisY
    static uint8_t no_of_overflows = 0;
    
    

    


   
    
    
    no_of_overflows++;
    if(value == 0)
    { 
      Xposition = ADC;
    
    if(Xposition > 0)
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
         
                
        
            }
            // Display seconds
                itoa(secsX, stringX, 10);  // Convert decimal value to string
                lcd_gotoxy(9, 1);
                lcd_puts(stringX);
      
        }
    
    }
    }
    else
    {
    Yposition = ADC;
    if (Yposition > 0)
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
         
                
        
            }
            // Display seconds
                itoa(secsX, stringY, 10);  // Convert decimal value to string
                lcd_gotoxy(9, 1);
                lcd_puts(stringX);
            
      
        }
  
    }
    }

     /* else(xPosition > 200 && Yposition > 200)
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
    */
    

}





