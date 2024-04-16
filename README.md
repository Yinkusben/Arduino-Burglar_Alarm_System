# Arduino Based Burglar Alarm System

Welcome to the Arduino Based Burglar Alarm System project! This system is designed for a small building (a shop) with four PIR sensors and one Magnetic Reed switch to monitor movement at each side of the building and check if the door is open. It includes a high decibel alarm and various security features.

## Introduction
This project is part of my portfolio for the ALX Software Engineering foundations course. For more information about this project and my other projects, please visit the [landing page](<https://yinkusben.github.io/Arduino-Burglar_Alarm_System).

## About Me
I'm an software engineer with a passion for IoT and embedded systems. Feel free to connect with me on [LinkedIn](<https://www.linkedin.com/in/yinkusben) to learn more about my professional background and interests.

## Overview
This project is an Arduino-based burglar alarm system designed for a small building (a shop) with four PIR sensors and one Magnetic Reed switch. It monitors movement at each side of the building and checks if the door is open, sounding a high decibel alarm upon detecting security-threatening activity. The system includes a 16x2 LCD display and a 4x4 keypad matrix for navigation.

## Features
**A 16x2 LCD display and a 4x4 matrix keypad for display and navigation**
- **Main menu displaying system status (armed or disarmed)**
- **2 levels of security breach:**
  - *First level: non-continuous sound and single SMS to configured phone number*
  - *Second level: continuous sound, SMS, and phone call to configured phone number*
- **Real-Time-clock module for scheduled arming/disarming**
- **GSM module sends SMS and make s Phone calls upon security braech detection**
- **SMS commands for arming/disarming**
- **Time and date settings adjustment**
- **Emergency phone number configuration**
- **Sensor and reed switch monitoring disable option**
- **Adjustable motion detection count before alarm**
- **SIM card presence and network signal level display on LCD**
- **Sensor and reed switch presence test option**
- **False alarm deactivation via keypad or SMS**

## Usage
To use the system, follow these steps:
1. Power on the device.
2. Navigate the menu using the keypad:
   - A: Next
   - B: Back
   - C: Enter
   - D: Delete
   - Keypad digits: Select options or enter settings
3. Configure settings such as:
   - Scheduled arming/disarming times
   - SMS commands
   - Time and date
   - Emergency phone number
   - Sensor and reed switch monitoring
   - Motion detection count
4. Monitor the LCD for system status and network information.
5. Test sensor and reed switch presence if needed.
6. Respond to security breaches as necessary.

## Installation

### Hardware Requirements
- Arduino Nano
- PIR sensors (4)
- Magnetic reed switch
- 16x2 LCD display
- 4x4 matrix keypad
- SIM800L GSM module
- RTC module
- High decibel buzzer
- 2N2222 transistor

### Software Requirements
- Arduino IDE
- Libraries:
  - i2c LCD library
  - Keypad library
  - EEPROM library

Follow these steps to install and set up the Arduino Based Burglar Alarm System:
1. Connect the hardware components according to the circuit diagram.
2. Install the Arduino IDE on your computer.
3. Install the required libraries (i2c LCD library, Keypad library, EEPROM library) in the Arduino IDE.
4. Upload the Arduino sketch to the Arduino Nano.
5. Power on the device and configure the settings as needed.
6. Your burglar alarm system is now ready to use!


## Contributing
Contributions to improve this project are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the [MIT License](LICENSE).
