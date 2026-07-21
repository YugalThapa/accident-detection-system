#include "config.h"
#include "IR_sensor.h"

void setup()
{
    Serial.begin(DEBUG_BAUD);   // DEBUG_BAUD = 115200

    initIRSensor();

    Serial.println("System Ready");
}

void loop()
{
    if (isHelmetWorn())     // runs when helmet is worn, IR detect object
    {
        Serial.println("Helmet Worn");
    }
    else
    {
        Serial.println("Helmet Not Worn");
    }
    //Serial.println(getIRValue());   // print 0 when detected otherwise 1
    delay(500);
}