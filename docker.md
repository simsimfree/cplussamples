# 작업샘플

docker 설치

 [macOS 버전](https://hub.docker.com/editions/community/docker-ce-desktop-mac/)


* 실행

    ```
    $docker command [run , push, search, create, start, ...]

    ```




## CMake
CMake 샘플 예제들

vscode는 실행하는 수준역할만 구성

솔루션 - 서브프로젝트 구성이 아닌 샘플

* 프로젝트 구성
  
    - build - 결과물
    - include - 프로젝트 헤더파일
    - extern - 외부 프로젝트 (gtest)
    - sublogic - 서브 디렉토리 구분 구현
    - static - 정적 라이브러리 프로젝트
    - test - testcase 프로젝트

```
cplustest                                                  
├─ build                            
│  ├─ cmakeSample_test (binary)                           
│  └─ cmakeSample (binary)                                                 
├─ include                                   
│  ├─ structures.h                            
│  └─ static.h                                                      
├─ sublogics                                   
│  ├─ sublogic1.cpp                            
│  └─ sublogic1.h                                                     
├─ statics     
│  └─ static.cpp                                                 
├─ test                                   
│  ├─ CMakeLists.txt                             
│  ├─ main.cpp                            
│  └─ test1.cpp                             
├─ CMakeLists.txt                              
├─ README.md                                   
└─ main.cpp   
```                                 
* 라이브러리
  
Boost


### CMakeLists.txt

* 변수

```
# sample variant
set(TEST_VAR "this is test value")

# add value
set(TEST_VAR ${TEST_VAR} "additional value")

set(BINARY ${CMAKE_PROJECT_NAME}_test)
add_executable(${BINARY} ${TEST_SOURCES})
```

* 파일 목록 (재귀) set
  
```
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ../test/*.h ../test/*.cpp)
```

* Macro ( predefine )
  
```
add_definitions("-Wall -std=c++17")
add_definitions(-DCMAKE_DEF_SAMPLE="cmake definition sample")

```


* Testcase
```
include(CTest)
enable_testing()

add_test(NAME ${BINARY} COMMAND ${BINARY})
```


* Include directory 
```
include_directories(${BOOST_ROOT}/include) 
```

* CMake subdirectory
include 경로에도 편입되는 듯 (gtest)
```
add_subdirectory(extern/googletest)
add_subdirectory(test)
```

* Target
```
# executable binary
add_executable(output main.cpp)

# libary
add_library(
    staticSample STATIC 
    statics/static.cpp
    )

# custom work target
add_custom_target( 
    sampleCustomTarget 
    COMMENT "sample custom Target"
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND echo "external command target"
    #DEPENDS cmakeSample
    )
```

* Target dependency
```
add_dependencies(cmakeSample sampleCustomTarget)
```

* link library
```
target_link_libraries(cmakeSample ${Boost_LIBRARIES})
target_link_libraries(cmakeSample staticSample)
```

* out binary
  
add_executable( <bin파일이름> [파일...] )
```
add_executable(output main.cpp)
``` 

* out library
add_executable( <bin파일이름> <TYPE> [파일...] )
```
add_library(
    staticSample STATIC 
    statics/static.cpp
    )
```
* extern library

    - GoogleTest
        
        clone 후 subdirectory로 편입
    - Boost
        
        용량이 크기 때문에 별도 설치

        CMake의 find_package로 필요 컴포넌트 import
        ```
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

        ```