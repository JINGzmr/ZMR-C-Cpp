#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main() {
    int fd;
    struct termios options;

    // 打开串口
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyS0");
        return -1;
    }

    // 获取当前串口配置
    tcgetattr(fd, &options);

    // 设置波特率
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // 配置串口参数
    options.c_cflag |= (CLOCAL | CREAD);    // 启用接收器，设置本地模式
    options.c_cflag &= ~PARENB;             // 无校验
    options.c_cflag &= ~CSTOPB;             // 1位停止位
    options.c_cflag &= ~CSIZE;              // 清除数据位标志
    options.c_cflag |= CS8;                 // 8位数据位

    // 应用配置
    tcsetattr(fd, TCSANOW, &options);

    // 写入数据到串口
    char *data = "Hello, serial port!";
    int n = write(fd, data, strlen(data));
    if (n < 0) {
        perror("Write failed");
        close(fd);
        return -1;
    }

    // 读取数据
    char buf[256];
    n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("Read failed");
    } else {
        buf[n] = '\0';
        printf("Received: %s\n", buf);
    }

    // 关闭串口
    close(fd);
    return 0;
}
