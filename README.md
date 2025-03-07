# Blynk Soil Moisture Monitoring System

This project uses an ESP32 with a DHT11 sensor, an RTC module, and a soil moisture sensor to monitor environmental conditions and send data to Blynk.

## Components Used:
- ESP32
- DHT11 Temperature & Humidity Sensor
- DS3231 RTC Module
- Soil Moisture Sensor
- Blynk IoT Platform

## Setup Instructions:
1. Clone this repository.
2. Install required libraries:
   - `DHT.h`
   - `BlynkSimpleEsp32.h`
   - `RTClib.h`
3. Enter your WiFi credentials in the `ssid` and `pass` variables.
4. Get your Blynk authentication token and replace `"YOUR_BLYNK_AUTH_TOKEN"`.
5. Upload the code to your ESP32 using Arduino IDE or PlatformIO.
