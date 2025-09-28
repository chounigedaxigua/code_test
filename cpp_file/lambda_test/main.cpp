#include <iostream>
using namespace std;
//全局变量
int all_num = 0;
int main()
{
    //局部变量
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    cout << "lambda1:\n";
    auto lambda1 = [=] {
        //全局变量可以访问甚至修改
        all_num = 10;
        //函数体内只能使用外部变量，而无法对它们进行修改
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda1();
    cout << all_num <<endl;

    cout << "lambda2:\n";
    auto lambda2 = [&]{
        all_num = 100;
        num_1 = 10;
        num_2 = 20;
        num_3 = 30;
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda2();
    cout << all_num << endl;
    return 0;
}