#include <Arduino.h>
#include <Adafruit_Sensor.h>     // Required dependency
#include <Adafruit_BMP280.h>    // BMP280 library
#include <Wire.h>               //Required for I2C

#include <SD.h>                 //SD 


Adafruit_BMP280 bmp; // Create a BMP280 object
#define SD_CS 5    // Chip Select pin for SD card module **CHANGE IF NEEDED**
File myFile;


void setup()
{
    // CODE FOR BMP280
    Serial.begin(115200);          // initialize serial communication with baud rate of 9600
    while (!Serial) delay(100);  // wait for native usb
    Serial.println(F("BMP280 test"));

    // Initialize BMP280 using status variable
    unsigned status;
    status = bmp.begin(BMP280_ADDRESS);

    if (!status) {
        Serial.println(F("ERROR: Could not find a valid BMP280 sensor. Check wiring or try a different I2C address (0x76 or 0x77)."));
        while (1) delay(10); // Stop execution
    }

    Serial.println(F("BMP280 successfully initialized!"));


    // CODE FOR TESTING THE SD MODULE
    Serial.begin(115200);
    delay(1000); // small delay to make sure the Serial Monitor has time to connect
    Serial.println("Serial communication started");

    if (!SD.begin(SD_CS)) {
        Serial.println("SD Card initialization failed!");
        while (1);
    }
    Serial.println("SD Card initialized.");

    //Writing in text file on the SD card
    myFile = SD.open("/test.txt", FILE_WRITE);
    
    if(myFile) {
        myFile.println("testing 1, 2, 3.");
        myFile.close();
        Serial.println("Done writing.");
    }
    else {
        Serial.println("Error opening test.txt");
    }

    //Reading from text file from the SD card
    myFile = SD.open("/test.txt");
    if (myFile) {
        Serial.println("Reading from test.txt:");
        while (myFile.available()) {
        Serial.write(myFile.read());
        }
        myFile.close();
    } else {
        Serial.println("Error opening test.txt");
    }
}

void loop()
{
    // THIS IS CODE FOR BMP280
    // Read sensor data
    float temperature = bmp.readTemperature();     // °C
    float pressure = bmp.readPressure();           // Pascals
    float altitude = bmp.readAltitude(101325);     // Meters (standard sea level pressure)

    // Display readings
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.print(F(" °C | Pressure: "));
    Serial.print(pressure);
    Serial.print(F(" Pa | Altitude: "));
    Serial.print(altitude);
    Serial.println(F(" m"));

    delay(500); // Update every 0.5 seconds
}






// Website viewed: https://docs.sunfounder.com/projects/umsk/en/latest/02_arduino/uno_lesson20_bmp280.html
// Website viewedL https://docs.arduino.cc/learn/programming/sd-guide/