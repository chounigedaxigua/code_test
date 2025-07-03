#include <iostream>
#include <string>
#include <cstdlib>

class wifi{
public:
    std::string wifi_name;

    wifi();
    wifi(std::string _name,std::string _passwd);
    int wifi_connect(const std::string& _name,const std::string& _passwd);
private:

};
