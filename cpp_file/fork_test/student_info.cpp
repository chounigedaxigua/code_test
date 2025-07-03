
#include "student_info.h"
#include <iostream>

haha::haha(std::string name_,int age_)
{
    name = name_;
    age = age_;
}

haha::~haha()
{
    std::cout<<name<<" 毕业了"<<std::endl;
}

void haha::show_data()
{
    std::cout<<name<<" age is "<<age<<std::endl;
}

void haha::hello()
{
    std::cout<<"hello"<<std::endl;
}
