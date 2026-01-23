#include<iostream>
#include <memory>
using namespace std;

int main()
{

/*
    1.unique_ptr
*   **特点**：同一时间只能有一个 `unique_ptr` 指向对象，不可复制但可移动。移动操作确保了动态分配的内存始终只有一个明确的所有者，从而防止了内存泄漏和二次释放
*   **适用场景**：管理单一所有权的资源（如工厂模式返回对象）。
*/
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

/*
    2.shared_ptr
*   **特点**：允许多个 `shared_ptr` 指向同一对象，通过引用计数实现自动内存管理。当所有 `shared_ptr` 都失效时，对象才会被释放。
*   **适用场景**：管理共享所有权的资源（如容器中的元素）。
*/
   std::shared_ptr<int> ptr3 = std::make_shared<int>(43);
   std::shared_ptr<int> ptr4 = ptr3;
   if (ptr3) {
      std::cout << "ptr3: " << *ptr3 << std::endl;
   }
   if (ptr4) {
      std::cout << "ptr4: " << *ptr4 << std::endl;
   }

/*
    3.weak_ptr
*   **特点**：不参与引用计数，只观察 `shared_ptr` 的生命周期。用于解决循环引用问题（如树形结构）。
*   **适用场景**：管理非所有权的资源（如缓存）。
*/
    std::shared_ptr<int> sptr = std::make_shared<int>(200);
    std::weak_ptr<int> wptr = sptr; // 创建 weak_ptr

    // 检查对象是否存在并访问
    if (auto tmp = wptr.lock()) {
        std::cout << *tmp << std::endl; // 输出 200
    }

/*
    4.reset
*   **特点**：释放当前管理的对象，并重新管理新的对象。reset 方法接受一个可选参数，可以是一个新对象的指针，也可以是 nullptr。
*   **适用场景**：管理动态分配的资源（如内存、文件句柄）。
    */
    ptr1.reset();
    ptr2.reset();
    // ptr3.reset();
    // 也可以 reset 一个新的指针（会先释放旧的，再管理新的）
    ptr2.reset(new int(200));
    std::cout << "Value after reset with new object: " << *ptr2 << std::endl; // 输出 200
    ptr4.reset();
    sptr.reset(); // 释放 shared_ptr
    if (wptr.expired()) {
        std::cout << "weak_ptr is expired." << std::endl;
    }
   return 0;
}
