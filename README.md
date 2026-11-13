# Smart Room Climate and Ventilation Assistant

## Project Overview

The Smart Room Climate and Ventilation Assistant is an ESP32-based IoT project designed to monitor temperature and humidity in a home office environment.

When the measured temperature or humidity exceeds the configured thresholds, the system activates visual and audible alerts and rotates a servo motor to represent opening a ventilation flap.

The project was developed and tested using the Wokwi simulation platform.

## Components Used

- ESP32 Development Board
- DHT22 Temperature and Humidity Sensor
- Servo Motor
- LED
- Buzzer

## Technologies Used

- Embedded C++ 
- ESP32
- Arduino IDE framework
- Wokwi Simulator

## Working Principle

1. The DHT22 sensor measures temperature and humidity.
2. The ESP32 reads the sensor values.
3. The readings are compared with predefined thresholds.
4. If either threshold is exceeded:
   - LED turns ON.
   - Buzzer produces an alert.
   - Servo rotates to represent ventilation activation.
5. When conditions return below the thresholds, the system returns to normal.

## Configured Thresholds

- Temperature: 30°C
- Humidity: 70%

These values are configurable demonstration thresholds.

## Simulation

The complete project was developed and tested using Wokwi with an ESP32.

## Future Improvements

- Integrate an actual ventilation fan.
- Add real-time monitoring through a web dashboard.
- Introduce remote monitoring through Wi-Fi.
- Store historical temperature and humidity readings.

## Author

Ryakala Srija

## Wokwi Simulation

https://wokwi.com/projects/480588354907044865