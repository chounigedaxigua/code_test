#include "shared_data.h"

int main() {
    // 打开共享内存
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 映射共享内存
    SharedData *data = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // 打开信号量
    sem_t *sem_write = sem_open(SEM_WRITE_NAME, 0);
    sem_t *sem_read = sem_open(SEM_READ_NAME, 0);

    if (sem_write == SEM_FAILED || sem_read == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 等待可以读（P操作）
        sem_wait(sem_read);

        if (data->ready) {
            printf("[Consumer] Received: %s\n", data->message);
            data->ready = 0;
        }

        // 通知可以写（V操作）
        sem_post(sem_write);
    }

    // 清理（通常不会执行到这里）
    munmap(data, sizeof(SharedData));
    close(shm_fd);
    sem_close(sem_write);
    sem_close(sem_read);

    return 0;
}