#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAX_STUDENT_NUM 100

enum arithmetic{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    ARI_MAX
};
typedef struct  _name_t
{
    int max_len;
    char *data;
}name_t;

typedef struct _student_t
{
    int age;
    name_t name;
}student_t;
typedef struct _class_t
{
    int class_num;
    int student_num;
    student_t student[MAX_STUDENT_NUM];
}class_t;
int student_init(student_t *student,int age,char *name)
{
    student->age = age;
    assert(name != NULL);
    student->name.data = name; 
}

int add(int a, int b){return a + b;}
int subtract(int a, int b){return a - b;}
int multiply(int a, int b){return a*b;}
int divide(int a, int b){return a/b;};

int main()
{
    int a = 10, b = 5;
    int (*haha[ARI_MAX])(int ,int) = {add, subtract, multiply, divide};
    printf("a = %d, s = %d, m = %d, d = %d\n",haha[ADD](a,b),haha[SUBTRACT](a,b),haha[MULTIPLY](a,b),haha[DIVIDE](a,b));
    return 0; 
}