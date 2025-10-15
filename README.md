# Voice-Controlled Exoskeleton with ML and IoT Integration

## Overview
This project presents a **voice-controlled wearable exoskeleton prototype** designed to assist limb movement using **Arduino-based control**, **IoT communication**, and a **prototype machine learning-enhanced interface**.  
The system integrates **voice command recognition**, **servo-driven actuation**, and **Flask-based local server communication** to enable responsive motion assistance.  
Developed as a **pair project during the second year of the Biomedical Engineering program**, this prototype explores the intersection of assistive robotics, embedded systems, and IoT-driven biomedical devices.

## Project Objectives
- Design a functional **wearable prototype** capable of executing motion commands via voice input.  
- Integrate **Arduino Uno** and **ESP8266 Wi-Fi module** for control and data transmission.  
- Use a **local Flask server** to process commands and manage communication between the ML model and the device.  
- Prototype a modular system architecture for future expansion into gesture control and closed-loop feedback.  

## System Architecture
The system consists of three primary modules:
1. **Hardware Layer:** Arduino Uno controls servo motors and processes signals from the ESP8266 module.  
2. **Software Layer:** A Flask-based local server runs on a PC, handling voice recognition, ML model inference, and command routing.  
3. **Communication Layer:** The ESP8266 manages bidirectional data exchange between the hardware and the server.

## Hardware & Tools
- Arduino Uno  
- ESP8266 Wi-Fi module  
- Servo motors (joint actuation)  
- Ultrasonic sensors (for distance monitoring)  
- Local Flask server (Python-based)  
- Python (ML pipeline & server logic)  
- Google Assistant + IFTTT voice trigger integration  

## Key Features
- **Voice-controlled actuation:** Converts voice commands into real-time motor responses.  
- **IoT integration:** Wireless command communication between local server and hardware.  
- **Modular ML pipeline:** Designed for future expansion into predictive motion and gesture-based control.  
- **Local data handling:** Uses Flask for command routing without requiring cloud dependency.  

## Repository Contents
/src     → Source code for Arduino, ESP8266, and Flask server  
/docs    → University project report and supporting documentation  
/media   → Presentation + prototype demonstration video  

## Demonstration Media
The `media/` folder includes:
- A **presentation video** explaining system design, workflow, and implementation.  
- A **prototype demonstration video** showing real-time voice-controlled limb movement and IoT communication in action.

## Acknowledgment
Developed as part of a **university module project** in the **Biomedical Engineering program (Year 2)**.  
Collaboratively completed by a two-member team focusing on hardware–software integration for assistive technologies.
All materials shared here have been approved for academic demonstration purposes.

## Future Work
- Implement **sensor-based feedback loops** for movement accuracy and safety.
- Integrate a **gyroscope** for motion stabilization and more precise actuation. 
- Develop **gesture-based ML control** and **cloud integration** for remote operation.  
- Explore **3D-printed wearable frame designs** for ergonomic improvements.  
