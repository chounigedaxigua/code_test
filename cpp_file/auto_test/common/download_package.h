#ifndef DWONLOAD_PACKAGE_H_
#define DWONLOAD_PACKAGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>

void download_5g_update_package(std::string package_path);

void decompression_5G_update_package(std::string decompre_file_path);

std::string get_last_mcu_package();

std::string get_mcu_version();

std::string get_soc_version();

std::vector<std::string> pull_tsu_version_info(int time);
#endif