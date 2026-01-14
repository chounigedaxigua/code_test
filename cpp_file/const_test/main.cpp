#include <iostream>
using namespace std;
int var = 100;
void func(){
    cout<<" func "<<endl;
}
int main()
{
    int var = 200;
    cout<<"main var= "<<var<<endl;
    cout<<"global var = "<<::var<<endl;
    func();
    ::func();
    return 0;
    }