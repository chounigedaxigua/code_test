#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <thread>
#include "controlcan.h"

#include <ctime>
#include <cstdlib>
#include "unistd.h"
#include "log.h"
VCI_BOARD_INFO pInfo;//用来获取设备信息。
int count=0;//数据列表中，用来存储列表序号。
VCI_BOARD_INFO pInfo1 [50];
int num=0;

void can_init()
{
    // num=VCI_FindUsbDevice2(pInfo1);
}


static void FCT_mode_hander()
{
    int counter = 0;
    while(1)
    {
        ++counter;

        system("cansend can0 1610FF91#00");
        usleep(300000);
        if(counter == 10)
        {
            counter = 0;
            // printf("FCT\n");
        }
    }
    
}

void FCT_mode_start()
{
#if 1
        if(system("sudo ip link set can0 down") != 0)
        {
            lpm_info(1,"can0 not close\n");
            
        }
        if(system("sudo ip link set can0 up type can bitrate 125000") != 0)
        {
            lpm_info(1,"can0 not open\n");
        }
        if(system("sudo ifconfig can0 txqueuelen 65536") != 0)
        {
            
        }
#endif
    std::thread FCT_mode_thread(FCT_mode_hander);
    FCT_mode_thread.detach(); 
}
