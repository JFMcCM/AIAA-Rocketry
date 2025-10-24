#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SD.h>

Adafruit_BMP280 bmp;    // I2C
#define SD_CS 5         // SD card CS (common on ESP32 dev boards)
File myFile;

void setup() {
  Serial.begin(115200);
  // while(!Serial) delay(50); // optional on ESP32, can remove

  Serial.println("BMP280 test");

  // I2C on ESP32 defaults are 21 (SDA) and 22 (SCL), make explicit:
  Wire.begin(21, 22);
  delay(50); // give sensor time after power-up

  // Try both common addresses
  if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
    Serial.println("Could not find BMP280 (I2C). Check wiring/address.");
    Serial.printf("sensorID: 0x%02X\n", bmp.sensorID());
    while (1) delay(10);
  }
  else{
    Serial.println("BMP280 OK.");
  }
  if (bmp.begin(0x76) || bmp.begin(0x77))
  {
    Serial.println("Found BMP280.");
  }
  Serial.println("Done");

  // SD card test (SPI)
  if (!SD.begin(SD_CS)) {
    Serial.println("SD init failed! (check wiring/CS/power)");
    while (1) delay(10);
  }
  Serial.println("SD OK.");

  myFile = SD.open("/test.txt", FILE_WRITE);
  if (myFile) { myFile.println("testing 1, 2, 3."); myFile.close(); Serial.println("Wrote file."); }
  else Serial.println("Error opening test.txt");

  myFile = SD.open("/test.txt");
  if (myFile) { Serial.println("Reading test.txt:"); while (myFile.available()) Serial.write(myFile.read()); myFile.close(); }
  else Serial.println("Error opening test.txt");
}

void loop() {
  Serial.print("T: "); Serial.print(bmp.readTemperature());
  Serial.print(" C | P: "); Serial.print(bmp.readPressure());
  Serial.print(" Pa | Alt: "); Serial.print(bmp.readAltitude(101325));
  Serial.println(" m");
  delay(500);
}