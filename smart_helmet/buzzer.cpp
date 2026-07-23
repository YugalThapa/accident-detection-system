#include "buzzer.h"
#include "config.h"

bool buzzerState = false;

void initBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);          // BUZZER_PIN = 14
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer Initialized");
}

void buzzerOn()
{
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerState = true;
}

void buzzerOff()
{
    digitalWrite(BUZZER_PIN, LOW);
    buzzerState = false;
}

void toggleBuzzer()
{
    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState);
}

void beep(unsigned int duration)
{
    buzzerOn();

    delay(duration);

    buzzerOff();
}