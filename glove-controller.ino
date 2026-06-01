//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize the LCD (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

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

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Mouse: Booting");
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

  // --- LCD UPDATE LOGIC ---
  // Determine current mode
  int currentMode = 0; // Idle
  if (b1 == 0 && b3 == 0) {
    currentMode = 2; // Scroll Mode
  } else if (b1 == 0) {
    currentMode = 1; // Move Mode
  }

  // Rewrite LCD
  if (currentMode != lastMode || b2 != lastLMB || b3 != lastRMB) {
    lcd.clear();
    
    // Top Row: Status
    lcd.setCursor(0, 0);
    if (currentMode == 2) lcd.print("Mode: Scrolling");
    else if (currentMode == 1) lcd.print("Mode: Stop Moving");
    else lcd.print("Mode: Default");

    // Bottom Row: Active Clicks
    lcd.setCursor(0, 1);
    if (b1 == 0 && b3 == 0) {
      lcd.print("");
    } else if (b2 == 0) {
      lcd.print("LMB");
    } else if (b3 == 0) {
      lcd.print("RMB");
    }
    
    // Save current state
    lastMode = currentMode;
    lastLMB = b2;
    lastRMB = b3;
  }

  // --- SERIAL OUTPUT ---
  Serial.print(GyX); Serial.print(",");
  Serial.print(GyY); Serial.print(",");
  Serial.print(GyZ); Serial.print(",");
  Serial.print(b1); Serial.print(",");
  Serial.print(b2); Serial.print(",");
  Serial.println(b3);

  delay(15);
}