#include "shared_data.h"

int main() {
    // 创建共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 设置共享内存大小
    if (ftruncate(shm_fd, sizeof(SharedData)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // 映射共享内存
    SharedData *data = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // 创建两个信号量：一个控制写，一个控制读
    sem_t *sem_write = sem_open(SEM_WRITE_NAME, O_CREAT, 0666, 1); // 初始可写
    sem_t *sem_read = sem_open(SEM_READ_NAME, O_CREAT, 0666, 0);   // 初始不可读

    if (sem_write == SEM_FAILED || sem_read == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    int counter = 0;
    while (1) {
        // 等待可以写（P操作）
        sem_wait(sem_write);

        // 写入数据
        snprintf(data->message, sizeof(data->message), "Hello from Producer %d", counter++);
        data->ready = 1;

        printf("[Producer] Sent: %s\n", data->message);

        // 通知可以读（V操作）
        sem_post(sem_read);

        sleep(1); // 模拟实时间隔
    }

    // 清理（通常不会执行到这里，实际应通过信号处理退出并清理）
    munmap(data, sizeof(SharedData));
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem_write);
    sem_close(sem_read);
    sem_unlink(SEM_WRITE_NAME);
    sem_unlink(SEM_READ_NAME);

    return 0;
}