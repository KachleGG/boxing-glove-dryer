# Boxing gloves dryer

## 
 - [Easy version](##Easy-version)
 - [Speed modulation version](##Speed-modulation-version)

## Documentation
For now it is just a 3D print that you will hook up to a 12V fan. The 3D model is now in version 2 and works just fine.

For 3D printing just look into the "STLs to print" folder and there you see folders titled as versions(V1, V2...), In each folder are STLs for printing and before them is a number of how many times you have to print the file out in this format:  **How many times**_boxing_glove_dryer_**Part number**.
The parts don't need to be printed in some chronological order it is purely for me so I don't get lost in the parts.

I'm using a 4-wire fan from an old computer but use any you want just change the 3D models or add an extension to this design to fit your fan.
For now I will be using only hot glue for interlocking parts because they can be separated pretty easily but still hold together and I don't want to start screwing things together because then it becomes too complicated.

There will be an easy one that will basically just blast the fan on full speed all the times it is pluged in to the socket(a module can be added for turning off) and than there will be one with a microcontroller and an encoder to change the speed of the fan.

If you're using an I2C LCD instead of an OLED, install:   **LiquidCrystal_I2C** library instead of Adafruit SSD1306.

## Easy version
### Things used
 - 12V fan
 - 12V power source
 - 3D printer
   - filament
 - Glue

### Assembly
Just print out the STLs, glue them together and glue the fan to the bottom of the 3D printed construction. Cut off any connector that remained on the power supply. Solder the positive and negative wires on the power supply to the positive and negative wires on the fan and ignore the other wires. Get some electrical tape and tape anything that might be dangerous. And you are done.

### Power consumption
 - I will be counting on the highest current that I can get from my power source(2A)
  - If your 12V fan pulls 2A we can calculate the formula like this:
      Power(W) = 12V * 2A = 24W

   - Energy consumption in 1 hour(approximate):
      Energy(kWh) = 24W * 1h / 1000 = **0.024kWh**

   - Energy consumption in 24 hours(approximate):
      Energy(kWh) = 24W * 24h / 1000 = **0.576kWh**

  - This is the energy consumption and you can calculate your cost per hour by multiplying your cost per kWh with the energy consumption:   **Cost per kWh** * 0.024 = **Cost per hour**


## Speed modulation version
### Things used
 - Arduino nano microcontroller
 - Rotary encoder with push button
 - 12V power source
 - 12V fan
 - 3D printer
   - filament
 - Glue
 - **Libraries**
    - Adafruit GFX Library
    - Adafruit SSD1306
    - Wire(Built-in)

### Assembly
Let's start with wiring everything:
#### Wiring

Rotary encoder wiring:
|Rotary Encoder Pin|	Arduino Pin   |
|------------------|----------------|
|CLK (A)           |	D2 (Interrupt)|
|DT (B)            |	D3            |
|SW (Button)       |	D4            |
|VCC               |	5V            |
|GND               |	GND           |

Fan wiring:
|Fan pin            |	Arduino Pin               |
|-------------------|---------------------------|
|Red (12V)          |	12V Power Supply          |
|Black (GND)        |	GND                       |
|Blue (PWM Control) |	D9 (PWM)                  |
|Yellow (Tachometer)|	Optional (RPM reading)    |

OLED display wiring:
|OLED Pin	| Arduino Nano  |
|VCC      |	5V            |
|GND      |	GND           |
|SCL      |	A5 (I2C Clock)|
|SDA      |	A4 (I2C Data) |

After everything is wired and printed you can glue the fan onto the 3D print And put the microcontroller, OLED display and encoder on the print.

Flash the code onto your microcontroller and you are done.

### Power consumption
|Component         |	Voltage (V)|	Current (A)|	Power (W)|
|------------------|-------------|-------------|-----------|
|Arduino Nano      |	5V         |	0.019 A    |	0.095 W  |
|OLED 0.96” Display|	5V         |	0.025 A    |	0.125 W  |
|Rotary Encoder    |	5V         |	0.005 A    |	0.025 W  |

**Fan consumes 24W with 12V and 2A**

 - Without fan power consumption:
      Power(W) = 0.095W + 0.125W + 0.025W = 0.245W
    
 - If we count the highest current scenario the consumption will look like this:
   - Energy consumption in 1 hour(approximate):
      Energy(kWh) = 24.25W * 1h / 1000 = **0.02425kWh**

   - Energy consumption in 24 hours(approximate):
      Energy(kWh) = 24.25W * 24h / 1000 = **0.582kWh**

  - This is the energy consumption and you can calculate your cost per hour by multiplying your cost per kWh with the energy consumption:   **Cost per kWh** * 0.02425 = **Cost per hour**



#### Disclaimer
The information provided herein is for educational and informational purposes only and should not be considered professional advice. By accessing this content, you acknowledge that you are solely responsible for your actions and decisions, including those related to assembling, modifying, or using any project, code, or components suggested herein.

We are not liable for any damages, injuries, or losses resulting from the use or misuse of this information, including but not limited to assembly processes, operational malfunctions, or unintended consequences. It is your responsibility to ensure compliance with all applicable local laws, regulations, and safety guidelines when undertaking any project. Proceed at your own risk.