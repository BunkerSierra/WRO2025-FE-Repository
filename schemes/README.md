Diagramas Electricos
====

En esta sección se presentan los diagramas eléctricos de todos los componentes y una descripción de su funcionamiento. Además, se desglosa el hardware del robot y su conexión con las piezas mecánicas. Todos los modelos y diseños 3D mencionados aquí están disponibles en la carpeta [models](/models).

## Diagrama Electrico General del Vehiculo: 

![DE-S25_bb](DE-S25_bb.jpg)

***Especificaciones:*** La placa **Arduino MEGA** es alimentada directamente desde el puerto de comunicación serial de la computadora **Raspberry Pi 4**. Esta última, a su vez, es alimentada por nuestro regulador de voltaje **LM2596**, configurado a **5.1V** y **3A**. Ajustamos el regulador a 5.1V porque al configurarlo exactamente a 5V, la Raspberry Pi solía presentar problemas de alimentación.


## Diagramas Eléctricos de Cada Componente y Sensor Vehiculo:


***Aclaración:*** Los siguientes diagramas muestran las conexiones de señal de cada sensor y componente eléctrico. **Únicamente** los diagramas de **Potencia** y **Motor con Motor Driver** incluyen las conexiones de alimentación, ya que son indispensables para replicar el robot. Los demás diagramas omiten estas conexiones para permitir flexibilidad a otros equipos, pero pueden consultarse en el **Diagrama Eléctrico General** mostrado arriba.


- **Sensores Ultrasonicos**
  
![IMG-DE_SUS](IMG-DE_SUS.jpg)


- **Acelerometro/Giroscopio GY-521**
  
![IMG-DE_Gyro](IMG-DE_Gyro.jpg)


- **Servo Motor**
  
![IMG-DE_Servo](IMG-DE_Servo.jpg)


- **Human Machine Interface**
  
![IMG-DE_HMI](IMG-DE_HMI.png)


- **Motor 12v - Motor Driver**
  
![IMG-DE_Motor_MDirver](IMG-DE_Motor_MDirver.png)


- **Etapa de Potencia y Raspberry pi 4**
  
![IMG-DE_Potencia](IMG-DE_Potencia.jpg)


Manejo de Movilidad
===
## Motor DC 12v con encoder 
Elegimos este motor principalmente por el **encoder integrado**. Este sensor nos permite conocer la posición del robot, lo que aporta múltiples beneficios a nuestra solución: calcular la cantidad de vueltas, la distancia recorrida, asistir en el estacionamiento en paralelo y, en general, todas las variables relacionadas con la posición.

![IMG-Motor12v](IMG-Motor12v.jpg)

Inicialmente, utilizábamos un motor de un juguete RC que incluía un diferencial. Con ese motor participamos en la etapa regional de Mexicali. Decidimos cambiarlo porque la velocidad variaba demasiado y la falta de un encoder hacía muy difícil mantener la consistencia en los movimientos. Sabemos que es imposible que un robot repita una rutina de manera exacta, pero ese componente lo dificultaba aún más. El cambio a un motor con encoder y un diferencial LEGO nos da un control mucho mayor sobre estas variables. Para lograrlo, diseñamos un soporte que acoplara el motor al diferencial LEGO, el cual pasó por 3 revisiones.

![IMG_Soporte_Motor_Rev1](IMG_Soporte_Motor_Rev1.jpeg)

*Así se veía la primera versión. Permitía pruebas básicas, pero el motor no estaba fijado al soporte, lo que generaba perturbaciones.*

-[Soporte para motor Rev3](/models/S25_Soporte_Motor_y_Transmision_Rev3.STL) 

*En la revisión actual, el motor está firmemente fijado al soporte, eliminando las perturbaciones por movimiento*. Así mismo tuvimos un caso similar con el engrane que se conecta al motor. 

## Movimiento 
Para que el robot avance en línea recta, utilizamos un **girosensor con un controlador PD**. Esto permite que el robot mantenga su rumbo. Como se ha mencionado, es imposible que sea perfecto, pero con este sistema la desviación es mínima, **nunca superando los 2°** desde el punto inicial (considerando 0° como el origen).

![IMG_Offset](IMG_Offset.jpeg)

De igual manera, utilizamos el girosensor para los giros del robot. Al llegar al punto deseado, el robot gira las ruedas y avanza hasta detectar el ángulo objetivo. Una vez alcanzado, detiene los motores y vuelve la dirección a la posición neutral.

![IMG_GiroSensor](IMG_GiroSensor.jpg)

**Actualización 12/09/2025: Sustitución de la Unidad de Medición Inercial (IMU)**

**Motivo:** La IMU anterior (GY-521) presentaba fallos intermitentes de lectura, caracterizados por un bloqueo o saturación de sus valores de salida. Este comportamiento generaba imprecisiones en la determinación de la orientación del vehículo, afectando la confiabilidad de las pruebas.

**Acción:** Se procedió a reemplazar la unidad por un modelo **GY-9250** (que integra los sensores MPU-9250 y BMP280), seleccionado por su mayor estabilidad y confiabilidad reportadas.

**Nota para réplica:** Para fines de replicación del sistema base, el modelo de sensor anterior es funcional. Esta actualización responde a una necesidad específica de robustez y precisión en la operación continua.

![IMG-GY9250](IMG-GY9250.jpg)

Gestión de Potencia y los Sentidos
====

## Energía
El robot utiliza **6 baterías de 3.7V y 9900mAh (18650)**. Están divididas en *4 portabaterías conectados en paralelo** para administrar la corriente de manera eficiente. El voltaje máximo del sistema es de **8.4V**.

Para alimentar nuestra computadora **Raspberry Pi 4**, utilizamos un **regulador de voltaje LM2596 ajustado a 5.1V**. Esto permite que la placa funcione correctamente sin necesidad de conectarla a un tomacorriente. Cabe recalcar que, inicialmente, realizábamos las pruebas para la gestión de obstáculos con la Pi conectada a la pared, lo que nos permitió validar el comportamiento de nuestro código. Sin embargo, era evidente que teníamos que resolver este problema para que el robot fuera completamente autónomo.

![IMG_Baterias_3.7v](IMG_Baterias_3.7v.webp)

## Sensores
Al inicio de la temporada, nuestra propuesta era utilizar **sensores láser VL53L0X**. Pensamos que serían la mejor opción por su largo alcance y precisión, por lo que nuestro primer chasis fue diseñado para ellos. Al realizar pruebas, notamos que sus características nos afectaban: el **rango de visión cónico** hacía que los sensores detectaran el suelo, causando muchas fallas. Además, usar 3 de estos sensores consumía una cantidad excesiva de memoria de nuestro microcontrolador (en ese momento, un Arduino UNO).

![IMG_SensorLaser](IMG_SensorLaser.jpg)

Estos problemas nos llevaron a reemplazarlos por **sensores ultrasónicos HC-SR04**. Con ellos participamos en la regional y siguen en nuestro modelo actual. El cambio fue sencillo gracias a nuestro diseño modular; los soportes para los ultrasónicos que habíamos diseñado para proyectos anteriores usaban el mismo sistema de encastre que los soportes láser en el chasis, haciendo la transición rápida y accesible.

Contamos con **3 sensores ultrasónicos:** 1 al frente y 2 en los costados. Los sensores laterales se usan principalmente para determinar la dirección de giro. Una vez que el robot sale del primer cuadrante, siempre habrá un lado con barrera y otro sin ella. El sensor que detecte la mayor distancia dictará el sentido del giro (horario o antihorario).

El sensor frontal tiene múltiples funciones:

1. En el desafío de "vuelta libre", detecta la distancia al muro antes de girar. Al detectar 50 cm, el robot se detiene y procede a girar.

2. En el desafío de "obstáculos", detecta la proximidad a un obstáculo. Al detectar menos de 15 cm, se detiene y gira en la dirección que indique el color.

![IMG_SU](IMG_SU.webp)

## HMI (Interfaz Hombre-Máquina)
En la tercera planta del vehículo hay un mini protoboard (170p) con **3 LEDs y un botón.** En el chasis también está montado un buzzer pasivo.

**Desafío de Vuelta Libre:** Al presionar el botón de arranque, se enciende un LED y el buzzer ejecuta un sonido, indicando que el código está en ejecución.

**Desafío de Obstáculos:** Dependiendo del caso detectado por la cámara, se encienden diferentes LEDs para proporcionar retroalimentación visual, y el buzzer ejecuta sonidos distintos para cada caso.

**Nota:** El buzzer también genera un sonido cada vez que los sensores ultrasónicos detectan un objeto.

Gestion de obtaculos
===
## Camara
Para el desafío de obstáculos, optamos por utilizar una **Raspberry Pi Camera rev.1.3**. En este apartado se detalla únicamente cómo montamos la cámara en el vehículo y los modelos utilizados. Para la información sobre el algoritmo de detección y la solución para esquivar obstáculos, consulta la carpeta [src.](/src)

Antes de usar la cámara oficial de Raspberry, utilizábamos el modelo **Night Vision Camera for Raspberry Pi - IR-CUT 5MP**. Como su nombre indica, es una cámara de visión nocturna. Al probarla con OpenCV, la imagen tenía un filtro rojo que impedía que nuestro algoritmo de detección de colores funcionara correctamente. Los valores de color variaban enormemente dependiendo del entorno, requiriendo condiciones de luz muy específicas, lo que era un problema grave.

![IMG_Camara_VN](IMG_Camara_VN.webp)

La solución fue cambiar a la cámara estándar de Raspberry Pi. Este cambio resolvió el problema inmediatamente, permitiendo que el robot funcione de manera confiable en distintos entornos. Con esto resuelto, procedimos a diseñar e implementar un soporte personalizado para la cámara, tomando ideas de varios diseños para nuestra solución.

![IMG_Camara_RB1.3](IMG_Camara_RB1.3.webp)
