#include "config.h"
#include "IR_sensor.h"
#include "gps.h"
#include "buzzer.h"

void setup()
{
    Serial.begin(DEBUG_BAUD);   // DEBUG_BAUD = 115200

    // initilizing all components
    initIRSensor();
    initGPS();
    initBuzzer();

    Serial.println("System Ready");
}

void loop()
{
    if (isHelmetWorn())     // runs when helmet is worn, IR detect object
    {   
        // for now IR detection is used as accident detection for testing
        Serial.println("Helmet Worn");
        buzzerOn();            // buzzer on whrn ir detect, for now ir is used as accident detection
        Serial.println("Buzzer ON");
        updateGPS();        // updating gps only after helmet is worn

        if (isGPSFixed())
        {
            Serial.println("GPS FIXED");

            Serial.print("Latitude : ");
            Serial.println(getLatitude(), 6);

            Serial.print("Longitude: ");
            Serial.println(getLongitude(), 6);

            Serial.print("Altitude: ");
            Serial.println(getAltitude());

            Serial.print("Speed: ");
            Serial.println(getSpeed());

            Serial.print("Satellites: ");
            Serial.println(getSatellites());

            Serial.print("Date: ");
            Serial.println(getDate());

            Serial.print("Time: ");
            Serial.println(getTime());

            Serial.print("Google Maps: ");
            Serial.println(getGoogleMapsLink());
        }
        else
        {
            Serial.println("Searching for satellites...");
            Serial.print("Visible Satellites: ");
            Serial.println(getSatellites());
        }
    }
    else
    {
        Serial.println("Helmet Not Worn");
        buzzerOff();
        Serial.println("Buzzer OFF");
    }
    //Serial.println(getIRValue());   // print 0 when detected otherwise 1
    delay(500);
}

