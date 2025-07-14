# Lumio-air-pointer
Air Mouse – Works like a regular mouse but by moving the device in mid‑air; built-in motion sensors (accelerometer + gyroscope) let your hand movements control the on-screen cursor.

---

## 🚀 What It Does

✅ Move your mouse **by tilting your hand in the air**.  
✅ Click, double-click, and right-click using **physical buttons**.  
✅ Perform **drag-and-drop gestures** with a long press.  
✅ Works via **USB Serial using Arduino + Python (PyAutoGUI)**.

---

## 🛠️ How It Works

- Uses **MPU6050 (accelerometer + gyroscope)** to detect your hand movements.
- Arduino interprets these movements and sends commands like `MOUSE_LEFT`, `LEFT_CLICK` over Serial.
- A **Python script reads these commands** and controls your system mouse using PyAutoGUI.

---

## ⚙️ Hardware Used

- Arduino Nano / Pro Micro (USB HID or Serial)
- MPU6050 Motion Sensor
- Push buttons (left-click, right-click)
- Optional: 3D-printed wearable enclosure

---

## 🖥️ Software Stack

- **Arduino (C++)** for sensor reading + Serial communication
- **Python (PyAutoGUI + PySerial)** for cursor control
- Runs on **Windows, Linux, or macOS** with minor adjustments

---

## 📦 Installation

### 1️⃣ Arduino Setup
- Wire up your **MPU6050 + buttons** to your Arduino.
- Upload the provided `air_mouse.ino` sketch to your Arduino.

### 2️⃣ Python Dependencies
Install required Python libraries:
```bash
pip install pyautogui pyserial
