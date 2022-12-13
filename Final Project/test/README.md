# Project 1

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

## Instructions

The goal of the project is cooperation in pairs, further study of the topic, design of own solutions, implementation, creation of project documentation and presentation of results. The division of roles and tasks within the team is up to their members.

* Students work on a project in the labs during the 10th and 11th weeks of the semester.

* Through the BUT e-learning, students submit a link to the GitHub repository, which contains the complete project in PlatfomIO and a descriptive README file. The submission deadline is the day before the next laboratory, i.e. in 2 weeks.

* The source code for the AVR must be written in C and/or Assembly and must be implementable on Arduino Uno board using toolchains from the semester, ie PlatformIO and not in the Arduino-style. No other development tools are allowed.

### Team members

* Oscar Pérez Marín
* Jesús Santos Gravalosa 

## Project structure

Our project has this structure:


```c
├── include
│   └── timer.h
├── lib
│   └── lcd
│   │   ├── lcd.c
│   │   ├── lcd.h
│   │   └── lcd_definitions.h
│   └── gpio
|       ├── gpio.c
|       └── gpio.h
└── src
    └── main.c
```
   


## Hardware description

### Arduino Uno pinout 

![arduino pinout](https://user-images.githubusercontent.com/114435572/207163933-46f9533f-72f0-4ba1-b027-babfba33d15f.jpg)


### Analog joy-stick 

Analog module have five pins. Besides the power pins (5V and GND) the module offers two analog and one digital pins. Analog inputs are used to measure the joystick position and the digital input is used for the button.

![Joytick](https://user-images.githubusercontent.com/114435572/207159637-dbdfa58b-5910-48cb-b4ea-f2da0240703e.PNG)

Pins: GND, +5V, VRX, VRY and SW

Connections:

 - GND to GND 
 - +5V to +5V
 - VRX to analog pin PC1
 - VRY to analog pin PC2
 - SW to digital pin PD2

### Rotary enconder

A rotary encoder is an input device which looks like a potentiometer, but it outputs a series of pulses, which are different from others and unique. When rotary encoder knob is turned clockwise or anti clockwise, it rotates in small steps which produces analog or digital signals. 

![encoder](https://user-images.githubusercontent.com/114435572/207161461-bfb96832-c19b-467a-944c-2c1135a35f83.jpg)

Pins: GND, +5V, SW, DT and CLK

Connections:

  - GND to GND
  - +5V to +5V
  - SW to digital pin PB5
  - CLK (output A) to digital  pin PB2
  - DT (output B) to digital pin PB3

### Digilent PmodCLP LCD module

The Digilent Pmod CLP is a 16×2 character LCD module that uses a 8-bit parallel data interface to let system boards display up to 32 different characters out of over 200 possible options.
The PmodCLP communicates with the host board via the GPIO protocol. This particular module requires specific timings in order to program the KS0066 correctly, as per the KS0066 datasheet. These timings are described after the pinout description table shown below:

![PINOUT LCD](https://user-images.githubusercontent.com/114435572/207163454-a2eae84c-fa1d-4b18-bea2-987df31d4849.PNG)

![LCD](https://user-images.githubusercontent.com/114435572/207163576-3dc8e387-9b37-4277-9bac-b12a0e2dd0f5.PNG)

Connections: 
   
   - GND to GND 
   - +5V  to +5V
   - DB4: data bit 4 to digital pin PD4
   - DB5: data bit 5 to digital pin PD5
   - DB6: data bit 6 to digital pin PD6
   - DB7: data bit 7 to digital pin PD7
   - RS: Register Select (High for Data Transfer, Low for Instruction Transfer) to digital pin PB0
   - E: Read/Write Enable (High for Read, falling edge writes data) to digital pin PB1
   
   
### Schematic

This is the schematic with all the connections already mentioned: 

![Schematic](https://user-images.githubusercontent.com/114435572/207170820-0523690d-826e-464c-94c5-e5af7bd5696e.png)

## Software description

### Flowcharts

### Main flowchart

![b786f2bb-2bfc-4b94-9a25-5d5690e9048f](https://user-images.githubusercontent.com/114435572/207454055-9d200ccc-da73-4cdc-8056-e949e9bb1380.jpg)

### Timer flowchart

![timer2](https://user-images.githubusercontent.com/114435572/207454121-3e43990d-6de3-4c3d-a445-4475d79c8faf.png)

### ADC flowchart

![ADC](https://user-images.githubusercontent.com/114435572/207455737-c28290e5-fca4-4893-a81b-477b8767e92f.png)



### Libraries

We used two additional libraries, LCD library and GPIO library.

### GPIO library

At the most basic level, GPIO refers to a set of pins on your computer’s mainboard or add-on card. These pins can send or receive electrical signals, but they aren’t designed for any specific purpose. This is why they’re called “general-purpose” IO.

Useful functions of this library: 

| **Return** | **Function name** | **Function parameters** | **Description** |
   | :-: | :-- | :-- | :-- |
   | `void` | `GPIO_mode_output` | `volatile uint8_t *reg, uint8_t pin` | Configure one output pin |
   | `void` | `GPIO_mode_input_pullup` | `volatile uint8_t *reg, uint8_t pin` | Configure one input pin and enable pull-up resistor |
   | `void` | `GPIO_write_low` | `volatile uint8_t *reg, uint8_t pin` | Write one pin to low value |
   | `void` | `GPIO_write_high` | `volatile uint8_t *reg, uint8_t pin` | Write one pin to high value |
   | `uint8_t` | `GPIO_read` | `volatile uint8_t *reg, uint8_t pin` | Read a value from input pin |
   
   
gpio.c: https://github.com/oSQuiGG/digital-electronics-2/blob/278a2b2c9639c20bf2e7b7b125e14eb4b0869440/Final%20Project/lib/gpio/gpio.c

gpio.h: https://github.com/oSQuiGG/digital-electronics-2/blob/278a2b2c9639c20bf2e7b7b125e14eb4b0869440/Final%20Project/lib/gpio/gpio.h


### LCD library

This library allows an Arduino board to control LiquidCrystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs. 

Useful functions of this library:

- void 	lcd_init (uint8_t dispAttr)
 	Initialize display and select type of cursor.
 
- void 	lcd_clrscr (void)
 	Clear display and set cursor to home position.
 
- void 	lcd_home (void)
 	Set cursor to home position.
 
- void 	lcd_gotoxy (uint8_t x, uint8_t y)
 	Set cursor to specified position.
 
- void 	lcd_putc (char c)
 	Display character at current cursor position.
 
- void 	lcd_puts (const char *s)
 	Display string without auto linefeed.
 
- void 	lcd_puts_p (const char *progmem_s)
 	Display string from program memory without auto linefeed.
 
- void 	lcd_command (uint8_t cmd)
 	Send LCD controller instruction command.
 
- void 	lcd_data (uint8_t data)
 	Send data byte to LCD controller.
 

lcd.c: https://github.com/oSQuiGG/digital-electronics-2/blob/278a2b2c9639c20bf2e7b7b125e14eb4b0869440/Final%20Project/lib/lcd/lcd.c

lcd.h: https://github.com/oSQuiGG/digital-electronics-2/blob/278a2b2c9639c20bf2e7b7b125e14eb4b0869440/Final%20Project/lib/lcd/lcd.h

lcd_definitions.h: https://github.com/oSQuiGG/digital-electronics-2/blob/278a2b2c9639c20bf2e7b7b125e14eb4b0869440/Final%20Project/lib/lcd/lcd_definitions.h

### Source files

main.c: https://github.com/oSQuiGG/digital-electronics-2/blob/1e44f9dc320f6a2bab06ce2787f75f7d7fd2990b/Final%20Project/src/main.c






## Video



https://user-images.githubusercontent.com/114435572/207458691-8705e085-831c-49f3-a408-f8202a08578c.mp4

https://www.youtube.com/shorts/UVWIxD-Jdzc



## References

Rotary encoder in Arduino: https://electropeak.com/learn/rotary-encoder-how-it-works-how-to-use-with-arduino/

Analog Joy-stick in Arduino: https://arduinogetstarted.com/tutorials/arduino-joystick

Digilent PmodCLP LCD module: https://digilent.com/reference/_media/pmod:pmod:pmodclp_rm.pdf

