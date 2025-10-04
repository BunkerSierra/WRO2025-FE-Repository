Models 
===
This section contains the 3D designs and models of the robot's mechanical parts, along with an explanation and justification for their use. For information about the parts and their relationship with the electrical components, please refer to the schemes folder [schemes](/schemes/README.md).

Mechanical Parts
===
One key point we would like to emphasize is that the majority of our mechanical parts were manufactured using laser cutting. Another small section of parts, primarily for the steering system, were 3D-printed.

## Vehicle Chasis
The vehicle consists of a chassis and two additional levels (floors), each housing different robot components:

- **Chassis:** Robot Motion Management
  - Steering system, DC drive motor, Motor driver, and a Mini Protoboard.
  - [Chassis View](/models/S25_Chasis_Rev12.STL).
- **Level 1:** Robot Controllers
  - Arduino Mega, Raspberry Pi y RaspBerry pi Camara rev 1.3
  - [Level 1 View](/models/S25_BS_Rev6.STL).
- **Level 2:** Electrical Components
  - Mini Protoboard with HMI and Gyro sensor.
  - [Level 2 View](/models/S25_Piso3_Rev1.STL).
 
As you may notice, the filenames for all models include their revision number. For example, the chassis is on its 12th revision. This reflects every change we have needed to make throughout the season. It is the part that has undergone the most changes.

As mentioned in other sections of the repository, our robot looked very different during the regional stage compared to its current form for the national stage. This is the main reason why this particular part has been modified so extensively. It was from **Rev8** onwards that it began to take on its current appearance.

**Update 14/09/2025**

**1. Chassis and Power System Modification**

**Motivation:** During performance testing for the obstacle challenge, we observed excessive energy consumption from the Raspberry Pi module. This was causing a rapid voltage drop in the batteries (~0.08V per complete run), which compromised the robot's operational autonomy to successfully complete multiple attempts or competition rounds.

**Implemented Solution:** To resolve this energy bottleneck, we expanded the power system by integrating a fourth battery holder, connected in parallel with the existing ones. This configuration:

**Increases the total capacity (Ah)** of the battery bank.

**Maintains the nominal operating voltage** for all components.

**Provides greater autonomy** by distributing the current demand across more power sources.

**Additional Changes:** As part of the chassis reconfiguration, we re-optimized the placement of the voltage regulator and the protoboard to improve accessibility, aesthetics, and cable management.

- [S25_Chasis_Rev14](/models/S25_Chasis_Rev14.STL).

To keep the battery holders securely in place, we designed another component (there are two of these in the robot) capable of holding two battery holders simultaneously. You can view the part here:

- [SB_DrakoR_Rev2](/models/SB_DrakoR_Rev2.STL).

## Mobility Management
**Motor Mount**

As this mechanical part is related to an electrical component, its explanation can be found in the [schemes](/schemes/README.md) folder.

**Motor Axle Support**

The output shaft of our motor couples to LEGO axles that are connected directly to the wheels. During initial testing, we noticed that these axles were bending. This created an undesired additional force on the motor's Z-axis and caused inconsistent performance in each test run.

As a solution, we designed and implemented a custom support for these axles. Once installed, the axles remain perfectly aligned at a 180° angle, eliminating bending and ensuring uniform and predictable behavior.
- [Motor Axle support](/models/S25_Soporte_Eje_Motor_Rev1.STL).

**24-Tooth Spur Gear**

Initially, we used a standard 24-tooth LEGO Spur gear, drilling out its center to fit the motor's main shaft. This allowed us to validate the behavior of the differential system.

However, this provisional solution had two critical problems: the hole was quickly deformed by wear and tear, and it generated considerable backlash. To resolve this, we designed our own gear, maintaining the standard LEGO dimensions but with the exact inner diameter for our shaft. This ensured a perfect fit and eliminated the backlash.

- **Old Gear:**

  - ![IMG_Spur24D_Lego](IMG_Spur24D_Lego.jpeg)


- **Proposed Gear by the Team:**

  - [New Custom Gear](/models/S25_Spur_24D_Rev3.STL)


**Steering System** 

Our steering system operates through a **linkage mechanism** connected to the **steering knuckles**. At the center of one of these links, a custom-made component is directly attached to an **MG90S servo motor**, allowing us to position the steering mechanism precisely at the specific angles required by our navigation algorithm.

The links were manufactured from **MDF** due to its rigidity and low weight, while the knuckles and connectors were 3D-printed to achieve complex geometries and reduced weight.

![IMG_Direccion_V1](IMG_Direccion_V1.jpeg)
![IMG_Direccion_V2](IMG_Direccion_V2.jpeg)

- **Steering System Components:**
  - [Servo to Beam 1 Connector](/models/S25_Conexion_Servo-enlace_Rev2.STL).
  - [Beam 1](/models/S25_Enlace_Direccion_Rev5.STL).
  - [Beam 2](/models/S25_Soporte_Servo_Rev4.STL).
  - [Spacers](/models/S25_Rondana_Direccion_Rev1.STL).
  - [Steering Knuckles](/models/S25_Mangueta_Rev1.STL).

The last component (steering knuckles) was printed in two versions: one with the original design and another mirrored version.

**Wheels**

We use **62.4mm** LEGO wheels due to our positive experience with them in previous Robomission competitions. We trust their excellent **grip** and the **low rolling resistance** they generate, which is crucial for the robot's energy efficiency and traction.

![IMG_Llantas_62.4mm_Lego](IMG_Llantas_62.4mm_Lego.webp)


## Obstacle Management

**Camera Mount**

The vision system is composed of several custom parts:

  - [Post Mount](/models/S25_Soporte_Poste_Camara_Rev1.STL).
  - [Post](/models/S25_Poste_Camara_Rev1.STL).
  - [Camera Mount](/models/S25_Soporte_Camara_Rev1.STL).
  - [70-Degree Joint](/models/S25_Union_70_grados_Camara_Rev1.STL).

The **height** and **tilt angle** of the camera are critical for our algorithm. The configuration must allow the robot to detect obstacles within a specific quadrant of the track.

- A **90°** (vertical) tilt did not allow for early detection.

- An initial **45°** tilt pointed the camera too far down, detecting obstacles too late.

- After a process of **trial and error**, we determined that a **70°** angle was optimal for our use case, as it provides the necessary field of view for timely and reliable detection.
  

**Update 07/09/2025**

We changed the camera mount angle to 63° and raised the mount height by 1/8 inch. Previously, with the mentioned specifications, the robot had a very low margin of error for positioning itself in front of obstacles and failed when detecting the position and color of the obstacles.

**Camera Angle and Height Optimization**

To improve reliability in detecting obstacle position and color, we adjusted the configuration:

- **Tilt Angle:** Changed from **70°** to **63°**.
  
[S25_Union63_grados_Poste-Soporte_CamaraRev2](/models/S25_Union63_grados_Poste-Soporte_CamaraRev2.STL).

- **Mount Height:** Increased by **1/8 inch**.
  
[S25_Soporte_CamaraRev2.STL](/models/S25_Soporte_CamaraRev2.STL).


The previous configuration, while functional, provided a **very low margin of error** for the robot to position itself correctly in front of obstacles. These fine adjustments significantly increased the success rate of detection and positioning.
