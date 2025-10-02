#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory"
#define SEM_WRITE_NAME "/my_semaphore_write"
#define SEM_READ_NAME "/my_semaphore_read"
#define SHM_SIZE 1024

typedef struct {
    char message[256];
    int ready; // 1 表示数据已准备好，可以被读取
} SharedData;

#endif