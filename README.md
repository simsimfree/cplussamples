# 작업샘플

테스트 기록용 작업들

## CMake
CMake 샘플 예제들
vscode는 실행하는 수준역할만 구성

프로젝트 구성
```
cplustest                                                        
├─ sublogics                                   
│  ├─ sublogic1.cpp                            
│  └─ sublogic1.h                              
├─ CMakeLists.txt                              
├─ README.md                                   
└─ main.cpp   
```                                 


CMakeLists.txt
```

add_definitions("-Wall -std=c++17")


add_executable(output main.cpp)
```