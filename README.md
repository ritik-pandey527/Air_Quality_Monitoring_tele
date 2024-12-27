# IoT-Based Smart Monitoring and Alert System

An IoT-based system for real-time environmental monitoring and alerting, leveraging sensors and Telegram bot integration for remote control and notifications.

## Features

- **Temperature & Humidity Monitoring**: Tracks environmental temperature and humidity using a DHT11 sensor.
- **Gas Level Detection**: Detects harmful gas levels with an MQ2 sensor and sends alerts when thresholds are exceeded.
- **Fire Detection**: Monitors fire presence using a flame sensor.
- **Alerts & Notifications**: Sends alerts to users via a Telegram bot for dangerous conditions.
- **User Commands via Telegram**: 
  - `/sensor` for current readings.
  - `/stop_buzzer` to stop the alarm.
- **Real-Time Display**: Shows sensor data on a 16x2 LCD.
- **Alarm System**: Triggers a buzzer during emergencies.

## Components

- **ESP32**: Microcontroller for Wi-Fi connectivity and sensor interfacing.
- **DHT11 Sensor**: Measures temperature and humidity.
- **MQ2 Gas Sensor**: Monitors gas levels.
- **Flame Sensor**: Detects fire.
- **Active Buzzer**: Alerts users with sound.
- **16x2 LCD with I2C Module**: Displays sensor data.

## Circuit Diagram

- **DHT11**: Connected to pin 19.
- **MQ2 Sensor**: Analog output connected to pin 34.
- **Flame Sensor**: Digital output connected to pin 5.
- **Buzzer**: Active-low, connected to pin 2.
- **LCD Display**: Connected via I2C (default address 0x27).

## Getting Started

### Prerequisites

1. **Arduino IDE** with the following libraries installed:
   - `LiquidCrystal_I2C`
   - `DHT`
   - `WiFi`
   - `WiFiClientSecure`
   - `UniversalTelegramBot`
   - `ArduinoJson`

2. A Telegram bot. Follow these steps to create one:
   - Open Telegram and search for the BotFather.
   - Use `/newbot` to create a new bot and get your bot token.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/<repository-name>.git
   cd <repository-name>
