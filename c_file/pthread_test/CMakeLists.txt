cmake_minimum_required (VERSION 3.22)

project (pthread)

find_package(Threads)

include_directories(include)

aux_source_directory(src SRC_LIST)
aux_source_directory(src/task SRC_LIST1)

add_executable(main ${SRC_LIST} ${SRC_LIST1})
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})#连接多线程库