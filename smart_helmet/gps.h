#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include "config.h"

void initGPS();
void updateGPS();

bool isGPSFixed();

float getLatitude();
float getLongitude();

float getAltitude();
float getSpeed();

uint8_t getSatellites();

String getDate();
String getTime();

String getGoogleMapsLink();

#endif