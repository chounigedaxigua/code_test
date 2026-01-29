#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// 共享数据
int buffer[BUFFER_SIZE];
int count = 0; // 当前缓冲区中的数据个数

// 同步原语
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER; // 给生产者用的条件变量（缓冲区满）
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER; // 给消费者用的条件变量（缓冲区空）

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; ++i) { // 生产10个物品
        item = rand() % 100;

        pthread_mutex_lock(&mutex);

        // 如果缓冲区满了，生产者等待
        while (count == BUFFER_SIZE) {
            printf("Producer: Buffer is full, waiting...\n");
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // 生产物品
        buffer[count] = item;
        count++;
        printf("Producer: Produced %d, count=%d\n", item, count);

        // 通知消费者现在有数据了
        pthread_cond_signal(&cond_consumer);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; ++i) { // 消费10个物品
        pthread_mutex_lock(&mutex);

        // 如果缓冲区空了，消费者等待
        while (count == 0) {
            printf("\tConsumer: Buffer is empty, waiting...\n");
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // 消费物品
        count--;
        item = buffer[count];
        printf("\tConsumer: Consumed %d, count=%d\n", item, count);

        // 通知生产者现在有空间了
        pthread_cond_signal(&cond_producer);

        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}