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

#include <U8g2lib.h>
#include <TinyGPS++.h>

#include "configuration.h"

//====== Timer for periodical events u.a.
#include "Timeout.h"
Timeout timerSerial;


#ifdef DISPLAY_MODEL
    uint8_t  display_address = 0x3c;    // It might be 0x3D
    //U8G2 *disp = NULL;
    DISPLAY_MODEL *disp = NULL;
    #define U8G2_HOR_ALIGN_CENTER(t)    ((disp->getDisplayWidth() -  (disp->getUTF8Width(t))) / 2)
    #define U8G2_HOR_ALIGN_RIGHT(t)     ( disp->getDisplayWidth()  -  disp->getUTF8Width(t))

    bool beginDisplay()
    {
        Wire.beginTransmission(display_address);
        if (Wire.endTransmission() == 0) {
            Serial.printf("Find Display model at 0x%X address\n", display_address);
            disp = new DISPLAY_MODEL(U8G2_R0, U8X8_PIN_NONE);
            disp->begin();
            disp->clearBuffer();
            disp->setFont(u8g2_font_inb19_mr);
            disp->drawStr(0, 30, "LilyGo");
            disp->drawHLine(2, 35, 47);
            disp->drawHLine(3, 36, 47);
            disp->drawVLine(45, 32, 12);
            disp->drawVLine(46, 33, 12);
            disp->setFont(u8g2_font_inb19_mf);
            disp->drawStr(58, 60, "LoRa");
            disp->sendBuffer();
            disp->setFont(u8g2_font_fur11_tf);
            delay(3000);
            return true;
        }
        Serial.printf("Warning: Failed to find Display at 0x%0X address\n", display_address);
        return false;
    }
    
#endif  //DISPLAY_MODEL

#ifdef HAS_GPS
    TinyGPSPlus gps;
    #define SerialGPS Serial1
    static bool find_gps = false;
    String gps_model = "None";



bool l76kProbe()
{
    bool result = false;
    uint32_t startTimeout ;
    Serial.print(">>> $PCAS03,0,0,0,0,0,0,0,0,0,0,,,0,0*02\r\n");
    SerialGPS.write("$PCAS03,0,0,0,0,0,0,0,0,0,0,,,0,0*02\r\n");
    delay(5);
    // Get version information
    startTimeout = millis() + 3000;
    Serial.print("Try to init L76K . Wait stop .");
    // SerialGPS.flush();
    while (SerialGPS.available()) {
        int c = SerialGPS.read();
        Serial.write(c);
        Serial.print(".");
        Serial.flush();
        SerialGPS.flush();
        if (millis() > startTimeout) {
            Serial.println("Wait L76K stop NMEA timeout!");
            return false;
        }
    };
    Serial.println();
    SerialGPS.flush();
    delay(200);

    Serial.print(">>> $PCAS06,0*1B\r\n");
    SerialGPS.write("$PCAS06,0*1B\r\n");
    startTimeout = millis() + 500;
    String ver = "";
    while (!SerialGPS.available()) {
        if (millis() > startTimeout) {
            Serial.println("Get L76K timeout!");
            return false;
        }
    }
    SerialGPS.setTimeout(10);
    ver = SerialGPS.readStringUntil('\n');
    if (ver.startsWith("$GPTXT,01,01,02")) {
        Serial.println("L76K GNSS init succeeded, using L76K GNSS Module\n");
        result = true;
    }
    delay(500);

    // Initialize the L76K Chip, use GPS + GLONASS
    Serial.print(">>> $PCAS04,5*1C\r\n");
    SerialGPS.write("$PCAS04,5*1C\r\n");
    delay(250);
    // only ask for RMC and GGA
    Serial.print(">>> $PCAS03,1,0,0,0,1,0,0,0,0,0,,,0,0*02\r\n");
    SerialGPS.write("$PCAS03,1,0,0,0,1,0,0,0,0,0,,,0,0*02\r\n");
    delay(250);
    // Switch to Vehicle Mode, since SoftRF enables Aviation < 2g
    Serial.print(">>> $PCAS11,3*1E\r\n");
    SerialGPS.write("$PCAS11,3*1E\r\n");
    return result;
}

bool beginGPS()
{
    SerialGPS.begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    bool result = false;
    for ( int i = 0; i < 3; ++i) {
        result = l76kProbe();
        if (result) {
            return result;
        }
    }
    return result;
}

#endif  //HAS_GPS



void displayInfo() {
    if (disp) {
        disp->clearBuffer();
        disp->setFont(u8g2_font_pxplusibmvga8_mr);
        disp->setCursor(5, 15); disp->print("LAT: ");
        disp->setCursor(5, 30); disp->print("LON: ");
        disp->setCursor(5, 45); disp->print("Date: ");
        disp->setCursor(5, 60); disp->print("Time: ");

        disp->setFont(u8g2_font_crox1h_tr);
        if (gps.location.isValid()) {
            disp->setCursor(40, 15); disp->print(gps.location.lat(), 6);
            disp->setCursor(40, 30); disp->print(gps.location.lng(), 6);
        } else {
            disp->setCursor(40, 15); disp->print("INVALID");
            disp->setCursor(40, 30); disp->print("INVALID");
        }
        if (gps.date.isValid()) {
            disp->setCursor(50, 45); disp->printf("%u. %u. %u", gps.date.day(),gps.date.month(),gps.date.year());
        } else {
            disp->setCursor(50, 45); disp->print("INVALID");
        }
        if (gps.time.isValid()) {
            disp->setCursor(50, 60); disp->printf("%2u:%2u:%2u.%2u", gps.time.hour(),gps.time.minute(),gps.time.second(),gps.time.centisecond());
        } else {
            disp->setCursor(50, 60); disp->print("INVALID");
        }
            
        disp->sendBuffer();
    }
}

//=======================================================================================
void printInfo()
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
        Serial.print(gps.date.day());
        Serial.print(F("."));
        Serial.print(gps.date.month());
        Serial.print(F("."));
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
    timerSerial.start(2000);
    Serial.begin(115200);
    while (!Serial && !timerSerial.time_over());
    if (Serial) { for (int i=0;i<10;i++) { Serial.println("."); delay(1000); } }

    //getChipInfo();
    #ifdef I2C_SDA
        Wire.begin(I2C_SDA, I2C_SCL);
    #endif

    Serial.println("\nSetup Board");

    beginDisplay();

    Serial.println("TinyGPS_Example");
    Serial.println("A simple demonstration of TinyGPS++ with an attached GPS module");
    Serial.printf("Testing TinyGPS++ library v. %s by Mikal Hart\n\n", TinyGPSPlus::libraryVersion());

    #ifdef HAS_GPS

        #ifdef GPS_EN_PIN
            pinMode(GPS_EN_PIN, OUTPUT);
            digitalWrite(GPS_EN_PIN, HIGH);
        #endif /*GPS_EN_PIN*/

        #ifdef GPS_PPS_PIN
            pinMode(GPS_PPS_PIN, INPUT);
        #endif // GPS_PPS_PIN

        #if defined(ARDUINO_ARCH_ESP32)
            SerialGPS.begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
        #endif // ARDUINO_ARCH_ESP32

        #if defined(T_BEAM_1W)
            find_gps = beginGPS();
            gps_model = "L76K";
            if(find_gps) {
                Serial.printf("GPS_MODEL %s found", gps_model);
            } else { Serial.printf("GPS_MODEL %s NOT found", gps_model); }
        #endif

    #endif // HAS_GPS

}

//=======================================================================================
void loop()
{
    // This sketch displays information every time a new sentence is correctly encoded.
    while (SerialGPS.available() > 0)
        if (gps.encode(SerialGPS.read())) {
            displayInfo();
            printInfo();
        }

    if (millis() > 15000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS detected: check wiring."));
        delay(15000);
    }
}

