cmake_minimum_required (VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

add_executable(simple_fac_mod  ${CMAKE_CURRENT_SOURCE_DIR}/../src/simple_fac_mod.cpp)

add_executable(fac_func_mod  ${CMAKE_CURRENT_SOURCE_DIR}/../src/fac_func_mod.cpp)

add_executable(abstrct_fac_mod  ${CMAKE_CURRENT_SOURCE_DIR}/../src/abstract_fac_mod.cpp)



 