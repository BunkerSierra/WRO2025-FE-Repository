Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2025.

BOM (electrical and mechanical parts):

Electric parts:
- Arduino UNO rev3 - x1
- Arduino servo shield for Nano and UNO - x1
- RaspberryPi 4 1gb Model B - x1
- RaspberryPi Camera - x1
- Motor Driver IMS-2 Wingxine - x1
- 5v DC Motor - x1
- Servomotor MG90S(9gr) - x1 
- Ultrasonic Sensor HC-SR04P - x3

Power parts:
- 3.7v 9900 mAh 18650 batteries - x4
- DC-DC Buck Converter Module LM2596 - x1

Mechanical parts:
- commercial steering system (Modified) - x1
- Commercial Differential system (Modified) - x1
- Commercial wheels - x4
  
## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction
Ultrasonic Sensors:
The robot's ultrasonic sensors have two purposes. The side ones are programmed for center finding and wall following, and the front one is designed to prevent it from colliding with obstacles. If it detects an obstacle within 20 centimeters of the robot, it stops and reverses (only in the areas where it is allowed to reverse).
In the free lap program, the robot first uses the center finding function before making the first turn. When it turns, it checks which sensor is detecting the shortest distance, and that sensor will follow the wall. From that point on, the robot will make all the necessary turns to complete the free lap. This last function also lets the robot know which direction it will have to turn: clockwise or counterclockwise.
This is the code it uses to calculate the distance in centimeters in the arduino IDE:

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH);
float distance = duration * 0.0343 / 2;
