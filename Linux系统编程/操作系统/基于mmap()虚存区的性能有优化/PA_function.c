#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

void PA_function(int size) {
    int i = 0;
    int fd = 0;
    struct timeval tv1, tv2;
    int* array = (int*)malloc(sizeof(int) * size);

    /* read */
    gettimeofday(&tv1, NULL);
    fd = open("mmap_test", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (sizeof(int) * size != read(fd, (void*)array, sizeof(int) * size)) {
        printf("Reading data failed...\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < size; ++i)
        ++array[i];
    if (sizeof(int) * size != write(fd, (void*)array, sizeof(int) * size)) {
        printf("Writing data failed...\n");
        exit(EXIT_FAILURE);
    }
    free(array);
    close(fd);
    gettimeofday(&tv2, NULL);
    printf("read/write 耗时： %ldms  |  ", (tv2.tv_usec - tv1.tv_usec) / 1000);
    // 延迟以便查看 maps 文件
    sleep(60);
}
