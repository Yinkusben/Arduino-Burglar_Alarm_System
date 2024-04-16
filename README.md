# Arduino Based Burglar Alarm System

## Overview
This project is an Arduino-based burglar alarm system designed for a small building (a shop) with four PIR sensors and one Magnetic Reed switch. It monitors movement at each side of the building and checks if the door is open, sounding a high decibel alarm upon detecting security-threatening activity. The system includes a 16x2 LCD display and a 4x4 keypad matrix for navigation.

## Features
- **Main menu displaying system status (armed or disarmed)**
- **2 levels of security breach:**
  - *First level: non-continuous sound and single SMS to configured phone number*
  - *Second level: continuous sound, SMS, and phone call to configured phone number*
- **Real-Time-clock module for scheduled arming/disarming**
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
1. Connect the Arduino to the PIR sensors and Magnetic Reed switch according to the circuit diagram.
2. Upload the Arduino sketch to the board.
3. Power on the device and configure settings as needed.

## Contributing
Contributions to improve this project are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the [MIT License](LICENSE).
