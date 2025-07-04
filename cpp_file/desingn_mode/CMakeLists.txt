cmake_minimum_required (VERSION 3.10)
 
# project (version_base_test)

# include_directories(. bsp bsp/can src)

# aux_source_directory(. SRC_LIST)


add_executable(simple_fac_mod  ${CMAKE_CURRENT_SOURCE_DIR}/simple_fac_mod.cpp)

add_executable(fac_func_mod  ${CMAKE_CURRENT_SOURCE_DIR}/fac_func_mod.cpp)

add_executable(abstrct_fac_mod  ${CMAKE_CURRENT_SOURCE_DIR}/abstract_fac_mod.cpp)


# target_link_libraries(${PROJECT_NAME}
#     -lpthread 
#     -lwiringPi
#     ${CMAKE_CURRENT_SOURCE_DIR}/bsp/can/libcontrolcan.so
#     )

 