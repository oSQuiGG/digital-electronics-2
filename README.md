# digital-electronics-2
## Laboratory exercise
### Arduino

**This is a bold text**

*This text is italicized*



![alt text](https://myoctocat.com/assets/images/base-octocat.svg)

# Lab 1: Oscar Pérez Marin

### Morse code


1. Listing of C code which repeats one "dot" and one "comma" (BTW, in Morse code it is letter `A`) on a LED. Always use syntax highlighting, meaningful comments, and follow C guidelines:

```c

#define LED_GREEN PB5 
#define PB5 13  



#define MILI_DELAY 300 // duration between dot and comma
#define SHORT_DELAY 300 //duration of dot in milliseconds
#define LONG_DELAY  900 // duration of commma in milliseconds
int main(void)
{
    uint8_t led_value = LOW;  // Local variable to keep LED status
    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
        // Generate a lettre `A` Morse code
         

          // Turn ON/OFF on-board LED
          digitalWrite(LED_GREEN, led_value);

          led_value = HIGH;

          // Pause the time of the dot
        _delay_ms(SHORT_DELAY);

         led_value = LOW;

         // Pause between dot an comma
        _delay_ms(MILI_DELAY);

        led_value = HIGH;

        // Pause between dot an comma
        _delay_ms(LONG_DELAY);
        
        }

    // Will never reach this
    return 0;
}
```


2. Scheme of Morse code application, i.e. connection of AVR device, LED, resistor, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![your figure]()




