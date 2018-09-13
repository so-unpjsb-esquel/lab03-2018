#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    /* Constantes O_* */
#include <sys/stat.h> /* Constantes de modo */
#include <mqueue.h>   /* Cola de mensajes */

int main(int argc, char* argv[])
{
    mqd_t mq;

    if (argc < 4) {
        fprintf(stderr, "Uso: %s nombre nro_msjs tam_msjs\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Crear la cola de mensajes utilizando la función mq_open(). Si ya
     * existe una cola de mensajes con el mismo nombre, la funcion tiene
     * que fallar. Los permisos deben ser de escritura-lectura para el 
     * usuario, y de solo lectura para grupo y el resto de los usuarios. 
     * No indicamos atributos, asi que el último parámetro debe ser NULL.
     */
    mq = mq_open();

    if (mq < 0) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Message queue created.\n");

    exit(EXIT_SUCCESS);
}
    
