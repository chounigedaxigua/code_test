#include <iostream>
#include <string>
#include <vector>
typedef struct _student_info
{
    std::string name;
    int age;
    
}student_info_t;
class test_class
{
public:
    // std::string name;
    // int age;
    student_info_t my_info;
    test_class(student_info_t mi):my_info(mi)
    {

    }
    void info_out();
};
void test_class::info_out()
{
    std::cout<<"姓名: "<<this->my_info.name;
    std::cout<<std::endl;
    std::cout<<"年龄: "<<this->my_info.age;
}
int main()
{
    student_info_t xm;
    xm.age = 26;
    xm.name = "小明";
    test_class *xiaoming = new test_class(xm);
    // std::cout << xiaoming->age << xiaoming->name << std::cout;
    xiaoming->info_out();
    // std::cout<< xiaoming->age;
    // std::cout<< xiaoming->name;
}