# Laboratorio 3 - Comunicación entre procesos y sincronización

## Ejercicio 1
En este ejercicio usaremos el API de cola de mensajes de POSIX, que permite intercambiar datos entre procesos mediante el paso de mensajes. El manual [`mq_overview`](http://man7.org/linux/man-pages/man7/mq_overview.7.html) presenta una introducción general al API de colas de mensajes.

Las funciones del API que vamos a usar en este ejercicio son:
* [`mq_open()`](http://man7.org/linux/man-pages/man3/mq_open.3.html): crea una nueva cola de mensajes, o abre una ya existente.
* [`mq_send()`](http://man7.org/linux/man-pages/man3/mq_send.3.html): envía un mensaje a la cola de mensajes, con una prioridad dada.
* [`mq_receive()`](http://man7.org/linux/man-pages/man3/mq_send.3.html): recibe un mensaje.
* [`mq_close()`](http://man7.org/linux/man-pages/man3/mq_close.3.html): cierra el descriptor de una cola de mensajes (se trata como si fuera un descriptor de archivo).
* [`mq_unlink()`](http://man7.org/linux/man-pages/man3/mq_unlink.3.html): elimina una cola de mensajes.
* [`mq_getattr()`](http://man7.org/linux/man-pages/man3/mq_getattr.3.html): recupera los atributos de la cola de mensajes especificada.

Completar los siguientes programas en el directorio `mq`, que permiten enviar y recibir mensajes por medio de una cola de mensajes:
* `mq_open.c`: crea una cola de mensajes.
* `mq_send.c`: envia un mensaje a travez de la cola de mensajes especificada.
* `mq_receive.c`: lee el mensaje de mayor prioridad en la cola de mensajes indicada.
* `mq_attr.c`: muestra información acerca de la cola de mensajes especificada.
* `mq_unlink.c`: elimina la cola de mensajes indicada.

Una vez completados, deben poder crear colas de mensajes y envíar y recibir mensajes por medio de las mismas.

Responder también las siguientes preguntas:
1. Ejecutar el programa `mq_receive` cuando la cola de mensajes está vacía, ¿Qué sucede? ¿Por qué?
2.	Enviar varios mensajes, algunos con distinta prioridad y otros con la misma prioridad, usando el programa `mq_send`. Luego, recuperarlos con `mq_receive`. ¿En qué orden son recuperados de la cola de mensajes? ¿Cómo se ordenan los mensajes con la misma prioridad?

## Ejercicio 2
En este ejercicio usaremos el API de POSIX para crear y utilizar segmentos de memoria compartida. Mediante estos segmentos, múltiples procesos pueden intercambiar datos de una manera mucho más rapida que mediante el intercambio de mensajes. El manual [`shm_overview`](http://man7.org/linux/man-pages/man7/shm_overview.7.html) tiene una introducción al API de memoria compartida de POSIX.

Las principales funciones que vamos a usar en el ejercicio son:
* [`shm_open()`](http://man7.org/linux/man-pages/man3/shm_open.3.html): crea un nuevo objeto de memoria compartida, o abre uno ya existente.
* [`ftruncate()`](http://man7.org/linux/man-pages/man2/ftruncate.2.html): cambia ("trunca") el tamaño del segmento de memoria compartida (es la misma función que cambia el tamaño de un archivo).
* [`mmap()`](http://man7.org/linux/man-pages/man2/mmap.2.html): realiza el mapeo del segmento de memoria compartida indicado dentro del espacio de direcciones del proceso.
* [`shm_unlink()`](http://man7.org/linux/man-pages/man3/shm_unlink.3.html): elimina el segmento de memoria compartida indicado.
* [`close()`](http://man7.org/linux/man-pages/man2/close.2.html): cierra el descriptor de un segmento de memoria compartida.

Completar los siguientes programas en el directorio `shm` haciendo uso del API de memoria compartida de POSIX, que utilizan memoria compartida para escribir y leer una serie de datos:
* `shm_create.c`: crea un segmento de memoria compartida.
* `shm_write.c`: escribe una serie de datos en el segmento de memoria compartida indicado.
* `shm_read.c`: lee los datos que se encuentren el segmento de memoria compartida especificado.
* `shm_unlink.c`: elimina el segmento de memoria compartida.

Responder también la siguiente pregunta:
1. ¿Cómo sabe `shm_read` cuanto datos puede leer del segmento de memoria compartida?

## Ejercicio 3
El programa `eco.c` crea dos procesos hijos que se comunican por medio de una tubería. Uno de los procesos lee una línea desde la _entrada estándar_, y la envía por la tubería. El segundo proceso lee esta línea de la tubería y la imprime por la _salida estándar_. El programa termina cuando se ingresa una linea en blanco (osea, un `\n`). 

Modificar el programa de manera que ambos procesos se comuniquen mediante paso de mensajes, en lugar de una tubería.

## Ejercicio 4
El programa `glob.c`, crea dos hilos que repetidamente incrementan la variable global `glob`, copiando primero su valor en una variable automática (local), incrementando el valor de dicha variable, y copiando luego el nuevo valor en `glob`. Cada hilo incrementa `glob` el número de veces indicado en la línea de comandos.
* Compilar y ejecutar el programa, probando valores hasta que se encuentre una condiciones de carrera.
* ¿Por qué ocurre esta situación de carrera? ¿Cómo se podría evitar?
* Evitar la condición de carrera mediante el uso de mutexes (`pthread_mutex_t`).
* Evitar la condición de carrera mediante un semáforo (`sem_t`) en lugar del mutex.

## Ejercicio 5
Completar los programas `sem_open.c`, `sem_wait.c`, `sem_post.c` y `sem_unlink.c` en el directorio `sem`.

Tendrían que poder ejecutar esta serie de comandos, en donde se crea un semáforo con un valor inicial de cero, y se realiza una operación _down_, luego un _up_, y finalmente se lo elimina.
```
$ sem_open semaforo 0
$ sem_wait semaforo &
$ sem_post semaforo
$ sem_unlink semaforo
```

## Ejercicio 6
El programa `philo.c` implementa un ejemplo del problema de la _cena de los filósofos_. Durante la ejecución del programa puede ocurrir una condición de carrera. 
1. Modificar el programa para evitar esta condición, mediante el uso de semáforos y mutexes.
2. El programa incorpora una solución para evitar el _bloqueo mutuo_ o _abrazo mortal_. Explicarla.

## Ejercicio 7 (opcional)
Modificado de: https://pdos.csail.mit.edu/6.828/2017/homework/lock.html

En este ejercicio exploraremos la programación paralela, utilizando hilos, exclusión mutua y una tabla _hash_. Para lograr un paralelismo real, se debe ejecutar este programa en una computadora con dos o más núcleos. 

En primer lugar, compilar y ejecutar el programa `ph.c`:
```
$ make ph
$ ./ph 2
```
El número 2 especifica el número de hilos que realizaran operaciones _put_ y _get_ sobre una tabla _hash_. Cuando termine de ejecutar, el programa debe generar una salida similar a la siguiente:
```
0: put time = 2.871728
1: put time = 2.957073
1: get time = 12.731078
1: 1 keys missing
0: get time = 12.731874
0: 1 keys missing
completion time = 15.689165
```
Cada hilo ejecuta dos fases. En la primera, almacena claves en la tabla,
y en la segunda fase trata de recuperar dichas claves de la tabla. La salida del programa indica cuanto tiempo duro cada fase para cada hilo. La última linea ("_completion time_") indica el tiempo total de ejecución del programa. En la salida de ejemplo anterior, el programa ejecutó durante aproximadamente 16 segundos.

Por ejemplo, si ejecutaramos nuevamente el programa, pero con un único hilo:
```
$ ./a.out 1
0: put time = 5.350298
0: get time = 11.690395
0: 0 keys missing
completion time = 17.040894
```
Vemos que el tiempo total de ejecución es levemente mayor que para el caso de ejecución con dos hilos (~17s contra ~15.6s). Sin embargo, notar que al utilizar dos hilos se realizó el doble de trabajo en la fase _get_, lo que representa un mejora de casi 2x (¡nada mal!). En cambio, para la fase _put_ se logró una mejora mucho más pequeña, ya que entre ambos hilos guardaron el mismo número de claves en algo menos de la mitad de tiempo (~2.9s contra ~5.3s).

Independientemente de si al ejecutar el programa en sus computadoras logran un incremento de velocidad, o la magnitud del mismo, notarán que el programa no funciona correctamente. Al ejecutar el mismo utilizando dos hilos, algunas claves posiblemente no puedan ser recuperadas. En el ejemplo anterior, una de las claves se perdió ("_1 keys missing_").

Esto empeora cuando incrementamos el número de hilos:
```
2: put time = 1.516581
1: put time = 1.529754
0: put time = 1.816878
3: put time = 2.113230
2: get time = 15.635937
2: 21 keys missing
3: get time = 15.694796
3: 21 keys missing
1: get time = 15.714341
1: 21 keys missing
0: get time = 15.746386
0: 21 keys missing
completion time = 17.866878
```
Dos consideraciones:
- El tiempo total de ejecución es aproxidamente el mismo que para el caso de dos hilos. Sin embargo, se realizó casi el doble de operaciones _get_, lo que indica que se esta obteniendo una buena paralelización.
- Más claves se han perdido. Es posible, sin embargo, que en una ejecución particular se pierdan más o menos claves, o incluso que no se pierda ninguna. ¿Por qué? Identificar la secuencia de eventos que pueden llevar a que se pierda una clave en el caso de dos o más hilos.

Para evitar la pérdida de claves, es necesario emplear exclusión mutua, durante las operaciones _put_ y _get_. Las funciones a utilizar son:
```
pthread_mutex_t lock;     // declare a lock
pthread_mutex_init(&lock, NULL);   // initialize the lock
pthread_mutex_lock(&lock);  // acquire lock
pthread_mutex_unlock(&lock);  // release lock
```

Se pide:
1. Modificar el código del programa `ph.c` de manera que no se pierdan claves al utilizar dos o más hilos. ¿Es aún la versión de dos hilos más rápida que la versión con un único hilo? De no ser así, ¿por qué?
2. Modificar el código para que las operaciones _get_ puedan ejecutarse en paralelo. (Tip: ¿Es necesario utilizar exclusión mútua al realizar una operación _get_?)
3. Modificar el código para que algunas de las operaciones _put_ puedan ejecutar en paralelo.

---

¡Fin del Laboratorio 3!