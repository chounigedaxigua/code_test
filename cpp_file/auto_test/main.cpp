#include "tcp_connect.h"
#include "uart.h"
#include <iostream>
#include <string>
#include <string.h>
#include <filesystem>
#include <stdlib.h>
#include "download_package.h"
#include "power_manage.h"
#include "log.h"
#include "update.h"
#define UART_FLAG
#define UPDATE_5G_FLAG
#define UPDATE_MCU_FLAG
#define LOG_FLAG
#define TEST_FLAG
// #define TCP_CLIENT_FLAG
// #define TCP_SERVER_FLAG
// #define POWER_MANAGE_FLAG
volatile int exit_code = 0;

int main(int argc, const char* argv[])
{
    // int tcp_status;
    
    if(argc != 4)
    {
        std::cout << "**************参数数量错误*************" << std::endl;
        std::cout << "第一个参数如果为1,更新MCU,否则不更新MCU" << std::endl;
        std::cout << "第二个参数如果为1,更新SOC,否则不更新SOC" << std::endl;
        std::cout << "第三个参数如果为1,更新之前进行断电重启" << std::endl;
        // std::cout<<"第3个参数如果为进入低功耗时间,单位为秒"<<std::endl;
        return -1;
    }
    lpm_info(1,(char*)"update start\n");
    power_manage_init();
    // power_gpio_set(0,0,0,0);
    // sleep(10);
    power_gpio_set(1,1,1,1);
#ifdef TEST_FLAG
    
    // std::cout<<haha<<std::endl;
#endif
#ifdef UART_FLAG
    // int uart_fd = uart_init("/dev/ttyAMA10");
    int uart_fd = uart_init("/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_B001NR1L-if00-port0");
    std::thread uartThread(uartHandler,uart_fd);
    uartThread.detach(); 
#endif
#ifdef POWER_MANAGE_FLAG
    int low_power_wait_time = atoi(argv[3]);
    power_manage_init();
    // power_gpio_set(1,1,1);
    normal_power_mode();
    if(low_power_wait_time > 0)
    {
        sleep(low_power_wait_time);
        low_power_mode();
    }
    
#endif

#ifdef UPDATE_MCU_FLAG
    if(strncmp(argv[1],"1",1) == 0)
    {
        mcu_update_t* mcu = new mcu_update_t();
        std::cout << mcu->download_update_package() <<"当前最新版本是: "<< mcu->update_package_name<< std::endl;
        mcu->update();
        delete mcu;
    }
    else
    {

    }
    
#endif

#ifdef UPDATE_5G_FLAG
    // download_5g_update_package("http://192.168.52.188:8082/artifactory/dailybuild-ag591eeu/main/202408291608/G26.0.0.100.000-66d02e8a.tar.gz");

    // decompression_5G_update_package("http://192.168.52.188:8082/artifactory/dailybuild-ag591eeu/main/202408291608/G26.0.0.100.000-66d02e8a.tar.gz");
    if(strncmp(argv[2],"1",1) == 0)
    {
        if(strncmp(argv[3],"1",1) == 0)
        {
            power_gpio_set(0,0,0,0);
        
            sleep(3);
            power_gpio_set(1,1,1,1);
            digitalWrite(GPIO_PROGRAM_5G,HIGH);
            sleep(3);
            lpm_info(1,(char*)"断电重启中......,等待TSU启动\n");
            sleep(2);
            digitalWrite(GPIO_PROGRAM_5G,LOW);
            sleep(20);
        }
        
        mode_update_t *soc = new mode_update_t();
        soc->update();
        delete soc;    
    }
    else
    {

    }
#endif
    exit_code = 1;
    // lpm_info(1,(char*)"Upgrade completed\n");
    while(0)
    {
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(3);
    }

#ifdef TCP_CLIENT_FLAG
    /* */
    int server_sock = connect_to_server("192.168.20.2",6666);
    std::thread clientThread(recive_handle, server_sock);
    clientThread.detach();

    send(server_sock,"connect success......",strlen("connect success......"),0);
#endif

#ifdef TCP_SERVER_FLAG
    int server_sockfd = socket(PF_INET,SOCK_STREAM,0);
    if(server_sockfd == -1)
	{
        close(server_sockfd);
        perror("socket error!");
    }
    struct sockaddr_in server_addr;

    tcp_server_init(server_sockfd,&server_addr,port);

    printf("Listen on port %d\n", port);
    while(1)
	{
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);
        
        std::thread tcpThread(requestHandling, client_sockfd, client_addr);
        tcpThread.detach(); 
    }
    close(server_sockfd);
#endif
   for(;;)
    {
        if(exit_code != 0)
        {
            break;
        }
    }

    return 0;
}

