cmake_minimum_required(VERSION 3.0.0)
project(cmakeSample VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions("-Wall -std=c++17")

# this is comment

add_executable(
    cmakeSample 
    main.cpp   

    sublogics/sublogic1.cpp
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
