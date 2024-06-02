#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/mman.h>

void PB_function(int size) {
    int i = 0;
    int fd = 0;
    struct timeval tv1, tv2;
    int* array;

    /* mmap */
    gettimeofday(&tv1, NULL);
    fd = open("mmap_test", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    array = mmap(NULL, sizeof(int) * size, PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd, 0);
    if (array == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < size; ++i)
        ++array[i];
    msync(array, sizeof(int) * size, MS_SYNC);
    munmap(array, sizeof(int) * size);
    close(fd);
    gettimeofday(&tv2, NULL);
    printf("mmap 耗时: %ldms  |  ", (tv2.tv_usec - tv1.tv_usec) / 1000);
    // 延迟以便查看 maps 文件
    sleep(60);
}
