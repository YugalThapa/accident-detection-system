#include "sim.h"
#include "config.h"

static HardwareSerial sim800(2);

void initSIM(){
    Serial.begin(115200);

    // Start communication with SIM800L
    sim800.begin(9600, SERIAL_8N1, GSM_RX_PIN , GSM_TX_PIN );

    Serial.println("Initializing SIM800L...");
    delay(3000);

}


void sendCommand(String command, int waitTime) {

  Serial.println(">> " + command);

  sim800.println(command);

  delay(waitTime);

  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}

void sendSMS(String phoneNumber, String message) {

  Serial.println("Sending SMS...");

  // Tell SIM800L the recipient
  sim800.print("AT+CMGS=\"");
  sim800.print(phoneNumber);
  sim800.println("\"");

  delay(1000);

  // Send message
  sim800.print(message);

  delay(500);

  // CTRL+Z (ASCII 26) tells SIM800L to send the SMS
  sim800.write(26);

  Serial.println("SMS command sent.");

  // Wait for network/SMS response
  delay(5000);

  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}