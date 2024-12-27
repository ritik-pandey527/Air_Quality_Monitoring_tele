# IoT-Based Smart Monitoring and Alert System

## Overview
This project is an IoT-based system that monitors environmental conditions using multiple sensors and alerts users via a Telegram bot. It provides real-time updates on temperature, humidity, gas levels, and fire detection. Users can interact with the system through a Telegram bot to get sensor data or control the buzzer.

## Features
- **Temperature and Humidity Monitoring**: Uses a DHT11 sensor to measure environmental temperature and humidity.
- **Gas Detection**: An MQ2 sensor detects gas levels and raises alerts when the value exceeds a predefined threshold.
- **Fire Detection**: Monitors for the presence of fire using a flame sensor.
- **Alert Mechanism**: Sends notifications via Telegram in case of dangerous conditions.
- **User Commands**: Provides a menu to check sensor readings or stop the buzzer.
- **LCD Display**: Displays real-time sensor readings on a 16x2 LCD screen.

## Components
- **ESP32**: Microcontroller for sensor interfacing and Telegram bot communication.
- **DHT11 Sensor**: Measures temperature and humidity.
- **MQ2 Gas Sensor**: Detects gas levels.
- **Flame Sensor**: Detects the presence of fire.
- **Active Buzzer**: Alerts users during dangerous conditions.
- **16x2 LCD Display with I2C**: Displays sensor readings.

## Circuit Diagram
1. **DHT11 Sensor**: Connected to pin 19.
2. **MQ2 Sensor**: Connected to analog pin 34.
3. **Flame Sensor**: Connected to digital pin 5.
4. **Buzzer**: Connected to pin 2 (active-low).
5. **LCD**: Connected via I2C to the ESP32.

## Commands
Users can interact with the system via a Telegram bot using the following commands:
- `/start`: Initialize the bot and display a welcome message.
- `/menu`: Show the list of available commands.
- `/sensor`: Get the current sensor readings (temperature, humidity, gas level, and fire status).
- `/stop_buzzer`: Stop the active buzzer.

## Installation and Setup
1. Clone this repository to your local machine.
2. Install the required libraries in the Arduino IDE:
   - `LiquidCrystal_I2C`
   - `DHT`
   - `WiFi`
   - `WiFiClientSecure`
   - `UniversalTelegramBot`
   - `ArduinoJson`
3. Update the `ssid` and `password` variables with your Wi-Fi credentials.
4. Update the `BOTtoken` and `CHAT_ID` with your Telegram bot token and chat ID.
5. Upload the code to your ESP32 using the Arduino IDE.

## Usage
1. Power up the ESP32 and ensure it connects to the Wi-Fi network.
2. Interact with the Telegram bot using the specified commands.
3. Monitor the LCD for real-time sensor data.
4. Receive alerts in case of dangerous conditions.

## Future Enhancements
- Integrate additional sensors for enhanced monitoring.
- Provide a web interface for more comprehensive control and visualization.
- Implement data logging for historical analysis.
