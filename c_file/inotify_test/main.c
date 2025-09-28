#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#define TARGET_FILE "/home/xhh/github_repositories/code_test/c_file/inotify_test/test.txt"
#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))
int a = 0;

void* monitor_file_nonblocking() {
    int fd, wd;
    char buffer[BUF_LEN];

    // 1. 创建 inotify 实例，并设置为非阻塞模式
    fd = inotify_init1(IN_NONBLOCK);
    if (fd == -1) {
        perror("inotify_init1");
        exit(EXIT_FAILURE);
    }

    // 2. 添加监控：只监控文件修改事件 IN_MODIFY
    wd = inotify_add_watch(fd, TARGET_FILE, IN_MODIFY);
    if (wd == -1) {
        perror("inotify_add_watch");
        fprintf(stderr, "无法监控文件: %s\n", TARGET_FILE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("✅ 开始非阻塞监控文件: %s （按 Ctrl+C 停止）\n", TARGET_FILE);

    while (1) {
        fd_set read_fds;
        int max_fd = fd;
        int ret;

        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);


        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        ret = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret == -1) 
        {
            perror("select");
            break;
        } else if (ret == 0) 
        {

            continue;
        }

        if (FD_ISSET(fd, &read_fds)) 
        {
            int length = read(fd, buffer, BUF_LEN);
            if(length > 0)
            {
                ++a;
                printf("The target file has been modified,lenth = %d\n",length);
            }
                
        }
    }

    // 6. 清理（通常不会到达这里，除非异常退出）
    inotify_rm_watch(fd, wd);
    close(fd);
}

int main() {
    int t = 0;
    pthread_t th;
    pthread_create(&th, NULL, monitor_file_nonblocking, NULL);
    // monitor_file_nonblocking();
    while(1)
    {
        
        while(t != a)
        {
            t = a;
            printf("a = %d\n",a);
        }
        // sleep(1);
    }
    return 0;
}