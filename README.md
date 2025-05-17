# Collision-Detection-System-CS410-SP2025

# Table of Contents
Feel free to use this to jump around this readme

[Team Members](#Team-Members)

[Problem](#Problem)

[Solution](#Solution)

[Documentation](#Documentation)

[Code](#Code)

[Website](#Website)

[Board](#Board)

[What We Learned](#What-We-Learned)

# Team-Members

Kaif Khalifa - Project Manager and Designer

Emry Hankins - Full-Stack and Systems Integration

Fardin Hasan - Backend & MQTT Integration 

Gustavo Aguiar - Embedded Systems and Sensor Integration

# Problem

Autonomous vehicles operate in unpredictable, crowded environments, surrounded by pedestrians, other vehicles, and fixed obsticles. Even minor collisions can lead to costly repairs if insurance won't cover it or safety hazards. 

The challenge than becomes: How can we detect collisions the moment that they happen? How can we alert the users? How can we prove it?

# Solution

How our solution works:

1. User signs up on the web-based app 
2. Sensors (Collision, distance, pressure) detect impact and proximity
3. ESP32 processes sensor data and send it to the MQTT server
4. Backend sends a mobile alert to the user's cell phone

Core Features:

- Real-time detection
- Low-latency MQTT communication 
- Mobile alerts
- Data logging

# Documentation

[Link to our Documentation](https://docs.google.com/document/d/1Gpf9F6l65aNqtSdLUW4sN3zz2r2ugYwhTedpowMC90c/edit?tab=t.c7bkemifnjyc)

# Code

[Here is the Web App code](https://github.com/kaifkhalifa/Collision-Detection-System-CS410-SP2025/tree/CDSCS8basicappdev)

[Here is the hardware and send warning code](https://github.com/kaifkhalifa/Collision-Detection-System-CS410-SP2025/tree/CDSCS-Hardware-and-Algorithm)

[Here is the Render hosting code](https://github.com/kaifkhalifa/Collision-Detection-System-CS410-SP2025/tree/render-hosting)

# Website

Clicking on [this link](https://collision-detection-system-cs410-sp2025.onrender.com/signup) will send you to the website you sign up for to start recieving the messages.

# Board

[Link to our Jira Board](https://umb-team-jmbz7ice.atlassian.net/jira/software/projects/CDSCS/boards/2)

# What-We-Learned

As a result of working on this project, we learned:

- Integration of multiple sensors into ESP32
- MQTT Communication
- Mobile latency and mobile sync issues
- Cross-functional collaboration
- - Good communication
- - Weekly meetings
- - Open collaboration
- Debugged complex systems under pressure
- Build a scalable and real-world applicable solution
