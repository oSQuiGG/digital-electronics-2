# Lab 5: Oscar Pérez Marin

### Analog-to-Digital Conversion

1. Complete table with voltage divider, calculated, and measured ADC values for all five push buttons.

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** | **ADC value (measured, hex)** |
   | :-: | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0   | 0 | 0 |
   | Up     | 0.495&nbsp;V | 101 | 100 | 63 |
   | Down   | 1.203&nbsp;V | 246 | 257 | 101 |
   | Left   | 1.96&nbsp;V | 401 | 410 | 19a |
   | Select | 3.18&nbsp;V | 650 | 640 | 280 |
   | none   | 5&nbsp;V | 1023 | 1023 | 3FF |

### Temperature meter

Consider an application for temperature measurement. Use analog temperature sensor [TC1046](http://ww1.microchip.com/downloads/en/DeviceDoc/21496C.pdf), LCD, and a LED. Every 30 seconds, the temperature is measured and the value is displayed on LCD screen. When the temperature is too high, the LED will turn on.

2. Draw a schematic of temperature meter. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![ESQUEMA](https://user-images.githubusercontent.com/114435572/199100614-d2b8000e-2083-4457-be2a-c4f0343a0ba4.png)



3. Draw two flowcharts for `main` function and `TIMER1_OVF_vect` interrupt service routine which overflows every 1&nbsp;sec. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![133ff72d-43f1-482e-a1bf-df08f37ad7bf](https://user-images.githubusercontent.com/114435572/199100474-427dbc70-4a05-4e04-a2d2-2398439a076b.jpg)
