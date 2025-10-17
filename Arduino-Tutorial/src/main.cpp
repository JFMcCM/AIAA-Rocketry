#include <Arduino.h>
#include <Adafruit_BMP280.h>  // Include the BMP280 library

/*
Runs once when the Arduino starts.
Used to initialize settings, pin modes, and librareies
*/
void setup()  // Prepares the system
{
  Serial.begin(9600);
}

/*
Runs repeatedly after setup().
Contains the main code that executes constinuously.
*/
void loop() // Handles ongoing tasks and logic
{
  Serial.println("Hello World!");
  delay(1000);
}

/* BMP 280 Library
Key Functions:
bmp.readTemperature() - Returns the temperature in degrees Celsius as a float.
bmp.readPressure() - Returns the pressure in Pascals as a float.
bmp.readAltitude(seaLevelPressure) - Returns the altitude in meters as a float.
*/

/* Coding SD card Module
- Library built into Arduino IDE
- Examples in Arduino IDE
Key Functions:
SD.begin(chipSelect) - Initializes the SD card and sets the chip select pin.
SD.open(filename, mode) - Opens a file on the SD card with the specified mode (READ, WRITE, etc.).
file.write() - Writes data to the file.
file.read() - Reads data from the file.
*/

// End of tutorial

// test