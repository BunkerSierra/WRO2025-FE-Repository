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


**Dirección** 

Nuestro sistema de dirección funciona mediante un mecanismo de **enlaces** conectados a las **manguetas**. En el centro de uno de estos enlaces, una pieza personalizada se conecta directamente a un servomotor **MG90S**, que nos permite posicionar la dirección con precisión en los ángulos específicos que requiere nuestro algoritmo de navegación.

Los enlaces fueron fabricados en **MDF** por su rigidez y bajo peso, mientras que las manguetas y conectores se imprimieron en 3D para lograr geometrías complejas y un peso reducido.

![IMG_Direccion_V1](IMG_Direccion_V1.jpeg)
![IMG_Direccion_V2](IMG_Direccion_V2.jpeg)

- **Piezas del sistema de dirección:**
  - [Conector del Servo a Viga 1](/models/S25_Conexion_Servo-enlace_Rev2.STL).
  - [Viga 1](/models/S25_Enlace_Direccion_Rev5.STL).
  - [Viga 2](/models/S25_Soporte_Servo_Rev4.STL).
  - [Espaciadores](/models/S25_Rondana_Direccion_Rev1.STL).
  - [Manguetas](/models/S25_Mangueta_Rev1.STL).
 Este ultimo, fue impreso de 2 maneras, uno con el diseño original y otro espejeado.


**Llantas**

Utilizamos llantas LEGO del modelo **62.4mm** debido a nuestra experiencia positiva con ellas en competencias previas de Robomission. Confiamos en su excelente **agarre** y la **baja fricción** que generan, lo cual es crucial para la eficiencia energética y la tracción del robot.
![IMG_Llantas_62.4mm_Lego](IMG_Llantas_62.4mm_Lego.webp)


## Gestion de Obstaculos

**Soporte para Cámara**

El sistema de visión se compone de varias partes personalizadas:


  - [Soporte para Poste](/models/S25_Soporte_Poste_Camara_Rev1.STL).
  - [Poste](/models/S25_Poste_Camara_Rev1.STL).
  - [Soporte para camara](/models/S25_Soporte_Camara_Rev1.STL).
  - [Union de 70 grados](/models/S25_Union_70_grados_Camara_Rev1.STL).

La **altura** y la **inclinación** de la cámara son críticas para nuestro algoritmo. La configuración debe permitir al robot detectar obstáculos dentro de un cuadrante específico de la pista.

- Una inclinación de **90°** (vertical) no permitía una detección temprana.

- Una inclinación inicial de **45°** apuntaba la cámara demasiado hacia el suelo, detectando los obstáculos demasiado tarde.

- Tras un proceso de **prueba y error**, determinamos que un ángulo de **70°** era el óptimo para nuestro caso de uso, ya que proporciona el campo de visión necesario para una detección oportuna y confiable.
  

**Actualización 07/09/2025**

Cambiamos el angulo del soporte para la camara a 63° y subimos la altura del soprte 1/8", anteriormente con las especificaciones que mencionabamos el robot tenia un margen de error muy bajo para posicionarce frente a los obstaculos y fallaba al momento de detectar la posicion y color de los obstaculos.

**Optimización del Ángulo y Altura de la Cámara**

Para mejorar la confiabilidad en la detección de la posición y el color de los obstáculos, ajustamos la configuración:

- **Ángulo de inclinación:** Cambiado de **70°** a **63°**.
  
[S25_Union63_grados_Poste-Soporte_CamaraRev2](/models/S25_Union63_grados_Poste-Soporte_CamaraRev2.STL).

- **Altura del soporte:** Aumentada en **1/8 de pulgada**.
  
[S25_Soporte_CamaraRev2.STL](/models/S25_Soporte_CamaraRev2.STL).


La configuración anterior, aunque funcional, dejaba un **margen de error muy bajo** para que el robot se posicionara correctamente frente a los obstáculos. Estos ajustes finos incrementaron significativamente la tasa de éxito de la detección y el posicionamiento.
