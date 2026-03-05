#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


/*
*   **特点**：区分读/写操作。

    *   **读锁**：可**共享**，允许多个读线程同时访问。
    *   **写锁**：**独占**，写时阻塞所有其他读/写线程。
*   **适用场景**：**读多写少**，如缓存、配置表等。
*   **C语言实现**：通过 POSIX 线程库 (`pthread_rwlock_t`) 提供


#include <pthread.h>
// 初始化读写锁
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
// 申请读锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
// 申请写锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
// 解锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
// 销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
*/

typedef struct {
    int config_value;
    char config_name[20];
} AppConfig;

AppConfig g_config = {100, "Default Config"};

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

// 读者线程函数
void* reader_thread(void* arg) {
    long thread_id = (long)arg;
    int read_count = 0;

    while (read_count < 3) { // 每个读者读3次
        // 尝试获取读锁
        pthread_rwlock_rdlock(&rwlock);

        printf("[Reader %ld] Read: Value=%d, Name='%s'\n", 
               thread_id, g_config.config_value, g_config.config_name);
        
        usleep(100000);

        pthread_rwlock_unlock(&rwlock);

        read_count++;
        sleep(1); // 两次读取之间休息一下
    }
    printf("[Reader %ld] Finished.\n", thread_id);
    return NULL;
}

// 写者线程函数
void* writer_thread(void* arg) {
    long thread_id = (long)arg;
    int write_count = 0;

    while (write_count < 2) { // 每个写者写2次
        // 尝试获取写锁
        pthread_rwlock_wrlock(&rwlock);

        printf("\n--- [Writer %ld] WRITING START ---\n", thread_id);
        
        // 修改共享资源
        g_config.config_value += 10;
        sprintf(g_config.config_name, "Updated by Writer %ld", thread_id);
        
        printf("[Writer %ld] Wrote: New Value=%d, New Name='%s'\n", 
               thread_id, g_config.config_value, g_config.config_name);
        
        usleep(200000);

        printf("--- [Writer %ld] WRITING END ---\n\n", thread_id);

        pthread_rwlock_unlock(&rwlock);

        write_count++;
        sleep(3); // 两次写入之间休息久一点
    }
    printf("[Writer %ld] Finished.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    long i;

    printf("Main: Creating reader and writer threads...\n");

    // 创建3个读者线程
    for (i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader_thread, (void*)i);
    }

    // 创建2个写者线程
    for (i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer_thread, (void*)i);
    }

    // 等待所有线程完成
    for (i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("Main: All threads finished. Cleaning up lock.\n");
    pthread_rwlock_destroy(&rwlock);

    return 0;
}