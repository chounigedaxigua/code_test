#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAX_STUDENT_NUM 100
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
int main()
{

    for(int i = 0;i<50;i++ )
    {
        printf("%d ",i);
    }
    printf("\n 50 \n");
    for(int i = 51;i<101;i++ )
    {
        printf("%d ",i);
    }
    return 0;
}