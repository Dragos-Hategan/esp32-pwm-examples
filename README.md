# ESP32 PWM Examples

This repository contains simple and practical examples of using **PWM (Pulse Width Modulation)** on the **ESP32**, written with the **ESP-IDF** framework.

---

## What’s Inside
- Basic PWM signal generation
- Controlling LED brightness
- Driving a motor with variable speed
- Multiple channels PWM usage
- Duty cycle adjustments in real-time

---

## Requirements
- **ESP32 DevKit v1** (or similar board)
- **ESP-IDF** installed → [Setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)

---

## Build & Flash
```bash
idf.py set-target esp32
idf.py build
idf.py -p COMx flash monitor   # replace COMx with your serial port
