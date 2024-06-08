#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h> 
using namespace std;

void daemonize() {
    // 创建子进程，退出父进程
    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 创建一个新的会话
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // 设置当前工作目录
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    // 关闭标准输入、输出和错误
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 重定向标准输出和错误到 /dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
}

int main() {
    // 守护进程化
    daemonize();

    // 在后台运行的守护进程将在这里执行其他任务
    // 例如记录日志、处理请求等

    // 示例：守护进程每隔一段时间向日志文件写入一条信息
    ofstream logfile("/var/log/mydaemon.log", ios::app);
    if (logfile.is_open()) {
        while (true) {
            logfile << "Daemon is running..." << endl;
            logfile.flush();
            sleep(10); // 等待10秒
        }
        logfile.close();
    } else {
        cerr << "Failed to open log file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
