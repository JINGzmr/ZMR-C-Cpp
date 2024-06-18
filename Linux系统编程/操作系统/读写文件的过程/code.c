#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char write_buf[] = "Hello, Linux file I/O!";
    ssize_t bytes_written = write(fd, write_buf, strlen(write_buf));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    printf("Wrote %ld bytes to the file.\n", bytes_written);

    // 将文件指针移到文件开头
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    char read_buf[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, read_buf, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    printf("Read %ld bytes from the file: %s\n", bytes_read, read_buf);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}