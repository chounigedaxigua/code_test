#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char buf[] = "I Love Linux";

int main(int argc, char **argv)
{
    int fd = open("mmap_test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open");
        exit(0);
    }

    write(fd, buf, sizeof(buf));    
    
    struct stat filestat;
    int ret = fstat(fd, &filestat); 
    if (ret < 0)
    {
        perror("fstat");
        exit(0);
    }
/*  PROT_EXEC - 内容可以被执行
    PROT_READ - 内容可以读取
    PROT_WRITE - 内容可以修改
    PROT_NONE - 无法访问*/

/*  MAP_SHARED - 对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享
	MAP_PRIVATE -  对映射区域的写入操作会产生一个映射文件的复制，
                   即私人的“写入时复制”，对此区域作的任何修改都不会写回原来的文件内容。*/
    char * p = mmap(NULL, filestat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  //文件映射

    if (p != MAP_FAILED)
    {
        printf("map memory： %s\r\n", p);
    }
    else
    {
        perror("mmap");
        exit(0);
    }

   	ret =  munmap(p, filestat.st_size);  //解除映射
    if (ret < 0)
    {
        perror("munmap");
    }
  
    return 0;
}
