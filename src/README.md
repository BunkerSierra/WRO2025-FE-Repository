Software Control
====

En este apartado se encuentra el software que hace funcionar los componentes electricos junto a las partes mecanicas del vehiculo. Sera hara mención de los componentes eléctricos de manera general en este apartado, para más información acerca de los compoentes revisar las siguientes carpetas:

- [Models](/models).
- [Schemes](/schemes).

## Control de Posición
Para saber cuanto se ha movido el robot, utilizamos el encoder que se encuentra incorporado en nuestro motor. En concreto es un Encoder tipo **HALL**: dispositivo que utiliza sensores de efecto Hall para detectar el movimiento rotatorio y convertirlo en una señal eléctrica que indica posición o velocidad. 
¿Que es el ***efecto hall***? El efecto Hall es la aparición de una diferencia de potencial (o campo eléctrico) transversal a un conductor cuando una corriente eléctrica lo atraviesa y, al mismo tiempo, se le aplica un campo magnético perpendicular a la dirección de la corriente.

Realizamos un software de control PID para que el robot avance la cantidad de pulsos que le indicamos, con el control PID nos aseguramos de que el robot no le falte o supere una gran cantidad de pulsos y asi obtener más constancia en las pruebas que realizamos con nuestro vehiculo. Hasta el momento hemos logrado mantenerlo en un rango de ±4 pulsos. El software esta incorporado tanto en el desafio de vuelta libre tanto en el de obstaculos.

- [CTRL_POS](/src/CTRL_POS.ino).

## Sensores Ultrasonicos
Como hemos mencionado en otros apartados del repositorio nuestro robot cuanta con 3 sensores ultrasonicos, uno en la parte frontal y 2 en los laterales (1 por lado), El sensor frontal tiene 2 funciones en nuestro vehiculo:

  1. Detectar la distancia entre el robot y las barreras de la pista **(Desafio Abierto)**
  2. Obtener la distancia entre el robot y los obstaculos **(Desafio de Obstaculos)**

1. En el desafio de vuelta libe y obstaculos el robot utiliza el sensor ultrasonico frontal para detectar cuando esta cerca de la barrera que tenga frente a el. Al llegar a una distancia ≤ 64 cm el vehiculo se detiene y da la vuelta en el sentido que hayan marcado los sensores laterales. Esto nos permite mantener una mayor constancia al momento de realizar la vueltas en ambos desafios.
   
2. En el desafio de obstaculos cuando el robot se posiciona frente a los obstaculos el sensor ddetecta la distancia entre el obstaculo y el vehiculo, de esta manera el robot sabe la cercania que tiene al obstaculo y que tan abierta o cerrada debe ser la vuelta

El codigo para usar los sensores ultrasonicos enta en el archivo [funciones](/src/S25_Obstaculos_29_08_2025/Funciones.ino), Dentro de el se encuentran la mayoria de las funciones que utilizamos en nuestro codigo principal.
