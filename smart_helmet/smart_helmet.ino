#include "config.h"
#include "IR_sensor.h"
#include "gps.h"
#include "buzzer.h"
#include "button.h"
#include "mpu6050.h"
#include "sim.h"

void sendAlertMessage();
MPU6050 imu;

void setup()
{
    Serial.begin(DEBUG_BAUD);   // DEBUG_BAUD = 115200

    // initilizing all components
    initIRSensor();
    initGPS();
    initBuzzer();
    buzzerOff();
    initButtons();
    imu.begin();            // mpu6050 initialization
    imu.calibrate(200);     // mpu6050 calibration
    initSIM();

    Serial.println("System Ready");
}

void loop()
{
    imu.update();           // update mpu6050 sensor value
    updateGPS();          // Always keep GPS updated

    float rawMagnitude = imu.getRawAccelerationMagnitude();

    if (!isHelmetWorn())        // testing false condition first, if helmet not worn then return to next loop continuously check for helmet worn
    {
        // buzzerOff();
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
    Serial.print("Visible Satellites: ");
    Serial.println(getSatellites());

    // manual sos
    if (isSOSPressed()){
        Serial.println("Manual Alert Message!!!");
        sendAlertMessage();
        while(true){
            beep(500);
            Serial.println("BEEEEPPPPPPPPPPPP........ ");
        }
    }

    // Simulate accident automatically
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
            // beep(200);
            delay(20);
        }

        // sending alert message now
        Serial.println("Automatic Alert Message!!!");
        sendAlertMessage();
        while(true){
            beep(500);
            Serial.println("BEEEEPPPPPPPPPPPP........ ");
        }
 
    }

    delay(500);
}

// Sends alert message
void sendAlertMessage()
{
    Serial.println("================================");
    Serial.println("Sending Emergency Alert...");
    Serial.println("================================");

    String message;

    message += "SMART HELMET EMERGENCY ALERT!\n";
    message += "Possible accident detected.\n\n";

    if (isGPSFixed())
    {
        float latitude = getLatitude();
        float longitude = getLongitude();

        Serial.println("GPS FIXED");

        Serial.print("Latitude : ");
        Serial.println(latitude, 6);

        Serial.print("Longitude: ");
        Serial.println(longitude, 6);

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

        message += "Latitude: ";
        message += String(latitude, 6);

        message += "\nLongitude: ";
        message += String(longitude, 6);

        message += "\nTime: ";
        message += String(getTime());

        message += "\nDate: ";
        message += String(getDate());

        message += "\n\nLocation:\n";
        message += getGoogleMapsLink();
    }
    else
    {
        Serial.println("GPS FIX NOT AVAILABLE");

        Serial.print("Visible Satellites: ");
        Serial.println(getSatellites());

        message += "GPS location unavailable.\n";
        message += "Please check the rider immediately.";
    }
    
    simCommunication(message);
    
}


void simCommunication(String message){
    // Check communication
  sendCommand("AT", 1000);

  // Check SIM
  sendCommand("AT+CPIN?", 1000);

  // Check signal
  sendCommand("AT+CSQ", 1000);

  // Check network registration
  sendCommand("AT+CREG?", 1000);

  // Set SMS text mode
  sendCommand("AT+CMGF=1", 1000);

  // Send SMS
  sendSMS(EMERGENCY_PHONE, message);
}
   

