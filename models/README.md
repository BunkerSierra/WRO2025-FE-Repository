Modelos 
===
En este apartado se encuentran los diseños y modelos 3d de las partes mecanicas que componen el robot junto con la explicacion y justificacíon de su uso, para informacíon acerca de las piezas y su relación con los componentes electricos revisar por favor carpeta [schemes](/schemes/README.md).

Partes Mecánicas
===
Un dato que consideramos recalcar es que la mayoria de las partes mecanicas las mandamos a hacer en corte laser, y otra pequeña seccion de piezas, en su mayoria del sistema de direccíon, las mandamos a imprimir en 3D.

## Chasis del Vehiculo
El vehiculo consta de su chasis y y otros 2 pisos, cada uno de los pisos cuenta con diferentes componentes del robot:
- **Chasis** Gesiton de movimiento del robot
  - Sistema de direccion, Motor de movimiemto, Driver para motor y un Mini Protoboard.
  - [Vista de Chasis](/models/S25_Chasis_Rev12.STL).
- **Piso 1** Controladores del Robot
  - Arduino Mega, Raspberry Pi y camara
  - [Vista de Piso 1](/models/S25_BS_Rev6.STL).
- **Piso 2** Componentes Electricos
  - Mini Protoboard con HMI y Girosensor.
  - [Vista de Piso 2](/models/S25_Piso3_Rev1.STL).
 
Como se puede notar, en los nombres de archivo de todos los modelos se menciona la revisíon de cada parte mecanica, por ejemplo el chasis lleva 12 revisones, esto por cada uno de los cambios que hemos necesitado durante la temporada. Es la parte que más ha cambiado, en otras secciones del repositorio hemos mencionado que nuestro robot era muy distinto durante la etapa regional a como se ve actualmente para la etapa nacional y ese el principal motivo por el cual la pieza ha cambiado tanto, a partir de la Rev8, es cuando comienza a verse como es actualmente.

## Gestion de Movilidad
**Soprte para Motor**

Esta parte mecanica al estar relacionada a un componente electrico, su explicacíon se encuentra en [schemes](/schemes/README.md)

**Soprte para Ejes del Motor**

El eje de salida de nuestro motor son axles de lego que estan conectados a nuestras llantas, por ende tuvimos que diseñar un soporte para estos ejes por que sin ellos los ejes se pandeaban y eso generaba una fuerza extra en el eje Z para el motor y cada prueba que haciamos se comportaba de manera diferente. Una vez que los soportes se implementaron en el robot los ejes de mantenian en un angulo de 180°
- [Soporte para ejes](/models/S25_Soporte_Eje_Motor_Rev1.STL).

**Engrane Spur 24D**

Inicialmente hicimos pruebas con un engrane Spur de 24 dientes de lego, taladramos el centro del engrane para que entrara en el eje principal del motor e inicialmente eso nos ayudo par ver como se comportaría el sistema diferencial. Sin embargo, no podíamos quedarnos con eso ya que con el desgate generado por el uso, el agujero driver se terminaba deformando y tenía un backlash bastante considerable. Usando la misma medida de lego realizamos un diseño de un engrane igual, pero con las medidas de nuestro eje principal.

- Engrane Viejo:

![IMG_Spur24D_Lego](IMG_Spur24D_Lego.jpeg)

- [Engrane propuesto por el equipo](/models/S25_Spur_24D_Rev3.STL)


**Dirección** 

Nuestra dirección funciona a partir de enlances que están conectados a manguetas y en el centro de una de las vigas de los enlaces hay una pieza que se conecta a un servomotor MG90S, el servomotor nos permite llevar la dirección a los ángulos que nosotros necesitamos dentro de nuestro algoritmo. Estos son diseños realizados por el equipo y para fabricarlos utilizamos MDF para los enlaces e impresión 3D para las manguetas.
![IMG_Direccion_V1](IMG_Direccion_V1.jpeg)
![IMG_Direccion_V2](IMG_Direccion_V2.jpeg)

- **Piezas del sistema de direccíon:**
  - [Conector del Servo a Viga 1](/models/S25_Conexion_Servo-enlace_Rev2.STL).
  - [Viga 1](/models/S25_Enlace_Direccion_Rev5.STL).
  - [Viga 2](/models/S25_Soporte_Servo_Rev4.STL).
  - [Espaciadores](/models/S25_Rondana_Direccion_Rev1.STL).
  - [Manguetas](/models/S25_Mangueta_Rev1.STL).
 Este ultimo, fue impreso de 2 maneras, uno con el diseño original y otro espejeado.

Utilizamos llantas de lego, en especifico el modelo que tiene la medida 62.4mm ya que las hemos utilizado en competencias anteriores de la categoría robomission, confiamos mucho en ellas tanto por su agarre al suelo y poca fricción que generan.
![IMG_Llantas_62.4mm_Lego](IMG_Llantas_62.4mm_Lego.webp)


## Gestion de Obstaculos
Para realizar el soporte para nuestra camara lo separamos en las siguientes partes:
  - [Soporte para Poste](/models/S25_Soporte_Poste_Camara_Rev1.STL).
  - [Poste](/models/S25_Poste_Camara_Rev1.STL).
  - [Soporte para camara](/models/S25_Soporte_Camara_Rev1.STL).
  - [Union de 70 grados](/models/S25_Union_70_grados_Camara_Rev1.STL).

La altura de nuestra camara es la necesaria para que el robot alcance a detectar los objetos en la pista, en nuestro caso por el algoritmo que diseñamos solamente es necesario que detecte los obstaculos que puede haber en 1 cuadrante de la pista. Ademas la union del soporte de la camara al poste tiene una inclinacíon de 70°, ya que si lo dejabamos en 90°(ortogonalmente), no alcanzaba a detectar los objetos necesarios. Inicialmente propusimos un angulo de 45° de inclinacíon pero la imagen de la camara volteaba a ver unicamente el suelo y eso hacia que detectara los obstaculos muy tarde,  por esa razon cambiamos el grado de inclinacion a 70°. Nos gustaria aclarar que esto fue hecho a partir de prueba y error. no utilizamos un calculo para encontar el grado de inclinacion correcto.
