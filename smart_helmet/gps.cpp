#include "gps.h"
#include <TinyGPS++.h>

// Private Objects 
static TinyGPSPlus gps;               // new object named "gps" is created
static HardwareSerial gpsSerial(2);   // using UART2 (TX2,RX2) for communication

// GPS Data 
static float latitude = 0.0;      // store latitude
static float longitude = 0.0;     // store longitude
static float altitude = 0.0;      // Stores altitude in meters
static float speed = 0.0;         // store speed of rider in km/h

static uint8_t satellites = 0;    // Stores the number of satellites currently being used

static String date = "";          // store current date as 04/08/2026
static String timeUTC = "";       // store current time as 14:25:32

static String googleMapLink = ""; // store google map link

static bool gpsFix = false;       // if false then no gps fix, if yes then valid position

// initilizing gps 
void initGPS()
{
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);    // GPS_BAUD = 9600, GPS_RX_PIN = 16, GPS_TX_PIN = 17    

    Serial.println("================================");
    Serial.println("GPS Initialized");
    Serial.println("Waiting for satellite fix...");
    Serial.println("================================");
}

// updating the gps locations
void updateGPS()
{
    while (gpsSerial.available())           // check for any data(byte)
    {
        gps.encode(gpsSerial.read());       // Read byte then give it to TinyGPS++
    }

    if (gps.location.isUpdated())           // check for new location
    {
        gpsFix = gps.location.isValid();    // true if the location is valid

        if (gpsFix)
        {
            latitude = gps.location.lat();
            longitude = gps.location.lng();

            altitude = gps.altitude.meters();

            speed = gps.speed.kmph();

            satellites = gps.satellites.value();

            char buffer[20];

            sprintf(buffer,
                    "%02d/%02d/%04d",
                    gps.date.day(),
                    gps.date.month(),
                    gps.date.year());

            date = String(buffer);

            // Convert UTC to Nepal Standard Time (UTC +5:45)

            // int hour = gps.time.hour();
            // int minute = gps.time.minute();
            // int second = gps.time.second();

            // // Add Nepal offset
            // minute += 45;
            // hour += 5;

            // // Handle minute overflow
            // if (minute >= 60)
            // {
            //     minute -= 60;
            //     hour++;
            // }

            // // Handle hour overflow
            // if (hour >= 24)
            // {
            //     hour -= 24;
            // }

            // char buffer[20];

            // sprintf(buffer,
            //         "%02d:%02d:%02d",
            //         hour,
            //         minute,
            //         second);

            // timeUTC = String(buffer);

            sprintf(buffer,
                    "%02d:%02d:%02d",
                    gps.time.hour(),
                    gps.time.minute(),
                    gps.time.second());

            timeUTC = String(buffer);

            googleMapLink = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
        }
    }
}

// return true is gps is fixed
bool isGPSFixed()
{
    return gpsFix;
}

// return latitude only
float getLatitude()
{
    return latitude;
}

// retun longitude only
float getLongitude()
{
    return longitude;
}

// return altitude only
float getAltitude()
{
    return altitude;
}

// return speed only
float getSpeed()
{
    return speed;
}

// return number of setallites used
uint8_t getSatellites()
{
    return satellites;
}

// return date only
String getDate()
{
    return date;
}

// return time only
String getTime()
{
    return timeUTC;
}

String getGoogleMapsLink()
{
    return googleMapLink;
}