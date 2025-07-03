cmake_minimum_required (VERSION 2.8)
 
project (automated_testing)

include_directories(./common ./tcp ./log ./update_version ./bsp)

aux_source_directory(. SRC_LIST)
aux_source_directory(./common SRC_LIST1)
aux_source_directory(./tcp SRC_LIST2)
aux_source_directory(./log SRC_LIST3)
aux_source_directory(./update_version SRC_LIST4)
aux_source_directory(./bsp SRC_LIST5)
add_executable(${PROJECT_NAME}  ${SRC_LIST} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST3} ${SRC_LIST4} ${SRC_LIST5})


target_link_libraries(${PROJECT_NAME}
    -lcurl
    -lwiringPi
    -lpthread
    )
