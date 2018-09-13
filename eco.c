#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUF_SIZE 1024

char buf[BUF_SIZE];

void writer(int fd[2]) {
    int n;
    close(fd[0]);
    do {
        n = read(0, buf, sizeof(buf));
        write(fd[1], buf, n);
    } while(n > 1);
}

void reader(int fd[2]) {
    int n;
    close(fd[1]);
    do {
        n = read(fd[0], buf, sizeof(buf));   
        write(1, buf, n);
    } while(n > 1);
}

int main(int argc, char* argv[])
{
    pid_t proc1, proc2;
    int fd[2];

    int r = pipe(fd);

    if (r == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    proc1 = fork();

    if (proc1 > 0) {
        proc2 = fork();
        if(proc2 > 0) {
            waitpid(proc1, NULL, 0);
            waitpid(proc2, NULL, 0);
        } else {
            reader(fd);
        }
    } else {
        writer(fd);
    }

    exit(EXIT_SUCCESS);
}
