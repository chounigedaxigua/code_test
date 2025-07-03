#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
 
int main(void)
{
    char buf[] = "hello world !";
	int fd;
	fd = open("lseek.txt", O_RDWR|O_CREAT);
	if(fd < 0){
		perror("open lseek.txt error");
		exit(1);
	}
 
    // write(fd,buf,sizeof(buf));
	int len = lseek(fd, 0, SEEK_END);
	if(len == -1){
		perror("lseek error");
		exit(1);
	}
	printf("file size = %d\n", len);
	close(fd);
	return 0;
}