#ifndef SIM_H
#define SIM_H

#include <Arduino.h>

void initSIM();
void sendCommand(String command, int waitTime);
void sendSMS(String phoneNumber, String message);

#endif