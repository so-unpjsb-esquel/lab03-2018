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

    if (argc != 3) {
        fprintf(stderr, "Uso: %s nombre_segmento cantidad\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * COMPLETAR
     * Abrir el segmento de memoria compartida indicado desde la linea de 
     * comandos, en modo de lectura/escritura.
     */
    fd = shm_open();

    if (fd == -1) {
        perror("shm_open()");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[2]);

    /*
     * COMPLETAR
     * Una vez abierto el segmento de memoria compartida, se puede acceder al
     * mismo utilizando el descriptor de archivo fd. Se debe ahora cambiar el
     * tamaño del segmento, utilizando la función ftruncate(). El tamaño 
     * debe ser el adecuado para almacenar una cantidad n de enteros (int).
     * Consultar el manual de la función ftruncate().
     */
    int r = ftruncate();

    // Recupera información acerca del segmento.
    fstat(fd, &sb);

    /*
     * COMPLETAR:
     * Mapear la zona de memoria compartida dentro de la memoria del proceso.
     * Consultar el manual de mmap() para ver que valores utilizar en cada 
     * parámetro. Se debe indicar lo siguiente:
     *   1er: dejar que el kernel seleccione donde crear el mapeo.
     *   2do: especificar el tamaño del mapeo (esta en la estructura sb).
     *   3ro: indicar que el mapeo sea de solo escritura.
     *   4to: indicar que la zona es compartida con otros procesos.
     *   5to: descriptor de archivo del segmento de memoria compartida.
     *   6to: offset.
     */
    addr = mmap();

    if (addr == MAP_FAILED) {
        perror("mmap()");
        exit(EXIT_FAILURE);
    }

    // Ya no es necesario mantener el descriptor de archivo.
    close(fd);

    // Escribe tanto bytes como tenga de tamaño el segmento.
    int i;
    for (i = 0; i < sb.st_size / sizeof(int); i++) {
        *addr = i;
        addr++;
    } 

    exit(EXIT_SUCCESS);
}
