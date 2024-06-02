#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "mmap_test"

void initialize_file(int size) {
    int *array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
    int fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        free(array);
        exit(EXIT_FAILURE);
    }
    write(fd, array, sizeof(int) * size);
    close(fd);
    free(array);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return -1;
    }

    int size = atoi(argv[1]);
    initialize_file(size);
    return 0;
}
