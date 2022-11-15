# Lab 7: Oscar Perez Marin

### Arduino Uno pinout

1. In the picture of the Arduino Uno board, mark the pins that can be used for the following functions/operations:
   * PWM generators from Timer0, Timer1, Timer2
   * analog channels for ADC
   * UART pins
   * I2C pins
   * SPI pins
   * external interrupt pins INT0, INT1

   ![arduino](https://user-images.githubusercontent.com/114435572/201790346-8426a6ca-44fb-4fcf-8c3d-b3225345512c.jpg)


### I2C communication

2. Draw a timing diagram of I2C signals when calling function `rtc_read_years()`. Let this function reads one byte-value from RTC DS3231 address `06h` (see RTC datasheet) in the range `00` to `99`. Specify when the SDA line is controlled by the Master device and when by the Slave device. Draw the whole request/receive process, from Start to Stop condition. The image can be drawn on a computer (by [WaveDrom](https://wavedrom.com/) for example) or by hand. Name all parts of timing diagram.

   
![fa4e6466-5339-4fe9-8119-d2e52cac94f9](https://user-images.githubusercontent.com/114435572/201795967-1b6ef84c-c10a-4a5e-8075-591e9c8c283d.jpg)

### Meteo station

Consider an application for temperature and humidity measurements. Use sensor DHT12, real time clock DS3231, LCD, and one LED. Every minute, the temperature, humidity, and time is requested from Slave devices and values are displayed on LCD screen. When the temperature is above the threshold, turn on the LED.

3. Draw a flowchart of `TIMER1_OVF_vect` (which overflows every 1&nbsp;sec) for such Meteo station. The image can be drawn on a computer or by hand. Use clear description of individual algorithm steps.

   ![8f514dd5-bc37-49e2-9a5e-76f28b4cdc11](https://user-images.githubusercontent.com/114435572/201792784-ab2454cc-e051-43a3-84b1-f7e9291e294d.jpg)

