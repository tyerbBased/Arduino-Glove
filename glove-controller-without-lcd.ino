//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int MPU_ADDR = 0x68;
int16_t GyX, GyY, GyZ;

const int btnEnable = 2;
const int btnLeft = 3;
const int btnRight = 4;

// State tracking variables to prevent LCD update lag
int lastMode = -1; // 0=Idle, 1=Move, 2=Scroll
int lastLMB = -1;
int lastRMB = -1;

void setup() {
  Wire.begin();
  
  // Initialize GY-6500
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(115200);

  pinMode(btnEnable, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
}

void loop() {
  // Read Gyro
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // Read Buttons
  int b1 = digitalRead(btnEnable);
  int b2 = digitalRead(btnLeft);
  int b3 = digitalRead(btnRight);

  // --- SERIAL OUTPUT ---
  Serial.print(GyX); Serial.print(",");
  Serial.print(GyY); Serial.print(",");
  Serial.print(GyZ); Serial.print(",");
  Serial.print(b1); Serial.print(",");
  Serial.print(b2); Serial.print(",");
  Serial.println(b3);

  delay(15);
}
