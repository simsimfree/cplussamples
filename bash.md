# bash

## 스크립팅 문법

| 문법 | 기능 | 내용 | Sample |
| :--------: | :-------- | :-------- | :------- | 
| > | 출력 리디렉션 | stdout 을 파일로 저장 | ``` $ echo "test" > ./test.txt ``` |
| < | 입력 리디렉션 | stdin을 파일로부터 읽음 | ``` $ cat < ./test.txt ``` |
| <<< | 표준 입력 | stdin을 문자열로부터 | ``` $ cat <<< "hello $USER" ``` |
| <<EOF <br> EOF | 다중문자열 표준 입력 | stdin을 여러 문자열로부터 | ``` $ cat > ./out.txt <<EOF ``` <br> ``` hello $USER ``` <br> ``` EOF ``` |
| >> | 출력 리디렉션2 | stdout 을 파일로 이어쓰기로 저장 | ``` $ echo "test" >> ./test.txt ``` |
| \| | 파이프 | 명령의 표준출력을 다른 명령의 표준입력으로 | ```$ ls -al \| grep .txt ``` |
| $ | 변수 | 사용시는 $쓰지 않고 참조할때만 $사용 | ``` $ var= "this is var"   \n $ echo $var ``` |
| $() | 명령 결과 변수화 | 명령 실행 결과를 변수처리.  | ``` $ docker rm $(docker ps -aq) 
 $ echo $(date) ```  |
| && | 여러 명령실행 | 에러가 **없어야** 다음 명령 수행 | ```$ make && make install ``` |
| ; | 여러 명령실행 2 | 에러가 **있어도** 다음 명령 수행 | ``` $ false; echo "hello" ``` |
| ' ' | 문자열 | 변수와 명령들도 문자열 그대로 | ``` $ echo '$var' ``` |
| " " | 문자열 2 | 변수와 명령결과들은 치환 | ``` $ echo "$var" ``` |
| " ' ' " | 명령의 명령 |  | ``` $ bash -c "bin/echo Hello 'World'"``` |
| \\문자 | 특수문자입력 | 문자열에서 ', " , $와 같은 문자입력 | ``` $ echo " \$ \" " ``` |
| ${} | 변수 & 치환 | 문자열에서 변수를 출력 ($와 같음)<br> 변수의 유무로 초기화, 값 유무 초기화 | ``` $ value=  ``` <br> ``` $ value2 =${value-"test"}  # value가 없다면 "test"   ``` <br> ``` $ value2=${value:-"test"} # value가 NULL이면 "test" ``` |
| \\ | 여러줄로 명령 실행 |  | ``` $ docker run \ ``` <br> ```     -d  --name hello``` |
| {1..10} | 숫자 컬렉션 | 시작부터 끝까지 연속된 숫자 | ``` $ echo "{1..10}" ``` |
| export | 환경변수 등록 | export  변수=값 | ``` $ export VALUE="test" ``` |
| sed | 텍스트 파일의 문자열을 변경 | sed -i "s/찾을문자열/바꿀문자열/g" 파일명 | ``` $ sed -i "s/findstr/foundstr/g" test.txt ``` |
| printf | formated 출력 | 파이프로 연동하여 입력하는 기능도 가능 | ``` $ printf 80\\test\\y \| example-config ``` |



## if

```
if [값1 비교연산자 값2]; then
   수행문
fi
```

### 숫자
* -eq : ==
* -ne : !=
* -gt : >
* -ge : >=
* -lt : <
* -le : <=

### 문자열
* = : ==
* == : ==
* != : !=
* -z : NULL 문자열
* -n : non NULL 문자열


## for

```
for i in 컬렉션
do
   수행문
done

```
### 형식

* 명령의 결과
  * ex) ls   
   ```
    for i in $(ls)
    do
        echo $i
    done
   ``` 

* 범위 지정
  
   ```
    for ((i=0; i<10;i++))
    do
        echo $i
    done
   ``` 

* 변수 열거  
   ```
    NUMS=(1 2 3)
    for i in ${NUMS[@]}
    do
        echo $i
    done
   ``` 

## while
```
  while [조건]
  do
     수행문

     break
  done
```



## output redirection
stdout을 test.txt 저장 

```
echo "test" > ./test.txt
```

## input redirection
test.txt 내용을 stdin으로 사용

```
cat < ./test.txt
```


## output redirection
stdout을 test.txt 저장

```
echo "test" >> ./test.txt
```





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