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

Add screenshots or GIFs here showing the controller in action.

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
* 3 Push Buttons
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
git clone https://github.com/username/arduino-gyro-mouse.git
cd arduino-gyro-mouse
```

### 2. Upload Arduino Firmware

1. Open `arduino_mouse.ino`
2. Select your Arduino Uno board
3. Upload the sketch

### 3. Run the Python Receiver

```bash
python receiver.py
```

---

## 🎮 Controls

| Button   | Action        |
| -------- | ------------- |
| Button 1 | Left Click    |
| Button 2 | Right Click   |
| Button 3 | Custom Action |

Moving the gyroscope controls the mouse cursor.

---

## 📂 Project Structure

```text
arduino-gyro-mouse/
│
├── Arduino/
│   └── arduino_mouse.ino
│
├── Python/
│   └── receiver.py
│
├── Assets/
│   └── screenshots/
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

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome.

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Open a Pull Request

---

## 📜 License

This project is licensed under the MIT License.

---

## ⭐ Support

If you found this project useful, consider giving it a star on GitHub!
