Software Control
====

En este apartado se encuentra el software que hace funcionar los componentes electricos junto a las partes mecanicas del vehiculo. Sera hara mención de los componentes eléctricos de manera general en este apartado, para más información acerca de los compoentes revisar las siguientes carpetas:

- [Models](/models).
- [Schemes](/schemes).

## Control de Posición
Para saber cuanto se ha movido el robot, utilizamos el encoder que se encuentra incorporado en nuestro motor. En concreto es un Encoder tipo ***HALL***: dispositivo que utiliza sensores de efecto Hall para detectar el movimiento rotatorio y convertirlo en una señal eléctrica que indica posición o velocidad. 
¿Que es el ***efecto hall***? El efecto Hall es la aparición de una diferencia de potencial (o campo eléctrico) transversal a un conductor cuando una corriente eléctrica lo atraviesa y, al mismo tiempo, se le aplica un campo magnético perpendicular a la dirección de la corriente.

Realizamos un software de control PID para que el robot avnce la cantidad de pulsos que le indicamos, con el control PID nos aeguramos de que el robot no le falte o supere una gran cantidad de pulsos y asi mantener mas constancia en las pruebas que realizamos con nustro vehiculo. Hasta el momento hemos logrado mantenerlo en un rango de ±4 pulsos. El software esta incorportarado tanto en el desafio de vulta libre tanto en el de obstaculos.

