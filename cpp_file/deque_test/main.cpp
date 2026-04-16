#include <iostream>
#include <deque>
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

    deque<function<void()>> print_cars;
    
    deque<int> dq;
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