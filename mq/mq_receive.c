#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>    /* Constantes O_* */
#include <sys/stat.h> /* Constantes de modo */
#include <mqueue.h>   /* Cola de mensajes */

int main(int argc, char* argv[])
{
    mqd_t mq;
    struct mq_attr attr;
    char *buf;
    int r;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s queue\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Abrir la cola de mensajes indicada en modo solo para lectura.
     */
    mq = mq_open();

    if (mq < 0 ) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    /* 
     * COMPLETAR
     * Obtener los atributos de la cola de mensajes abierta.
     */
    r = mq_getattr();

    if (r == -1) {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Crear un buffer lo suficientemente grande como para almacenar el 
     * contenido del mensaje que se va a leer desde la cola de mensajes.
     * El tamaño máximo de los mensajes que se pueden enviar a travez de
     * la cola de mensajes esta especificado en los atributos de la misma.
     */
    buf = (char*) malloc();

    unsigned int prio = 0;

    /* 
     * COMPLETAR
     * Obtener el siguiente mensaje disponible en la cola de mensajes mq,
     * guardando su contenido en el buffer buf, y la prioridad del mismo
     * en la variable prio. Consultar el manual mq_receive().
     */
    r = mq_receive();

    if (r == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Imprimir el contenido del mensaje, y su prioridad.
     */
    printf("Message received: ?, priority ?\n");

    exit(EXIT_SUCCESS);
}
    
