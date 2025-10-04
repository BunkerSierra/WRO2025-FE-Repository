Software Control
====

This section contains the software that operates the electrical components along with the vehicle's mechanical parts. The electrical components will be mentioned in a general manner in this section. For more detailed information about the components, please refer to the following folders:

- [Models](/models).
- [Schemes](/schemes).

## Position Control

**Encoder**

To determine how much the robot has moved, we use the encoder incorporated into our motor. Specifically, it is a HALL encoder: a device that uses **Hall** effect sensors to detect rotational movement and convert it into an electrical signal indicating position or speed.

**What is the** ***Hall effect?*** The Hall effect is the appearance of a potential difference (or electric field) transverse to an electrical conductor when an electric current flows through it and, simultaneously, a magnetic field is applied perpendicular to the direction of the current.

We implemented PID control software to make the robot advance the specific number of pulses we command. With the PID control, we ensure the robot does not fall significantly short of or exceed the target pulse count, thus achieving greater consistency in our vehicle's test runs. So far, we have managed to maintain the error within a range of ±4 pulses. This software is incorporated into both the Free Turn and the Obstacles challenges.

- [CTRL_POS](/src/CTRL_POS.ino).


**Gyro Sensor**

The use of this sensor is fundamental for our vehicle's operation. It has only two objectives, but they are very important:

1. Moving in a straight line **(Both challenges)**.
2. Make Turns.

**1. Straight-Line Movement:** To ensure the robot follows a trajectory without significant deviation, we use a PD control system to maintain the robot at the 0° angle of the gyroscope's Z-axis. We use a GY9250 Accelerometer/Gyroscope. To maintain the same angle, the control system adjusts the steering using the servo motor. This means that if the robot deviates, the steering system turns in the opposite direction to the deviation, allowing the robot to stay centered. As expected, it doesn't always stay perfectly parallel to the trajectory; over very long distances, there is a deviation of no more than 2 degrees, but it remains within our specified tolerances.

**2. Making Turns:** All turns the robot makes on the track are based on the gyro sensor. It's important to clarify that for making turns, the robot's steering moves to the maximum possible position (Left or Right). We do not adjust the steering to intermediate positions for turns, as this would introduce many more variables to consider. Once the steering is in position for the turn, the vehicle moves forward until it reaches the target angle indicated by the gyro sensor. When it stops, the steering returns to the center position, and the robot continues with its routine.


## Sensores Ultrasonicos

**Front Sensor**

As mentioned in other sections of the repository, our robot is equipped with 3 ultrasonic sensors: one on the front and two on the sides (one per side). The front sensor has two main functions:

  1. To detect the distance between the robot and the track barriers **(Open Challenge).**
  2. To obtain the distance between the robot and the obstacles **(Obstacle Challenge).**

1. Open & Obstacle Challenge Barrier Detection: In both the Free Turn and Obstacles challenges, the robot uses the front ultrasonic sensor to detect when it is close to the barrier in front of it. When the distance reaches ≤ 64 cm, the vehicle stops and turns in the direction indicated by the side sensors. This allows us to maintain greater consistency when executing turns in both challenges.
   
2. Obstacle Challenge Proximity Sensing: In the Obstacle challenge, when the robot positions itself in front of an obstacle, the sensor detects the distance between the obstacle and the vehicle. This allows the robot to know its proximity to the obstacle and determine how wide or tight the turn needs to be.

he code for using the ultrasonic sensors is located in the [funciones](/src/S25_Obstaculos_29_08_2025/Funciones.ino) file. This file contains most of the functions we use in our main code.

**Side Sensors**

The side sensors serve several objectives in our vehicle, which are as follows:

1. Determine the direction of rotation (Clockwise/Counter-clockwise).
2. Wall following.
3. Detect the inner barriers.
4. Detect the parking boundaries.

Previously, the sensors shared the same port for the **Trigger** pin using a Y-cable. Initially, we did this because our microcontroller was an Arduino UNO, which saved ports, and we thought it was a good idea as it also simplified the code. However, due to our vehicle's needs and the additional sensors we integrated over time, the Arduino UNO had insufficient ports, forcing us to upgrade to an Arduino MEGA. Despite this change, we continued with the shared trigger configuration for the side sensors. Over time, we noticed the sensors exhibited erratic behavior or did not always return accurate distances. For this reason, leveraging the abundance of digital ports on the new microcontroller, we modified the setup so that each sensor now has its own dedicated trigger port.

The objectives of the side sensors are explained below:

1. **Turn Direction:** In both challenges, when the robot makes its first turn to head to another quadrant, we call the *twoSUS* function to get the distance detected by both sensors. Depending on which sensor detected the greater distance, we determine the turn direction for the run: if the right sensor had the greater distance, the direction is clockwise; if the left sensor had the greater distance, it is counter-clockwise.
   
2. **Wall Following:** In the Obstacle challenge, we use a PD follower to track the outer barriers in cases where there are one or two green objects in the quadrant (the development of the obstacle avoidance algorithm will be discussed later). After completing the quadrant with obstacles, the robot positions itself to detect the obstacles in the next obstacle quadrant.

3. **Inner Barrier Detection:** In cases involving at least one red object, the robot uses the side sensor facing the inner barriers to align with them. This provides greater control over the robot's position after avoiding the red obstacle. We previously also used wall following for scenarios involving red objects, but since the distance traveled was very short, the robot would end the following routine in inconsistent positions, making it very difficult to position itself for the next quadrant or obstacle.

4. **Parking Boundary Detection:** The name of this objective is self-explanatory. When the robot completes the three laps, we use one of the side sensors (depending on the turn direction) to detect one of the parking boundaries to initiate the parking routine.

   
## Obstacle Management 

**Algorithm**

The category rules mention 36 possible obstacle position cases. To solve this challenge, our team first discussed the best approach, as it's crucial to correctly define the problem before programming. After several hours of discussion, we arrived at the following solution: the position cases can be simplified to just 4 core scenarios:

- Red
- Green
- Green - Red
- Red - Green

Regardless of their specific location within the quadrant, all cases reduce to these 4 configurations. Therefore, our solution was to program routines for these 4 cases. After avoiding the obstacles in one quadrant, the robot positions itself to detect the obstacles in the next quadrant. This process repeats in a loop until the 3 laps are completed.

**Object and Color Detection Program**

Our camera program divides the screen's view into zones and highlights the contour of the obstacles, ignoring contours smaller than the area covered by the actual obstacles. It changes the value of a variable depending on the color of the obstacle detected in front of it and selects the case based on the color and position of the objects. To determine the position of the obstacles, we use the camera's pixels on the Y-axis; the case is determined by the pixel location and the color of the object's contour.

Since the robot uses both a Raspberry Pi and an Arduino, the camera sends these values to the Arduino via the serial port by printing the value and transmitting it. The Arduino then performs an action based on the received value. To provide a simpler visual confirmation of the detected case, the robot has 4 LEDs, and one lights up for each specific case detected. As an additional feedback mechanism, it also generates different sound frequencies depending on the case.

