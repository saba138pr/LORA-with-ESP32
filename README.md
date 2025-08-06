# LORA-with-ESP32
Simple LoRa communication project using two ESP32 boards. One acts as a transmitter sending data (like PWM values), and the other as a receiver. Ideal for IoT beginners.
# 📡 LoRa Communication with ESP32

This project demonstrates a simple and effective communication system using LoRa modules and two ESP32 boards. One board functions as the **transmitter**, periodically sending data, and the other board acts as the **receiver**, receiving and processing that data.

## 🚀 Features

- LoRa-based wireless communication
- Low-power, long-range data transmission
- PWM value generation and transmission (customizable)
- Simple codebase – easy to modify and expand
- Suitable for IoT beginners and enthusiasts

## 🧰 Hardware Used

- 2 × ESP32 Development Boards
- 2 × LoRa SX1278 Modules (or compatible)
- Jumper wires
- Breadboard or PCB

## 🔌 Basic Connections

| ESP32 Pin | LoRa Pin |
|-----------|----------|
| 3.3V      | VCC      |
| GND       | GND      |
| GPIO18    | SCK      |
| GPIO23    | MOSI     |
| GPIO19    | MISO     |
| GPIO5     | NSS (CS) |
| GPIO14    | RESET    |
| GPIO26    | DIO0     |

> ⚠️ Make sure to power the LoRa module with 3.3V. Do **not** use 5V.

## 📁 Project Structure

