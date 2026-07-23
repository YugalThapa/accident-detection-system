#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

void initBuzzer();

void buzzerOn();
void buzzerOff();

void toggleBuzzer();

void beep(unsigned int duration);

#endif