#include "wifi.h"

wifi::wifi()
{

}

wifi::wifi(std::string _name,std::string _passwd){
    
}

int wifi::wifi_connect(const std::string& _name,const std::string& _passwd){
    std::string command = "nmcli con up id '" + _name + "' ";
    
    if (!_passwd.empty()) {
        command += "pp '" + _passwd + "'";
    }
    std::system(command.c_str());

    return 0;
}