#include "uart.h"
#include <string.h>
#include <pthread.h>
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int uart_init(std::string dev)
{
    int uart_fd = -1;
    if((uart_fd=serialOpen(dev.c_str(),38400))<0)
    { 
      std::cout <<"Serial port initialization failed\n"<<std::endl;
      return -1;
    }
    // std::cout<<"uart OK........."<<std::endl;
    std::cout << "uart_fd = " << uart_fd << std::endl;
    // serialPrintf(uart_fd, "uart OK.........");
    return uart_fd;
}

float get_current(char *current_char)
{
  float z = 0;
  float x = 0;
  float t = 0;
  // std::string curent = current_char;
  // pthread_mutex_lock(&mut);
  
  for(int i = 0;i < 4;i++)
  {
    if(current_char[i] < '0' || current_char[i] > '9')
    {
      // pthread_mutex_unlock(&mut);
      return -1;
    }
    else
    {
      t = current_char[i] - 48;
      for(int j = 1;j < 4 - i;j++)
      {
        t = t  * 10;
      }
    }
    z += t;
  }
  for(int i = 4;i < 7;i++)
  {
    if(current_char[i] < '0' || current_char[i] > '9')
    {
      // pthread_mutex_unlock(&mut);
      return -1;
    }
    else
    {
      t = current_char[i] - 48;
      for(int j = 0;j < i - 3;j++)
      {
        t *= 0.1;
      }
    }
    x += t;
  }
  // pthread_mutex_unlock(&mut);
  return z + x;
  
}

void uartHandler(int uart_fd)
{
    char buff[32] = {0};
    float current = 0;
    while(1)
    {
       int sz = serialDataAvail(uart_fd); 
       
       if(sz > 0)
       {
          for(int i = 0; i < sz; i++)
          {
              int c = serialGetchar(uart_fd);
              if(c != -1)
                  buff[i] = c;  
          }
          // std::cout<<buff;
          current = get_current(buff);
          if(current >= 0)
          {
            // std::cout << current << " mA\n";
          }
          // serialPrintf(uart_fd, buff);
          memset(buff,0,32);
       }
       else
       {
         usleep(50000); // 必要的延时50ms
       }
    }
    // for (;;)
    // {
    //     if (serialDataAvail(uart_fd) > 0)
    //     {
    //         putchar(serialGetchar(uart_fd));
    //                     fflush (stdout) ;    
    //     }
    // }

    serialClose(uart_fd);
    printf("close serial.\n");
}