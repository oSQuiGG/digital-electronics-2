# Project 1

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

## Instructions

The goal of the project is cooperation in pairs, further study of the topic, design of own solutions, implementation, creation of project documentation and presentation of results. The division of roles and tasks within the team is up to their members.

* Students work on a project in the labs during the 10th and 11th weeks of the semester.

* Through the BUT e-learning, students submit a link to the GitHub repository, which contains the complete project in PlatfomIO and a descriptive README file. The submission deadline is the day before the next laboratory, i.e. in 2 weeks.

* The source code for the AVR must be written in C and/or Assembly and must be implementable on Arduino Uno board using toolchains from the semester, ie PlatformIO and not in the Arduino-style. No other development tools are allowed.

## Recommended GitHub repository structure

   ```c
   YOUR_PROJECT        // PlatfomIO project
   ├── include         // Included files
   ├── lib             // Libraries
   ├── src             // Source file(s)
   │   └── main.c
   ├── test            // No need this
   ├── platformio.ini  // Project Configuration File
   └── README.md       // Report of this project
   ```

## Recommended README.md file structure

### Team members

* Oscar Pérez Marín(responsible for xxx)
* Jesús Santos Gravalosa (responsible for xxx)

## Hardware description

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




### Schematic

Insert descriptive text and schematic(s) of your implementation.

## Software description

Put flowchats of your algorithm(s). Write descriptive text of your libraries and source files. Put direct links to these files in `src` or `lib` folders.

## Video

Insert a link to a short video with your practical implementation example (1-3 minutes, e.g. on YouTube).

## References

1. Write your text here.
2. ...
