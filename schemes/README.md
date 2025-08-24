Diagramas Electricos
====

En esta seccion, se presentaran los diagramas electricos de todos los componentes electricos. Tambien una descripcion de como se utilizan y por que los escogimos. 

Gestión de Potencia y los Sentidos
====

-Energía
El robot utiliza baterías de 3.7v a 9900mAh(18650), en total usa 6 baterías y están divididas en 3 portabaterias conectados en paralelo, esto ultimo para administra de manera eficiente la corriente del robot. El voltaje máximo del robot es de 8.4v.
Para entregarle la energía suficiente a nuestra computadora gráfica, el RaspBerry pi 4, utilizamos un regulador de voltaje regulado a 5.1v. Esto permite que la placa pueda funcionar correctamente sin la necesidad de conectarlo a un tomacorriente, cabe recalcar que al inicio nuestras pruebas para la gestión de obstáculos las realizábamos de esa manera, con el RaspBerry conectado a un tomacorriente al inicio esto nos permitió ver el comportamiento de nuestro código, pero a futuro era obvio que teníamos solucionar este problema ya que el robot no puede estar conectado a un tomacorriente durante las pruebas;).

-Sensores
Al inicio de la temporada nuestra propuesta fue utilizar los sensores laser VL53L0X, pensamos que serían la mejor opción por su largo alcance y precisión descrita, entonces nuestro primer chasis lo diseñamos teniendo en mente el uso de esos sensores. Conforme Realizamos pruebas notamos que por exactamente las características que seleccionamos esos sensores nos estaban afectando a nuestras pruebas y el algoritmo que propusimos, Los sensores no tienen un rango de visón recto, sino cónico y eso hacia que los sensores detectaran el suelo y las pruebas fallaban mucho. Por si no fuera poco, usar 3 de esos sensores consumían una cantidad intrigante de memoria de nuestro microcontrolador (Arduino UNO en ese momento).
Todos estos problemas nos condujeron a tomar la decisión de reemplazar los sensores laser por sensores ultrasónicos HC - SR04, con esos sensores participamos en la etapa regional y a día de hoy siguen siendo parte de nuestro modelo actual de robot, hacer el cambio fue sencillo ya que los soportes que utilizamos para los sensores ultrasónicos ya los habíamos diseñado para proyectos anteriores, e incorporarlos al chasis fue sencillo ya que siempre intentamos que los accesorios y sensores de nuestros proyectos sean modulares, ósea que sean fácil de reemplazar y el diseño del encastre para encajar el soporte de los sensores ultrasónicos en el chasis era el mismo que el de los sensores laser.

Esto hizo que la implementación y pruebas de los sensores fuera un cambio accesible y rápido.

 Anteriormente mencionamos que contamos con 3 sensores ultrasónicos, 1 al frente del robot y los otros 2 se encentran a los costados, los sensores de los contados son principalmente utilizados para encontrar la dirección de giro del robot, una vez el robot sale del primer cuadrante (en ambos desafíos) siempre habrá un lado donde halla barrera y un lado que no tenga barrera, el sensor que detecte la mayor distancia dictara el sentido del giro del robot, horario o antihorario. Mientras tanto el sensor ultrasónico dele frente tiene varias funciones, una de ellas es detectar la distancia entre el muro y el robot antes de dar vuelta en el desafío de vuelta libre, al detectar que está a 50 cm de la barrera el robot se detiene y procede a dar la vuelta. Otra de sus funciones es detectar la distancia entre el robot y un obstáculo en el desafío de obstáculos, cuando el robot se encuentra frente a menos de 15 cm de un obstáculo se detiene y gira en el sentido que el color indique. 
