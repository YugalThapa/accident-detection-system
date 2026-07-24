#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

void initButtons();

bool isSOSPressed();
bool isCancelPressed();

// temprory accident simulation
bool isAccidentPressed();

#endif