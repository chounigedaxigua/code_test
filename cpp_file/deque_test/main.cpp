#include <iostream>
#include <deque>
#include <list>
#include <functional>
#include <unistd.h>
using namespace std;
class car
{
public:
    car(string name, string color) : m_name(name), color(color) {}
    ~car() {}
    string m_name;
    string color;
    void print() {
        cout << "name: " << m_name << ", color: " << color << endl;
        sleep(1);
    }
};



int main() {

    list<function<void()>> print_cars;
    // deque<function<void()>> print_cars;//也可以使用deque，但是list更合适，因为list的插入和删除更高效，不需要像deque那样移动元素
    car car1("car1", "red");
    car car2("car2", "blue");
    car car3("car3", "green");
    print_cars.push_back([&car1](){car1.print();});
    print_cars.push_back([&car2](){car2.print();});
    print_cars.push_back([&car3](){car3.print();});
    for (auto it = print_cars.begin(); it != print_cars.end(); ++it) {
        (*it)();
    }
    
    return 0;
}