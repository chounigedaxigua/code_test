#include<iostream>
#include <memory>
using namespace std;
/*
1
1 1
1 1 2
1 1 2 3 5 8
F(n) = F(n-1) + F(n-2)
*/
int haha(int n)
{
   if(n == 1 || n == 2)
   {
      return 1;
   }
   else
   {
      return haha(n-1) + haha(n-2);
   }
}
int main()
{
   // cout << haha(10) << endl;
   // 创建 unique_ptr
std::unique_ptr<int> ptr1 = std::make_unique<int>(42); // C++14 推荐

// 转移所有权（移动语义）
std::unique_ptr<int> ptr2 = std::move(ptr1); 

// 访问内容
if (ptr2) {
    std::cout << *ptr2 << std::endl; // 输出 42
}
if (ptr1) {
   std::cout << "ptr1: " << *ptr1 << std::endl; // ！！！这行代码不会被执行！！！
} else {
   std::cout << "ptr1 is now empty (nullptr)." << std::endl; // 会执行这行
}
   return 0;
}