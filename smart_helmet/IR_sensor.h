#ifndef IR_SENSOR_H
#define IR_SENSOR_H

// Initialize IR Sensor
void initIRSensor();

// Read IR Sensor
bool isHelmetWorn();

// Get raw sensor value
int getIRValue();

#endif