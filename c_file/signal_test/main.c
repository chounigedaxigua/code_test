// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>

// // 全局变量，指示程序是否应退出
// volatile sig_atomic_t stop = 0;

// void handle_sigint(int sig) {
//     printf("Caught signal %d\n", sig);
//     stop = 1; // 设置退出标志
// }

// int main() {
//     // 将 SIGINT 信号的处理程序设置为 handle_sigint 函数
//     signal(SIGINT, handle_sigint);

//     while (!stop) { // 检查是否应退出
//         printf("Running...\n");
//         sleep(1);
//     }

//     printf("Exiting...\n");

//     return 0;
// }
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void signal_catchfunc(int);


int main() {

   int ret;

   signal(SIGINT, signal_catchfunc);


   printf("开始生成一个信号\n");
   ret = raise(SIGINT);
   if (ret != 0) {
      printf("错误，不能生成SIGINT信号\n");
      exit(0);
}

printf("退出....\n");
   return 0;
}

void signal_catchfunc(int signal) {
   printf("捕获信号\n");
}