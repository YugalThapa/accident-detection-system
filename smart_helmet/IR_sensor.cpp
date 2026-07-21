#include <Arduino.h>

#include "config.h"
#include "IR_sensor.h"

void initIRSensor()
{
    pinMode(IR_SENSOR_PIN, INPUT);
}

bool isHelmetWorn()
{
    return (digitalRead(IR_SENSOR_PIN) == HELMET_WORN);
}

int getIRValue()
{
    return digitalRead(IR_SENSOR_PIN);
}