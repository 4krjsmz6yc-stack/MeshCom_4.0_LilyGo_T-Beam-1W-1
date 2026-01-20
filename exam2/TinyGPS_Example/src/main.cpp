/*
  This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
  Base on TinyGPSPlus //https://github.com/mikalhart/TinyGPSPlus
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <esp_mac.h>
#include "soc/rtc.h"

#if defined(ARDUINO_ARCH_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5,0,0)
#include "hal/gpio_hal.h"
#endif
#include "driver/gpio.h"
#endif //ARDUINO_ARCH_ESP32

#include <TinyGPS++.h>

#include "configuration.h"

TinyGPSPlus gps;
#define SerialGPS Serial1

//=======================================================================================
void displayInfo()
{
    Serial.print(F("Location: "));
    if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
    } else {
        Serial.print(F("INVALID"));
    }

    Serial.print(F("  Date/Time: "));
    if (gps.date.isValid()) {
        Serial.print(gps.date.month());
        Serial.print(F("/"));
        Serial.print(gps.date.day());
        Serial.print(F("/"));
        Serial.print(gps.date.year());
    } else {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" "));
    if (gps.time.isValid()) {
        if (gps.time.hour() < 10) Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        if (gps.time.second() < 10) Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(F("."));
        if (gps.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(gps.time.centisecond());
    } else {
        Serial.print(F("INVALID"));
    }

    Serial.println();
}


//=======================================================================================
void setup()
{
    //setupBoards();
    Serial.begin(115200);
    while (!Serial);
    for (int i=0;i<10;i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nSetup Board");

    //getChipInfo();
    #ifdef I2C_SDA
        Wire.begin(I2C_SDA, I2C_SCL);
    #endif

#ifdef HAS_GPS

#ifdef GPS_EN_PIN
    pinMode(GPS_EN_PIN, OUTPUT);
    digitalWrite(GPS_EN_PIN, HIGH);
#endif /*GPS_EN_PIN*/

#ifdef GPS_PPS_PIN
    pinMode(GPS_PPS_PIN, INPUT);
#endif

#if defined(ARDUINO_ARCH_ESP32)
    SerialGPS.begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
#elif defined(ARDUINO_ARCH_STM32)
    SerialGPS.setRx(GPS_RX_PIN);
    SerialGPS.setTx(GPS_TX_PIN);
    SerialGPS.begin(GPS_BAUD_RATE);
#endif // ARDUINO_ARCH_
#endif // HAS_GPS
    // When the power is turned on, a delay is required.
    delay(1500);

    Serial.println("DeviceExample.ino");
    Serial.println("A simple demonstration of TinyGPS++ with an attached GPS module");
    Serial.print("Testing TinyGPS++ library v. ");
    Serial.println(TinyGPSPlus::libraryVersion());
    Serial.println("by Mikal Hart\n");
}

//=======================================================================================
void loop()
{
    // This sketch displays information every time a new sentence is correctly encoded.
    while (SerialGPS.available() > 0)
        if (gps.encode(SerialGPS.read())) displayInfo();

    if (millis() > 15000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS detected: check wiring."));
        delay(15000);
    }
}

