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
| $ | 변수 | 사용시는 $쓰지 않고 참조할때만 $사용 | ``` $ var= "this is var"   ``` <br>  ``` $ echo $var ``` |
| $() | 명령 결과 변수화 | 명령 실행 결과를 변수처리.  | ``` $ docker rm $(docker ps -aq) ``` <br>``` $ echo $(date) ```  |
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

```bash
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

```bash
for i in 컬렉션
do
   수행문
done

```
### 형식

* 명령의 결과
  * ex) ls   
   ```bash
    for i in $(ls)
    do
        echo $i
    done
   ``` 

* 범위 지정
  
   ```bash
    for ((i=0; i<10;i++))
    do
        echo $i
    done
   ``` 

* 변수 열거  
   ```bash
    NUMS=(1 2 3)
    for i in ${NUMS[@]}
    do
        echo $i
    done
   ``` 

## while
```bash
  while [조건]
  do
     수행문

     break
  done
```


