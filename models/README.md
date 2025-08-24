Modelos 
===
En este apartado se encuentran los diseños y modelos 3d de las partes mecanicas que componen el robot, ademas de informacion importante acerca de las piezas y los compoenetes electricos que se usan en ellas.

Manejo de Movilidad
===

-Motor DC 12v con encoder 
===
Escogimos este motor principalmente por el encoder ya incluido en el, ya que con este sensor podemos conocer la posición del robot y ese dato nos aporta varios beneficios en nuestra solución: nos permite conocer cuantas vueltas ha dado, la distancia que se ha desplazado el robot, ayudarnos a estacionarnos en paralelo, en general todas las variables que estén relacionadas con la posición del robot. 

Inicialmente utilizábamos otro motor que ya tenía incluido un sistema diferencial, era parte de un juguete de un carro RC, con ese motor participamos en la etapa regional de Mexicali. Hicimos el cambio de motor ya que la velocidad del motor variaba mucho y no teníamos un encoder y sumadas esas 2 variables hacia muy difícil mantener la constancia del movimiento del robot. Sabemos que es imposible hacer que un robot repita de manera exacta una rutina en varios intentos, pero ese componente nos dificultaba aun mas esta tarea. Por eso realizamos el cambio a un motor con encoder y el diferencial de lego, ya que nos permite tener más control sobre diferentes variables y parámetros anteriormente mencionados. Para eso tuvimos que diseñar un soporte para el motor en el que también pudiera conectarse junto con el diferencial de lego nos tomó 3 revisiones. 

Imagen soporte rev1

Así se veía al inicio y nos permitía hacer pruebas sin embargo el motor no se fijaba de ninguna manera al soporte y eso generaba perturbaciones en nuestras pruebas. 

Imagen soporte rev3 

En la foto se puede ver la revisión actual del soporte en donde el motor ya se fija a este mismo y no genera las perturbaciones por el movimiento. Así mismo tuvimos un caso similar con el engrane que se conecta al motor. Inicialmente hicimos pruebas con un engrane Spur de 24 dientes de lego, taladramos el centro del engrane para que entrara en el eje principal del motor e inicialmente eso nos ayudo par ver como se comportaría el sistema diferencial. Sin embargo, no podíamos quedarnos con eso ya que con el desgate generado por el uso, el agujero driver se terminaba deformando y tenía un backlash bastante considerable. Usando la misma medida de lego realizamos un diseño de un engrane igual, pero con las medidas de nuestro eje principal.

Imagen transitatoria de los engranes Viejo----- > Nuevo 

-Dirección
===
Nuestra dirección funciona a partir de enlances que están conectados a manguetas y en el centro de una de las vigas de los enlaces hay una pieza que se conecta a un servomotor MG90S, el servomotor nos permite llevar la dirección a los ángulos que nosotros necesitamos dentro de nuestro algoritmo. Estos son diseños realizados por el equipo y para fabricarlos utilizamos MDF para los enlaces e impresión 3D para las manguetas.

Foto de la dirección y sus piezas

Utilizamos llantas de lego, en especifico el modelo que tiene la medida 62.4mm ya que las hemos utilizado en competencias anteriores de la categoría robomission, confiamos mucho en ellas tanto por su agarre al suelo y poca fricción que generan.

-Movimiento 
===
Para hacer que el robot se mueva derecho utilizamos un girosensor con un controlador PD, este nos permite hacer que el robot mantenga su posición al avanzar, como anteriormente hemos mencionado es imposible que el robot siempre se mantenga derecho, pero con este programa y sensor podemos hacer que el robot mantenga su posición por una buena cantidad de distancia y su desviación es muy pequeña , nunca superando los 2 cm del punto inicial. 
De igual manera utilizamos el Girosensor para las vueltas del robot, al momento de llegar al punto deseado el robot gira la dirección y el robot avanza hasta detectar el ángulo deseado, cuando llega al ángulo marcado detiene el motor y regresa la dirección a la posición original. 
