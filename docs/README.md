# Arduino based Burglar Alarm System with SMS and Call Notification

![Cover Image](/Pictures/Image_1.jpg)

## Introduction
This project is part of my portfolio for the ALX Software Engineering foundations course. This project was inspired by a friend who had eperienced security issues around his shop, He gave me a call and said he needed a device that would notify him of security-threatning actvity at his shop at his closing hours (majorly at night). For more information about this project and my other projects, please visit my GitHub profile.

### Navigation
- [Overview](#overview)
- [Features](#features)
- [Demonstration Video](https://youtu.be/kV54afeCj6w?si=KlQmew_SsVj5R9Ii)

## Overview
This project is an Arduino-based burglar alarm system designed for a small building (a shop) with four PIR sensors and one Magnetic Reed switch. The system employs algorithm for threat detection detection The PIR sensor are set to single trigger mode, a flag is raised only if any of the PIR sensor detects movement about 5 times within 30 sec (This is of course not perfect and would definitely respond to a non malicious movement, but it is meant to be Armed only at night when the area is usually not busy at all) it also checks if the door is open and sounds a high decibel alarm upon detecting security-threatening activity. The system includes a 16x2 LCD display and a 4x4 keypad matrix for display and navigation respectively.

## Features
1. **Motion Detection**: 
   - ![Motion Detection Image](/Pictures/PIR-detection.png)
   - The system uses 4 PIR sensors to detect motion arounf the 4 walls of a building.
2. **Door unlock detection**: 
   - ![Door unlock detection image](/Pictures/Reed_switch.jpg)
   - The sysem uses a magnetic reed switch to detect unauthorized access to locked doors
3. **Emergency Siren**:
   - ![Emergencu Siren Notification](/Pictures/buzzer.jpg)
   - Upon detecting intruder activity or a security breach,the crazy sound from the high decibel buzzer goes off, The sould could scare away the intruder and it is more than loud enough to call the public's attention.
4. **Customized Alarm Arming Time**:
   - ![Customized alarm Aring time](link-to-call-notification-image.jpg)
   - The device can be configured to be Armed at specific times of the day (e.g During times when you are not around)
5. **SMS Notification**:
   - ![SMS Notification Image](link-to-sms-notification-image.jpg)
   - When motion is detected, the system sends an SMS notification to the user's phone.
6. **Call Notification**:
   - ![Call Notification Image](link-to-call-notification-image.jpg)
   - In addition to SMS, the system can also make a call to alert the user of the intrusion.

## About
This project was inspired by my dear friend(Benjamnin) experience with security issues at his workshop. On several occasions, the neighboring shops had experinced break-ins at their shops and thft of their goods and belongings during the night periods, Benjamin gave me a call and said he need somethng that can notify him of unusal activity around his shop and probably makes an alarmingsound that calls the publi'sattention.
Soi thought od building somthing that can provide hima real-time informaiton of security breaches at the four sides of his shop and at his door entrance. I wanted to create a solution that not only detects intrusions but also alerts the user immediately through SMS and call notifications.

This project is part of my portfolio for [ALX Software Engineering], where I am currently studying software engineering. It has been a challenging but rewarding experience, and I'm excited to share my work with others.

### Links
- [GitHub Repository](https://github.com/Yinkusben/Arduino-Burglar_Alarm_System)
- [LinkedIn](https://www.linkedin.com/in/yinkusben)
- [GitHub](https://github.com/Yinkusben)
- [X (Twitter)](https://x.com/simpletronics)

