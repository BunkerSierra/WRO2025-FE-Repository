Software Control
====

En este apartado se encuentra el software que hace funcionar los componentes electricos junto a las partes mecanicas del vehiculo. Sera hara mención de los componentes eléctricos de manera general en este apartado, para más información acerca de los compoentes revisar las siguientes carpetas:

- [Models](/models).
- [Schemes](/schemes).

## Control de Posición

**Encoder**

Para saber cuanto se ha movido el robot, utilizamos el encoder que se encuentra incorporado en nuestro motor. En concreto es un Encoder tipo **HALL**: dispositivo que utiliza sensores de efecto Hall para detectar el movimiento rotatorio y convertirlo en una señal eléctrica que indica posición o velocidad. 
¿Que es el ***efecto hall***? El efecto Hall es la aparición de una diferencia de potencial (o campo eléctrico) transversal a un conductor cuando una corriente eléctrica lo atraviesa y, al mismo tiempo, se le aplica un campo magnético perpendicular a la dirección de la corriente.

Realizamos un software de control PID para que el robot avance la cantidad de pulsos que le indicamos, con el control PID nos aseguramos de que el robot no le falte o supere una gran cantidad de pulsos y asi obtener más constancia en las pruebas que realizamos con nuestro vehiculo. Hasta el momento hemos logrado mantenerlo en un rango de ±4 pulsos. El software esta incorporado tanto en el desafio de vuelta libre tanto en el de obstaculos.

- [CTRL_POS](/src/CTRL_POS.ino).

**Girosensor**



## Sensores Ultrasonicos

**Sensor Frontal**

Como hemos mencionado en otros apartados del repositorio nuestro robot cuanta con 3 sensores ultrasonicos, uno en la parte frontal y 2 en los laterales (1 por lado), El sensor frontal tiene 2 funciones en nuestro vehiculo:

  1. Detectar la distancia entre el robot y las barreras de la pista **(Desafio Abierto)**
  2. Obtener la distancia entre el robot y los obstaculos **(Desafio de Obstaculos)**

1- En el desafio de vuelta libe y obstaculos el robot utiliza el sensor ultrasonico frontal para detectar cuando esta cerca de la barrera que tenga frente a el. Al llegar a una distancia ≤ 64 cm el vehiculo se detiene y da la vuelta en el sentido que hayan marcado los sensores laterales. Esto nos permite mantener una mayor constancia al momento de realizar la vueltas en ambos desafios.
   
2- En el desafio de obstaculos cuando el robot se posiciona frente a los obstaculos el sensor ddetecta la distancia entre el obstaculo y el vehiculo, de esta manera el robot sabe la cercania que tiene al obstaculo y que tan abierta o cerrada debe ser la vuelta

El codigo para usar los sensores ultrasonicos enta en el archivo [funciones](/src/S25_Obstaculos_29_08_2025/Funciones.ino), Dentro de el se encuentran la mayoria de las funciones que utilizamos en nuestro codigo principal.

**Sensores Laterales**

Los sensores laterares tienen varios objetivos en nuestro vehiculo, son los siguientes:

1. Determinar el sentido de giro (Horario-Antihorario).
2. Seguidores de pared.
3. Detectar las barreras internas.
4. Detectar las limitaciones de aparcamiento.

Anteriormente los sensores compartian el mismo puerto para el pin **Trigger** con un cable en Y. Al inicio lo haciamos por que nuestro microcontrolador era un Arduino UNO y eso nos ahorraba puertos y creiamos que era una buena idea por que tambien facilitaba el codigo, sin embargo por las necesidades de nuestro vehiculo y los sensores que añadiamos con el tiempo el Arduino UNO se quedaba muy corto de puertos y nos vimos en la necesidad de cambiar al Arduino MEGA. A pesar del cambio continuamos con la configuración de los sensores laterales, con el tiempo notamos que los sensores tenian un comportamiento erratico o no siempre daban las distancias de manera correcta. Por esta razón aprovechando la gran cantidad de puertos digitales del nuevo microcontrolador realizamos el cambio para que cada sensor tenga su propio puerto trigger.

A continuacion se explicaran cada uno de los objetivos de los sensores laterales:

1. En ambos desafios, cuando el robot robot da la primer vuelta para dirigirse a otro cuadrante enviamos la funcion *twoSUS* para bstener la distancia detectada de ambos sensores y dependiendo de cual fue el que detcto mayor distancia, determinamos el sentido de giro para la prueba: si el sensor derecho tenia la mayor distancia entonces el sendido es horario, pero si el que tenia la mayor distancia fue el izquierdo entonces el sentido es Antihorario.
   
2. En el desafio de obstaculos utilizamos un seguidor PD para seguir las barreras exteriores en los casos donde hay uno o dos objetos verdes en el cuadrante (más adelante se menciona el desarrollo del algoritmo para esquivar obstaculos). Cuando termina el cuadrante con obstaculos el robot se posiciona para detectar los obstaculos del siguiente cuadrante de obstaculos.

3. En los casos donde hay al menos un objeto rojo el robot utiliza el sensor lateral que apunta hacia las barreras internas para alinaerse con ellas, de esta manera se obtiene un mayor control de la poscion del robot despues de esquivar el obstaculo de color rojo. Anteriormente tambien segiamos la pared en el caso donde hay objetos rojos involucrados, pero como la distancia que recorria era muy pequeña ecuando el robot terminaba el seguidor terminaba en posiciones diferentes y hacia muy dificil posicionarse para el siguiente cuadrante u obstaculo.

4. El nombre de este objetivo es muy claro, no hay mayor explicacion fuera de que cuando el robot termina las 3 vueltas utilizamos uno de los sensores laterales (depende del sentido de giro) para detectar una de las limitaciones de aparcamiento para iniciar con la rutina para aparcarse.

   
## Manejo de obstaculos 

**Algoritmo**

En las reglas de la categoria se hace mención de los 36 casos posibles de posicion obstaculos, para resolver este desafío primero discutimos entre equipo cual seria la mejor opcion para resolverlo, ya que antes de programar se tiene que plantear la poblematica de manera correcta. Despues de varias horas de discusión, llegamos a la siguiente solucion: los casos de poscion de pueden simplificar a unicamente 4 casos 

- Rojo
- Verde
- Verde - Rojo
- Rojo - Verde

independientemente de el espacio donde se encuentren los casos se reducen a simplemente 4 configuraciones por cuadrante, entonces nuestra solucion es programar la rutina de los 4 casos y al terminar de esquivar los obstaculos por cuadrante el robot se posiciona para detectar los obstaculos del siguiente cuadrante. Esto se repite en bucle hasta haber completado las 3 vueltas.

**Programa para Detección de Objetos y Colores**

Nuestro programa de cámara divide la visión de la pantalla por zonas y resalta el contorno de los obstáculos, ignorando contornos más pequeños al área que abarcan los obstáculos; cambia el valor de una variable dependiendo del color del obstáculo que detecte frente a él. Y seleccona el caso dependiendo de el color y la poscion de los objetos. Para determinar la posición de los obstaculos utilizamos los pixeles de la camara en el eje Y, dependiendo en que pixel se encuentren y el color del contorno de los objetos se determina el caso.

Como el robot usa Raspberry y Arduino, la forma en que manda estos valores la cámara al Arduino, es por medio del puerto serial, imprimiendo el valor y mandándolo al Arduino, el cual hace una acción dependiendo del valor obtenido. Para vizualizar de una manera mas sencilla si se detecto el caso correcto, el robot cuenta con 4 LED's y se encienden (1 por caso) dependiendo del caso que se detecto. Como extra genera diferntes frecuencias de sonido sugun el caso.

