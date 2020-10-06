cmake_minimum_required(VERSION 3.0.0)
project(cmakeSample VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions("-Wall -std=c++17")




#include path
include_directories(include)

#messsaging
message(WARNING "this is sample warning")

#add preprocessor
add_definitions(-DCMAKE_DEF_SAMPLE="cmake definition sample")

#use libraries

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_NO_SYSTEM_PATHS TRUE) 

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "/Users/heewonjoe/dev/libs/boost")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
endif (Boost_NO_SYSTEM_PATHS)

include_directories(${BOOST_ROOT}/include) 


find_package(Boost REQUIRED COMPONENTS random) 
if(Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS}) 
endif()


add_subdirectory(extern/googletest)
add_subdirectory(test)

add_custom_target( 
    sampleCustomTarget 
    COMMENT "sample custom Target"
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND echo "external command target"
    #DEPENDS cmakeSample
    )

link_directories (libs)

set(LIBRARY_OUTPUT_DIRECTORY libs)
set(ARCHIVE_OUTPUT_DIRECTORY libs)
add_library(
    staticSample STATIC 
    statics/static.cpp
    )


add_executable(
    cmakeSample 
    main.cpp   

    sublogics/sublogic1.cpp
    )

add_dependencies(cmakeSample sampleCustomTarget)

target_link_libraries(cmakeSample ${Boost_LIBRARIES})
target_link_libraries(cmakeSample staticSample)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
