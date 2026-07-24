#ifndef CONFIG_H
#define CONFIG_H


// MPU6050 (I2C)
#define SDA_PIN             21
#define SCL_PIN             22


// GPS (UART2)
#define GPS_RX_PIN          16      // ESP32 receives (RX2)from GPS TX
#define GPS_TX_PIN          17      // ESP32 transmits (TX2) to GPS RX


// SIM800L (UART1)
#define GSM_RX_PIN          26      // ESP32 receives from GSM TX
#define GSM_TX_PIN          25      // ESP32 transmits to GSM RX


// IR Sensor
#define IR_SENSOR_PIN       18


// Active Buzzer
#define BUZZER_PIN          14


// Push Buttons
#define SOS_BUTTON_PIN      27
#define CANCEL_BUTTON_PIN   33
#define ACCIDENT_BUTTON_PIN  25


// SERIAL BAUD RATES
#define DEBUG_BAUD          115200
#define GPS_BAUD            9600
#define GSM_BAUD            9600


// ACCIDENT DETECTION PARAMETERS
// Acceleration threshold (g)
#define ACCIDENT_THRESHOLD      3.0
// Helmet tilt angle (degree)
#define TILT_THRESHOLD          60
// Accident confirmation delay (ms)
#define ACCIDENT_DELAY          5000


// GPS SETTINGS
#define GPS_TIMEOUT         10000      // milliseconds
// GSM SETTINGS
#define PHONE_NUMBER        "+97798XXXXXXXX"
// SMS Message
#define ALERT_MESSAGE       "Emergency! Accident detected. Location:"


// BUZZER SETTINGS
#define BUZZER_ON           HIGH
#define BUZZER_OFF          LOW
#define BUZZER_DURATION     500


// IR SENSOR LOGIC
// Change this if your sensor behaves opposite
#define HELMET_WORN         LOW     // because detect = 0 output by IR
#define HELMET_NOT_WORN     HIGH



// BUTTON LOGIC
#define BUTTON_PRESSED      LOW
#define BUTTON_RELEASED     HIGH


#endif