#include <fcntl.h>      // Constantes O_*
#include <sys/stat.h>   // Constantes de modo
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>     // ftruncate()
#include <string.h>     // strlen()
#include <stdio.h>      // printf()

int main(int argc, char* argv[])
{
    int fd;
    int *addr;
    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s nombre_segmento\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Abrir el segmento de memoria compartida cuyo nombre es indicado desde
     * la linea de comandos, en modo de solo lectura. Consultar el manual de
     * la función shm_open().
     */
    fd = shm_open();

    if (fd == -1) {
        perror("shm_open()");
        exit(EXIT_FAILURE);
    }

    // recupera información acerca del segmento
    fstat(fd, &sb);

    /* 
     * COMPLETAR
     * Mapear la zona de memoria compartida dentro de la memoria del proceso.
     * Consultar el manual de la función para ver que valores utilizar, para
     * cada argumento. Deben indicar lo siguiente:
     * - 1er: dejar que el kernel seleccione donde crear el mapeo.
     * - 2do: especificar el tamaño del mapeo (esta en la estructura sb).
     * - 3ro: indicar que el mapeo sea de solo lectura.
     * - 4to: indicar que la zona es compartida con otros procesos.
     * - 5to: descriptor de archivo del segmento de memoria compartida.
     * - 6to: offset.
     */
    addr = mmap();

    if (addr == MAP_FAILED) {
        perror("mmap()");
        exit(EXIT_FAILURE);
    }

    // Cierra el descriptor de archivo ya que no es necesario a partir de 
    // este momento.
    close(fd);

    // Lee tantos bytes como tenga el tamaño del segmento.
    int i = 0;
    for (i = 0; i < sb.st_size / sizeof(int); i++) {
        printf("%d\n", *addr);
        addr++;
    } 

    exit(EXIT_SUCCESS);
}
