cmake_minimum_required (VERSION 3.22)

project (pthread)

include_directories(include)

aux_source_directory(. SRC_LIST)
aux_source_directory(task SRC_LIST1)

add_executable(main ${SRC_LIST} ${SRC_LIST1})

