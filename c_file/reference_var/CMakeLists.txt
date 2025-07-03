cmake_minimum_required (VERSION 3.22)

project (reference_var)

#include_directories(include)

aux_source_directory(. SRC_LIST)
#aux_source_directory(src/task SRC_LIST1)

add_executable(main ${SRC_LIST})
#target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})#连接多线程库
