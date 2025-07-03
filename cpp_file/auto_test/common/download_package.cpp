#include "download_package.h"

static std::string get_file_name(const std::string& str)
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

static void download_mcu_update_package()
{

    system("/home/xhh/auto_test/temp/project_t/shell/download_mcu_package.sh");

}
static std::string get_ota_mcu_log_name()
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

    pclose(fp);
    return ota_mcu_file_names.back();
}
std::string get_mcu_version()
{
    FILE * mcu_fp = NULL;
    std::string ret;
    std::string ota_mcu_log_name;
    std::string ota_mcu_cmd;
    char cmd[256] = {0};
    char mcu_v[128] = {0};
    while(1)
    {
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(3);
    }
    // sleep(15);
    ota_mcu_log_name =  get_ota_mcu_log_name();
    ota_mcu_log_name = ota_mcu_log_name.substr(0, ota_mcu_log_name.length() - 1);
    sprintf(cmd,"cat /home/xhh/auto_test/project/tsu_version_info/unsynctime/%s |grep mcu_ver|awk -F' : ' '{print $2}'",ota_mcu_log_name.c_str());
    // system("adb pull /data/tsu_info/mcu_ver.txt tsu_version_info");
    

    mcu_fp = popen(cmd,"r");
    if(fgets(mcu_v,128,mcu_fp)>(char*)0)
    {
        ret = mcu_v;
    }
    pclose(mcu_fp);
    return ret;
}
std::string get_soc_version()
{
    FILE * soc_fp = NULL;
    std::string ret;
    char soc_v[128] = {0};
    while(1)
    {
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(3);
    }
    sleep(10);
    system("adb pull /etc/cx_version tsu_version_info");
    soc_fp = popen("cat /home/xhh/auto_test/project/tsu_version_info/cx_version|grep version|awk -F'=' '{print $2}'","r");
    if(fgets(soc_v,128,soc_fp)>(char*)0)
    {
        ret = soc_v;
    }
    pclose(soc_fp);
    return ret;
}
std::vector<std::string> pull_tsu_version_info(int time)
{
    FILE * mcu_fp = NULL;
    FILE * soc_fp = NULL;
    std::vector<std::string> ret;
    std::string ota_mcu_log_name;
    std::string ota_mcu_cmd;
    char cmd[256] = {0};
    char mcu_v[128] = {0};
    char soc_v[128] = {0};
    while(1)
    {
        if(!system("adb root"))
        {
            break;
        }
        std::cout<<"Wait for the mod to be online"<<std::endl;
        sleep(3);
    }
    sleep(time);
    ota_mcu_log_name =  get_ota_mcu_log_name();
    ota_mcu_log_name = ota_mcu_log_name.substr(0, ota_mcu_log_name.length() - 1);
    sprintf(cmd,"cat /home/xhh/auto_test/project/tsu_version_info/unsynctime/%s |grep mcu_ver|awk -F' : ' '{print $2}'",ota_mcu_log_name.c_str());
    // system("adb pull /data/tsu_info/mcu_ver.txt tsu_version_info");
    system("adb pull /etc/cx_version tsu_version_info");

    mcu_fp = popen(cmd,"r");
    if(fgets(mcu_v,128,mcu_fp)>(char*)0)
    {
        ret.push_back(mcu_v);
    }

    soc_fp = popen("cat /home/xhh/auto_test/project/tsu_version_info/cx_version|grep version|awk -F'=' '{print $2}'","r");
    if(fgets(soc_v,128,soc_fp)>(char*)0)
    {
        ret.push_back(soc_v);
    }
    pclose(mcu_fp);
    pclose(soc_fp);

    return ret;
}

void download_5g_update_package(std::string package_path)
{
    char cmd[512] = {0};

    char shell_output[1024] = {0};

    std::string file_name = get_file_name(package_path);

    std::cout<<file_name<<std::endl;

    sprintf(cmd,"curl -u \"publictest:Publictest.1234\" -X GET %s>/home/xhh/auto_test/project/update_package/mode5g_package/%s\n",package_path.c_str(),file_name.c_str());

    // shell_open(cmd,shell_output,1024);
    system(cmd);

}

void decompression_5G_update_package(std::string package_path)
{
    char cmd[512] = {0};

    char shell_output[4096] = {0};

    std::string decompre_file_name = get_file_name(package_path);

    sprintf(cmd,"tar -zxvf /home/xhh/auto_test/project/update_package/mode5g_package/%s -C /home/xhh/auto_test/project/update_package/mode5g_package",decompre_file_name.c_str());
 
    std::cout<< cmd <<std::endl;

    // shell_open(cmd,shell_output,4096);
    system(cmd);

    std::cout<< shell_output <<std::endl;

}
//curl -u "publictest:Publictest.1234" -X GET http://192.168.52.188:8082/artifactory/dailybuild-ag591eeu/main/202408252322/main_202408252322.tar.gz>/home/xhh/haha.tar.gz


std::string get_last_mcu_package()
{
    FILE *fp = NULL;
    char name[64] = {0};
    int i = 0;
    std::vector<std::string>bin;
    std::string ret;
    
    download_mcu_update_package();

    fp = popen("ls /home/xhh/auto_test/project/update_package/mcu_package/|grep .bin","r");
    if(fp == NULL)
    {
        perror("no mcu bin or popen err\n");
    }
    //vector <std::string>().swap(bin);
    while(fgets(name,64,fp) > (char*)0)
    {
        bin.push_back(name);
        memset(name,0,sizeof(name));
    }

    for(auto it = bin.begin();it != bin.end();it++)
        std::cout<<*it;
        
    pclose(fp);

    return bin.back();
}