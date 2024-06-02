#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern void PA_function(int size);
extern void PB_function(int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return -1;
    }

    int size = atoi(argv[1]);
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return -1;
    } else if (pid1 == 0) {
        // Child process PA
        PA_function(size);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return -1;
    } else if (pid2 == 0) {
        // Child process PB
        PB_function(size);
        exit(0);
    }

    // Parent process waits for both child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}
