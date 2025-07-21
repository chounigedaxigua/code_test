#include "say_hello.h"
#include <stdio.h>


void say_hello()
{
    printf("hello\n");
}

void test_fun()
{
    void (*fun[10])() = {say_hello};
    fun[0]();
}
