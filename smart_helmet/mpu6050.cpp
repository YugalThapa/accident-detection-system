#include "mpu6050.h"
#include "config.h"
#include <math.h>

#define PWR_MGMT_1 0x6B
#define WHO_AM_I 0x75
#define ACCEL_XOUT_H 0x3B

bool MPU6050::begin() {
  Wire.begin(SDA_PIN, SCL_PIN);

  // Wake up the sensor
  writeRegister(0x6B, 0);

  uint8_t id = readRegister(0x75);

  Serial.print("WHO_AM_I = 0x");
  Serial.println(id, HEX);

  return (id == 0x72);
}

void MPU6050::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t MPU6050::readRegister(uint8_t reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom((uint8_t)address, (uint8_t)1);

  if (Wire.available())
    return Wire.read();

  return 0;
}

void MPU6050::update() {
  Wire.beginTransmission(address);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);

  Wire.requestFrom((uint8_t)address, (uint8_t)14);

  accelX = (Wire.read() << 8) | Wire.read();
  accelY = (Wire.read() << 8) | Wire.read();
  accelZ = (Wire.read() << 8) | Wire.read();

  // Skip temperature
  Wire.read();
  Wire.read();

  gyroX = (Wire.read() << 8) | Wire.read();
  gyroY = (Wire.read() << 8) | Wire.read();
  gyroZ = (Wire.read() << 8) | Wire.read();

  float ax = accelX / 16384.0;
  float ay = accelY / 16384.0;
  float az = accelZ / 16384.0;


  filteredAccelX = lowPassFilter(ax, filteredAccelX);
  filteredAccelY = lowPassFilter(ay, filteredAccelY);
  filteredAccelZ = lowPassFilter(az, filteredAccelZ);
}

void MPU6050::calibrate(uint16_t samples) {
  Serial.println("Keep the helmet stationary...");
  delay(2000);

  float sumAx = 0;
  float sumAy = 0;
  float sumAz = 0;

  float sumGx = 0;
  float sumGy = 0;
  float sumGz = 0;

  for (uint16_t i = 0; i < samples; i++) {
    update();

    sumAx += accelX / 16384.0;
    sumAy += accelY / 16384.0;
    sumAz += accelZ / 16384.0;

    sumGx += gyroX / 131.0;
    sumGy += gyroY / 131.0;
    sumGz += gyroZ / 131.0;

    delay(5);
  }

  accelOffsetX = sumAx / samples;
  accelOffsetY = sumAy / samples;

  // Gravity should be +1 g on Z
  accelOffsetZ = (sumAz / samples) - 1.0;

  gyroOffsetX = sumGx / samples;
  gyroOffsetY = sumGy / samples;
  gyroOffsetZ = sumGz / samples;

  Serial.println("Calibration Complete!");

  Serial.print("Accel Offset X: ");
  Serial.println(accelOffsetX, 4);

  Serial.print("Accel Offset Y: ");
  Serial.println(accelOffsetY, 4);

  Serial.print("Accel Offset Z: ");
  Serial.println(accelOffsetZ, 4);

  Serial.print("Gyro Offset X: ");
  Serial.println(gyroOffsetX, 4);

  Serial.print("Gyro Offset Y: ");
  Serial.println(gyroOffsetY, 4);

  Serial.print("Gyro Offset Z: ");
  Serial.println(gyroOffsetZ, 4);
}

float MPU6050::getAccelX() {
  return filteredAccelX - accelOffsetX;
}

float MPU6050::getAccelY() {
  return filteredAccelY - accelOffsetY;
}

float MPU6050::getAccelZ() {
  return filteredAccelZ - accelOffsetZ;
}

float MPU6050::getGyroX() {
  return (gyroX / 131.0) - gyroOffsetX;
}

float MPU6050::getGyroY() {
  return (gyroY / 131.0) - gyroOffsetY;
}

float MPU6050::getGyroZ() {
  return (gyroZ / 131.0) - gyroOffsetZ;
}

float MPU6050::getAccelerationMagnitude() {
  float ax = getAccelX();
  float ay = getAccelY();
  float az = getAccelZ();

  return sqrt(ax * ax + ay * ay + az * az);
}

float MPU6050::lowPassFilter(float current, float previous) {
  return alpha * current + (1 - alpha) * previous;
}

float MPU6050::getRoll() {
  float x = getAccelX();
  float y = getAccelY();
  float z = getAccelZ();

  float roll = atan2(y, sqrt(x * x + z * z));

  return roll * 180.0 / PI;
}

float MPU6050::getPitch() {
  float x = getAccelX();
  float y = getAccelY();
  float z = getAccelZ();

  float pitch = atan2(-x, sqrt(y * y + z * z));

  return pitch * 180.0 / PI;
}

float MPU6050::getRawAccelerationMagnitude() {
  float ax = accelX / 16384.0;
  float ay = accelY / 16384.0;
  float az = accelZ / 16384.0;

  return sqrt(ax * ax + ay * ay + az * az);
}

bool MPU6050::isRealAccidentDetected(){
  if (getRawAccelerationMagnitude() > 1.2) {
    return true;
  }
  else{
    return false;
  }
}