# 🎮 Arduino Gyro Mouse Driver

Transform your Arduino Uno into a motion-controlled mouse using a gyroscope and customizable buttons.

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![Language](https://img.shields.io/badge/Python-3.x-yellow)
![License](https://img.shields.io/badge/License-MIT-green)

---

## ✨ Features

* 🖱️ Gyroscope-based cursor movement
* 🎯 Smooth and responsive mouse control
* 🔘 Three programmable control buttons
* 🔌 Simple USB serial communication
* 🐍 Python receiver application for desktop integration
* ⚡ Lightweight and easy to customize

---

## 📷 Preview

```text
Arduino Uno + Gyroscope
          │
          ▼
    Serial USB
          │
          ▼
    Python Receiver
          │
          ▼
      Mouse Input
```

---

## 🛠 Hardware Requirements

* Arduino Uno
* MPU6050 (or compatible gyroscope/accelerometer)
* 3 Push Buttons (I used HATOR Aurum mechanical switches)
* USB Cable

---

## 📦 Software Requirements

* Python 3.10+
* Arduino IDE

### Python Dependencies

```bash
pip install pyserial pynput
```

---

## 🚀 Installation

### 1. Clone the repository

```bash
git clone https://github.com/tyerbBased/Arduino-Glove.git
cd Arduino-Glove
```

### 2. Upload Arduino Firmware

1. Open `glove-controller.ino` or `glove-controller-without-lcd.ino` if you don't want to use it with LCD.
2. Select your Arduino Uno board
3. Upload the sketch

### 3. Run the Python Receiver

```bash
python glove-driver.py
```
You can customize sensitivity or dead-zones inside python script.

---

## 🎮 Controls

| Button   | Action        |
| -------- | ------------- |
| Button 1 (Pin 2)    | Stop Moving  |
| Button 2 (Pin 3)    | Left Click   |
| Button 3 (Pin 4)    | Right Action |
| Button 1 + Button 3 | Scrolling    |

Moving the gyroscope controls the mouse cursor.

---

## 📂 Project Structure

```text
Arduino-Glove/
│
├── glove-controller.ino
│
├── glove-controller-with-lcd.ino
│
├── glove-driver.py
│
└── README.md
```

---

## ⚙️ How It Works

The Arduino reads gyroscope and button data and sends it through a serial connection.

The Python application:

* Receives serial data
* Interprets movement values
* Moves the system cursor
* Handles mouse button events

This approach allows the Arduino Uno to function as a motion-controlled mouse without requiring native USB HID support.

---

## 🔧 Customization

You can easily modify:

* Cursor sensitivity
* Dead zone filtering
* Button mappings
* Smoothing algorithms
* Serial communication speed

---

## 📜 License

This project is licensed under the MIT License.

---

## ⭐ Support

If you found this project useful, consider giving it a star on GitHub!
