//
// Ejercicio 4
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define N 5
const char *names[N] = { "Platon", "Kant", "Spinoza", "Marx", "Russell" };

#define M 5                     
const char *topic[M] = { "Espagueti!", "Vida", "El ser", "Star Trek", "Futbol" };

pthread_mutex_t forks[N];

// Mueve el cursor a la linea x, columna y (ver codigos ANSI)
#define xy(x, y) printf("\033[%d;%dH", x, y)

// Borra desde el cursor hasta el fin de la linea
#define clear_eol(x) print(x, 13, "\033[K")

// Borra la pantalla 
#define clear() printf("\033[H\033[J") 

void print(int y, int x, const char *fmt, ...)
{
    static pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;
    va_list ap;
    va_start(ap, fmt);

    pthread_mutex_lock(&screen);
    xy(y + 1, x), vprintf(fmt, ap);
    xy(N + 1, 1), fflush(stdout);
    pthread_mutex_unlock(&screen);
}

void eat(int id)
{
    int f[2], ration, i;        /* tenedores */
    f[0] = f[1] = id;

    // hace a algunos filosofo "zurdos"
    f[id & 1] = (id + 1) % N;

    clear_eol(id);
    print(id, 13, "..oO (necesito tenedores)");

    // trata de tomar los tenedores
    for (i = 0; i < 2; i++) {
        if (!i) {
            clear_eol(id);
	}

        print(id, 13 + (f[i] != id) * 12, "tenedor%d", f[i]);

        // espera para tomar el segundo tenedor
        sleep(3);
    }

    // come durante un tiempo
    for (i = 0, ration = 3 + rand() % 8; i < ration; i++) {
        print(id, 35 + i * 4, "ñom");
        sleep(1);
    }
}

void think(int id)
{
    int i, t;
    char buf[64] = { 0 };

    do {
        clear_eol(id);

        // piensa en algo...
        sprintf(buf, "..oO (%s)", topic[t = rand() % M]);

        for (i = 0; buf[i]; i++) {
            print(id, i + 13, "%c", buf[i]);
            if (i < 5)
                usleep(200000);
        }

        usleep(500000 + rand() % 1000000);
    } while (t);
}

void *filosofo(void *a)
{
    int id = *(int *) a;
    print(id, 1, "%10s", names[id]);
    while (1) {
        think(id);
        eat(id);
    }
}

int main()
{
    int i, id[N];
    pthread_t tid[N];

    clear();

    for (i = 0; i < N; i++) {
        id[i] = i;
    }

    for (i = 0; i < N; i++) {
        pthread_create(tid + i, 0, filosofo, id + i);
    }

    pthread_exit(0);
}

