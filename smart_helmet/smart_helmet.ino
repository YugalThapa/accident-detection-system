#include "config.h"
#include "IR_sensor.h"
#include "gps.h"
#include "buzzer.h"
#include "button.h"
#include "mpu6050.h"

MPU6050 imu;

void setup()
{
    Serial.begin(DEBUG_BAUD);   // DEBUG_BAUD = 115200

    // initilizing all components
    initIRSensor();
    initGPS();
    initBuzzer();
    initButtons();
    imu.begin();
    imu.calibrate(200);

    Serial.println("System Ready");
}

void loop()
{
    imu.update();
    updateGPS();          // Always keep GPS updated

    float rawMagnitude = imu.getRawAccelerationMagnitude();

    if (!isHelmetWorn())        // testing false condition first, if helmet not worn then return to next loop continuously check for helmet worn
    {
        buzzerOff();
        Serial.println("Helmet Not Worn");
        Serial.print("rawMagnitude: ");
        Serial.println(rawMagnitude);
        delay(500);

        return;
    }

    // if helmet is worn then system continue to check for accident
    Serial.println("Helmet Worn");
    Serial.print("rawMagnitude: ");
    Serial.println(rawMagnitude);

    // Simulate accident
    if (imu.isRealAccidentDetected())            // temprory accident simulation using push button
    {
        Serial.println("ACCIDENT DETECTED!");

        buzzerOn();

        unsigned long startTime = millis();

        // timer for cancel button
        while (millis() - startTime < ACCIDENT_DELAY)
        {
            if (isCancelPressed())
            {
                Serial.println("Alert Cancelled");

                buzzerOff();

                return;
            }

            delay(20);
        }

        // buzzerOff();

        Serial.println("Sending Emergency Alert...");

        // gps information
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

        // sendSMS();   <-- Later
    }

    delay(500);
}




   

