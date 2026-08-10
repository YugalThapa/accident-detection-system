#include "button.h"
#include "config.h"

void initButtons()
{
    pinMode(SOS_BUTTON_PIN, INPUT_PULLUP);
    pinMode(CANCEL_BUTTON_PIN, INPUT_PULLUP);

    Serial.println("Buttons Initialized");
}

bool isSOSPressed()
{
    return digitalRead(SOS_BUTTON_PIN) == LOW;
}

bool isCancelPressed()
{
    return digitalRead(CANCEL_BUTTON_PIN) == LOW;
}
