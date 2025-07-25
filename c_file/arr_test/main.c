#include <stdio.h>
#include <math.h>
int main()
{
    int arr[5] = {[1] = 1,[2] = 2,[3] = 3,[4] = 4};
    *(arr+2) = 30;
    for(int i=0;i<5;i++)
    {
        printf("[%d] = %d\n",i+1,arr[i]);
    }
    return 0;
}
// int main()
// {
//     int a[3];
//     printf("a = %p,&a = %p",a,&a);
//     printf("a+1 = %p\n",a+1);
//     printf("&a+1 = %p\n",&a+1);

//     printf("*&a = %p\n",*&a);
//     printf("*&a + 1 = %p\n",*&a+1);
//     int arr[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
//     int (*p)[2] = (int(*)[2])arr;
//     for(int i=0; i<sizeof(arr)/sizeof(int[2]);i++)
//     {
//         for(int j=0; j<2; j++)
//         {
//             printf("%d\t",p[i][j]);
//         }
//     putchar(10);
// }
// }
// int main(void)
// {
//     char c = 'm';
//     char *pc = &c;
//     char **pp = &pc;
//     printf("c = %c\n",c);
//     printf("*pc = %c\n",*pc);
//     printf("&c = %p\n",&c);
//     printf("pc = %p\n",pc);
//     printf("*pp = %p\n",*pp);
//     printf("**pp = %c\n",**pp);
//     return 0;
// }
// int main()
// {
//     printf("%s\n %p\n %c\n %c\n",
//     "china","china",*"china","china"[3]);
//     return 0;
// }