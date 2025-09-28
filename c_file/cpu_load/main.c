#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

// 假设这些是你项目中的类型定义（请根据实际定义修改）
typedef int             sal_status_t;
typedef uint16_t        sal_uint16_t;
typedef uint64_t        sal_uint64_t;
typedef pid_t           pid_t;


sal_status_t process_cpuload_get(pid_t pid, sal_uint16_t* cpu_load)
{

    char* token;
    char* saveptr;
    int  column = 0;
    double t_f = 0;
    if (cpu_load == NULL) {
        return -1;
    }

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "top -b -n 1 | grep \"^ *%d \"", pid);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return -1;
    }

    char line[1024];
    *cpu_load = 0;

    if (fgets(line, sizeof(line), fp) != NULL) {       
        token = strtok_r(line, " ", &saveptr);

        sal_uint16_t percent = 0;
        
        while (token != NULL) {
            column++;
            if (column == 9) { // 第8列通常是 %CPU
                t_f = (sal_uint16_t)atof(token);
                percent = t_f * 10;
                // percent = (sal_uint16_t)atoi(token);
                break;
            }
            token = strtok_r(NULL, " ", &saveptr);
        }

        // if (percent > 0 || column >= 8) {
            *cpu_load = percent; // 直接存入整数值，比如 5 表示 5%，或者 53 表示 5.3% 取决于 top 输出
        // }
    }

    pclose(fp);

    if (*cpu_load == 0 && column < 8) {
        return -1;
    }

    return 0;
}

int main()
{
    pid_t pid = 1676; // 替换为你想查询的进程 PID
    sal_uint16_t cpu = 0;

    sal_status_t ret = process_cpuload_get(pid, &cpu);

    if (ret == 0) {
        printf("进程 PID=%d 的 CPU 占用率为: %u%%\n", pid, cpu);
    } else {
        printf("获取进程 PID=%d 的 CPU 占用率失败\n", pid);
    }

    return 0;
}