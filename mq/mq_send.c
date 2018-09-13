#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>    /* Constantes O_* */
#include <sys/stat.h> /* Constantes de modo */
#include <mqueue.h>   /* Cola de mensajes */

int main(int argc, char* argv[])
{
    mqd_t mq;

    if (argc < 4) {
        fprintf(stderr, "Uso: %s queue msg prio\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Abrir la cola de mensajes indicada como parametro desde la línea
     * de comandos. Como queremos enviar un mensaje, abrirla únicamente
     * para escritura. Consultar el manual de la función mq_open().
     */
    mq = mq_open();

    if (mq < 0) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    int prio = atoi(argv[3]);

    /*
     * COMPLETAR
     * Enviar el mensaje (indicado como argumento en la linea de comandos)
     * a travez de la cola de mensajes mq, con prioridad prio.
     */
    int r = mq_send();

    if (r == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    printf("Message sended!\n");

    exit(EXIT_SUCCESS);
}
    
