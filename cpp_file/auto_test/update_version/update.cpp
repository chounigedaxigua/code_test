#include <cstring>
#include <vector>
#include <stdlib.h>
#include "update.h"
#include "log.h"
#include "can.h"
int mcu_update_t::download_update_package()
{
    FILE *fp = NULL;
    char name[64] = {0};
    int i = 0;
    std::vector<std::string>bin;
    std::string ret;
    //download
    popen("/home/xhh/auto_test/temp/project_t/shell/download_mcu_package.sh","r");

    fp = popen("ls /home/xhh/auto_test/project/update_package/mcu_package/|grep .bin","r");
    if(fp == NULL)
    {
        perror("no mcu bin or popen err\n");
        return -1;
    }
    // vector <std::string>().swap(bin);
    while(fgets(name,64,fp) > (char*)0)
    {
        bin.push_back(name);
        memset(name,0,sizeof(name));
    }

    // for(auto it = bin.begin();it != bin.end();it++)
    //     std::cout<<*it;
        
    pclose(fp);
    if(false == bin.empty())
    {
        update_package_name = bin.back();
    }
    else
    {
        lpm_info(1,"No valid bin file available\n");
    }
    
    return 0;
}
int mcu_update_t::get_ver_log_file_name()
{
    FILE * fp =NULL;
    char out[128] = {0};
    std::vector<std::string> ota_mcu_file_names;
    system("rm /home/xhh/auto_test/project/tsu_version_info/unsynctime/ -rf");
    if(system("adb pull /usrdata/cx_log/log/unsynctime /home/xhh/auto_test/project/tsu_version_info") == 0)
    {
        // sleep(1);
        fp = popen("ls /home/xhh/auto_test/project/tsu_version_info/unsynctime |grep ota_mcu","r");
        if(fp == NULL)
        {
            perror("popen err");
            return -1;
        }
        else
        {
            while(fgets(out,128,fp) > (char*)0)
            {
                ota_mcu_file_names.push_back(out);
                memset(out,0,128);
            }
        }
    }
    else
    {
        lpm_info(1,"Failed to download the MCU log file\n");
        pclose(fp);
        return -1;
    }

    pclose(fp);
    ver_log_file_name = ota_mcu_file_names.back();
    return 0;
}

int mcu_update_t::get_cur_version()
{
    int timer_ = 0;
    FILE * mcu_fp = NULL;
    std::string ota_mcu_cmd;
    char cmd[256] = {0};
    char mcu_v[128] = {0};
    while(1)
    {
        if(timer_ > 30)
        {
            lpm_info(1,"Timeout was not started when getting the MCU version");
            return -1;
        }
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        ++timer_;
        sleep(3);
    }
    this->get_ver_log_file_name();
    sprintf(cmd,"cat /home/xhh/auto_test/project/tsu_version_info/unsynctime/%s |grep mcu_ver|awk -F' : ' '{print $2}'",ver_log_file_name.c_str());
    // system("adb pull /data/tsu_info/mcu_ver.txt tsu_version_info");
    

    mcu_fp = popen(cmd,"r");
    if(fgets(mcu_v,128,mcu_fp)>(char*)0)
    {
        cur_version = mcu_v;
    }
    pclose(mcu_fp);

    return 0;
}
int mcu_update_t::update()
{
    int time = 20;
	int timer_ = 0;
	std::string cmd;
    
	cmd = "/home/xhh/auto_test/temp/project_t/shell/program_bin.sh /home/xhh/auto_test/project/update_package/mcu_package/" + update_package_name;
	std::cout<<cmd<<std::endl;
	if(system(cmd.c_str()) == 0)
	{
		lpm_info(1,"Wait for the TSU restart\n");
		sleep(3);
	}
	else
	{
		lpm_info(1,"The MCU version update failed\n");
		return -1;
	}
	while(1)
    {
        if(!system("adb root"))
        {
            break;
        }
		++timer_;
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(1);
		if(timer_ >= 120)
        {
            lpm_info(1,"The timeout is not started,The MCU version update failed\n");
            return -1;
        }
    }
	timer_ = 0;
	std::cout<<"等待"<<time<<"秒读取MCU版本。。。"<<std::endl;
	sleep(time);
    this->get_cur_version();
	lpm_info(1,"The MCU version number after the update is:%s\n",cur_version.c_str());

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::string mode_update_t::get_file_name(const std::string& str)
{
    int i = 0;
    int len = str.length();
    std::string ret;

    for(;i<len;i++)
    {
        if(str[len-i] == '/')
        {
            break;
        }
    }
    return str.substr(len - i + 1,i);
}
int mode_update_t::download_update_package()
{
    char cmd[512] = {0};

    char shell_output[1024] = {0};

    std::string file_name = get_file_name(local_address);
    
    std::cout<<file_name<<std::endl;

    sprintf(cmd,"curl -u \"publictest:Publictest.1234\" -X GET %s>/home/xhh/auto_test/project/update_package/mode5g_package/%s\n",remote_address.c_str(),file_name.c_str());

    // shell_open(cmd,shell_output,1024);
    system(cmd);
}
int mode_update_t::get_update_package_path()
{
    update_package_path = "/home/xhh/auto_test/package/haha";//默认值
    return 0;
}
int mode_update_t::get_ver_log_file_name()
{

}

int mode_update_t::get_cur_version()
{
    int timer_ = 0;
    FILE * soc_fp = NULL;
    std::string ret;
    char soc_v[256] = {0};
    while(1)
    {
        if(timer_ > 30)
        {
            lpm_info(1,"Timeout was not started when getting the SOC version");
            return -1;
        }
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(3);
        ++timer_;
    }
    sleep(10);
    system("adb pull /etc/cx_version /home/xhh/auto_test/project/tsu_version_info");
    soc_fp = popen("cat /home/xhh/auto_test/project/tsu_version_info/cx_version|grep version|awk -F'=' '{print $2}'","r");
    if(fgets(soc_v,128,soc_fp)>(char*)0)
    {
        cur_version = soc_v;
    }
    pclose(soc_fp);
    return 0;
}
int mode_update_t::update()
{

    // FILE *fp1 = NULL;
    std::string cmd ;
    std::string path;
    std::string pre_tsu_version;
    std::string cur_tsu_version;

    // char a[128] = {0};
    // char b[1024] = {0};
    // int flag = 0;
    // char out[8] = {0};
    
    // fp1 = popen("find /home/xhh/auto_test/project/update_package -name update","r");
    // if(fp1 == NULL)
    // {
    //     perror("no upgrade file");
    // }
    // fgets(b,1024,fp1);
    
    // path = b;
    // path = path.substr(0,path.length() - 7);
    // std::cout<<path<<std::endl;

    // pre_tsu_version = get_soc_version();
    this->get_update_package_path();
    if(false == update_package_path.empty())
    {
        cmd = "/home/xhh/auto_test/project/shell/QFirehose -f " + update_package_path;
    }
    

    // while(1)
    // {
    //     if(!system("adb root"))
    //     {
    //         break;
    //     }
    //     std::cout<<"Wait for the mod to be online"<<std::endl;
    //     sleep(1);
    // }

    // char output[4096] = {0};

    std::cout<<cmd<<std::endl;

    FCT_mode_start();

    if(system(cmd.c_str()) == 0)
    {
        lpm_info(1,"The 5G module was updated successfully\n");
        this->get_cur_version();
        // std::cout<<"5G 模更新前版本号为:"<<pre_tsu_version<<std::endl;

        lpm_info(1,"The current version number of the 5G module is %s\n",cur_version.c_str());
    }
    else
    {
        lpm_info(1,"The 5G module update failed\n");
    }

    // pclose(fp1);
    return 0;
}