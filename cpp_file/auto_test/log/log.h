#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define LOG_MAX_LEN 4096

int lpm_info(int save,char *msg,...);

#endif