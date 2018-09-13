#include <fcntl.h>      // Constantes O_*
#include <sys/stat.h>   // Constantes de modo
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>      // printf()

int main(int argc, char* argv[])
{
    int r;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s nombre_segmento\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR.
     * Eliminar el segmento de memoria compartida indicado en la linea de
     * comandos. Consultar el manual de shm_unlink().
     */
    r = shm_unlink();

    if (r == -1) {
        perror("shm_open()");
        exit(EXIT_FAILURE);
    }
    
    printf("Shared memory segment %s removed.\n", argv[1]);

    exit(EXIT_SUCCESS);
}
