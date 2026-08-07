#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

class MPU6050 {
public:
  bool begin();
  void update();

  void calibrate(uint16_t samples = 200);

  float getAccelX();
  float getAccelY();
  float getAccelZ();

  float getGyroX();
  float getGyroY();
  float getGyroZ();

  float getAccelerationMagnitude();
  float getRawAccelerationMagnitude();
  bool isRealAccidentDetected();

  float getRoll();
  float getPitch();

private:
  const uint8_t address = 0x68;

  int16_t accelX;
  int16_t accelY;
  int16_t accelZ;

  int16_t gyroX;
  int16_t gyroY;
  int16_t gyroZ;

  float accelOffsetX = 0;
  float accelOffsetY = 0;
  float accelOffsetZ = 0;

  float gyroOffsetX = 0;
  float gyroOffsetY = 0;
  float gyroOffsetZ = 0;

  float filteredAccelX = 0;
  float filteredAccelY = 0;
  float filteredAccelZ = 0;

  float alpha = 0.2;

  float lowPassFilter(float current, float previous);

  void writeRegister(uint8_t reg, uint8_t value);
  uint8_t readRegister(uint8_t reg);
};

#endif