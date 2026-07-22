#include "config.h"
#include "IR_sensor.h"
#include "gps.h"

void setup()
{
    Serial.begin(DEBUG_BAUD);   // DEBUG_BAUD = 115200

    // initilizing all components
    initIRSensor();
    initGPS();

    Serial.println("System Ready");
}

void loop()
{
    if (isHelmetWorn())     // runs when helmet is worn, IR detect object
    {
        Serial.println("Helmet Worn");
        updateGPS();        // updating gps only after helmet is worn
        
        if (isGPSFixed())
        {
            Serial.println("GPS FIXED");

            Serial.print("Latitude : ");
            Serial.println(getLatitude(), 6);

            Serial.print("Longitude: ");
            Serial.println(getLongitude(), 6);

            Serial.print("Satellites: ");
            Serial.println(getSatellites());
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
    }
    //Serial.println(getIRValue());   // print 0 when detected otherwise 1
    delay(500);
}

