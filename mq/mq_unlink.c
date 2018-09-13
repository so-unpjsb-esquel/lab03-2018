#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>   /* Cola de mensajes */

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Eliminar la cola de mensajes indicada desde la linea de comandos.
     */
    int r = mq_unlink();

    if (r < 0) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }

    printf("Message queue deleted.\n");

    exit(EXIT_SUCCESS);
}
    
