#pragma once
#include <string>
#include <iostream>
#include <unistd.h> 
enum device_t{MCU,MODE};

class update_t{
public:
    // virtual ~update_t();

    
    virtual int download_update_package() = 0;
    virtual int update() = 0;
    virtual int get_ver_log_file_name() = 0;
    
    virtual int get_cur_version() = 0;

    std::string pre_version;
    std::string cur_version;
    std::string ver_log_file_name;
    std::string remote_address;
    std::string local_address;
    
};

class mcu_update_t:public update_t{
public:
    
    virtual int download_update_package();
    virtual int update();
    virtual int get_ver_log_file_name();
    virtual int get_cur_version();
    int get_update_package_name();
    
    std::string update_package_name;
};

class mode_update_t:public update_t{
public:

    virtual int download_update_package();
    virtual int update();
    virtual int get_ver_log_file_name();
    virtual int get_cur_version();

    std::string get_file_name(const std::string& str);
    int get_update_package_path();
    std::string update_package_path;
};

