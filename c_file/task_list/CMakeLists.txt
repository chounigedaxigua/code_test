# 指定 CMake 的最低版本要求（推荐 3.10 或更高）
cmake_minimum_required(VERSION 3.10)

# 定义项目名称与使用的语言（这里是 C 语言）
project(MyTaskManager C)

# 设置 C 标准（可选，推荐）
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 查找 pthread 库（多线程支持）
find_package(Threads REQUIRED)

# 添加可执行文件
add_executable(my_task_manager
    main.c
    task.c
    task.h
    task_list.c
    task_list.h
)

# 链接 pthread 库
# 注意：find_package(Threads) 会定义 Threads::Threads 目标
target_link_libraries(my_task_manager PRIVATE Threads::Threads)