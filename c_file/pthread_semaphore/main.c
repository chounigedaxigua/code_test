#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define PARKING_SPOTS 3 // 3个车位
#define NUM_CARS 8      // 来了8辆车

sem_t parking_spots;

void* car_thread(void* arg) {
    long car_id = (long)arg;
    int current_spots; // 用于存储剩余车位数

    printf("[Car %ld] Arrived at the parking lot. Looking for a spot...\n", car_id);

    // P操作 (wait): 尝试获取一个车位,如果没有车位，这里就会阻塞
    sem_wait(&parking_spots);

    // 成功获取到车位，现在安全地获取信号量的值
    sem_getvalue(&parking_spots, &current_spots);
    printf("[Car %ld] >>> Parked! (Remaining spots: %d)\n", car_id, current_spots);
    
    // 模拟停车（临界区）
    sleep(rand() % 3 + 1); // 随机停1到3秒

    // 离开前，再次获取一次值，因为其他进程也会获取信号量，所以它又变了
    sem_getvalue(&parking_spots, &current_spots);
    printf("[Car %ld] is about to leave. (Spots before leaving: %d)\n", car_id, current_spots);

    // V操作 (post): 离开停车场，释放一个车位
    sem_post(&parking_spots);
    
    // 释放后，再看一下值
    sem_getvalue(&parking_spots, &current_spots);
    printf("[Car %ld] <<< Left. (Spots after leaving: %d)\n", car_id, current_spots);

    return NULL;
}

int main() {
    pthread_t cars[NUM_CARS];
    long i;

    if (sem_init(&parking_spots, 0, PARKING_SPOTS) != 0) {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }

    printf("--- Parking Lot Simulation Started (Total Spots: %d) ---\n", PARKING_SPOTS);

    srand(time(NULL));
    for (i = 0; i < NUM_CARS; i++) {
        pthread_create(&cars[i], NULL, car_thread, (void*)i);
        usleep(50000);
    }

    for (i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    printf("--- All cars have been processed. ---\n");

    sem_destroy(&parking_spots);

    return 0;
}