# Dockerfile

도커 이미지 설정파일

dockerfile 에 설정된 내용으로 이미지를 생성

```bash
$touch Dockerfile
```

## .dockerignore
 
### 도커 컨텍스트

Dockerfile 과 같은 디렉토리의 모든 파일은 컨텍스트를 이룬다.

이미지 생성시 포함됨으로 무시하는 조건이 필요

```.dockerignore
*.cpp
.git
.svn
```

## DSL

```dockerfile
FROM ubuntu:14.04
MAINTAINER Foo Bar <foo@bar.com>

RUN apt-get update
RUN apt-get install -y nginx
RUN echo "\ndaemon off;" >> /etc/nginx/nginx.conf
RUN chown -R www-data:www-data /var/lib/nginx
EXPOSE 80 
EXPOSE 443 

WORKDIR /etc/nginx

CMD ["nginx"]
COPY app.js

```

* FROM 
  * 기반 이미지. 항상 첫번째. 
* MAINTAINER (생략가능)
  * 이미지 생성자 정보
* RUN
  * 명령 실행
  * 사용자 입력이 있는 명령에 -y옵션이나 쉘명령으로 대응
  * 이미지의 히스토리에 기록
  * 실행 결과는 캐시되어 다음빌드때 사용. 
    * 캐시를 사용하지 않으려면 docker build --no-cache 옵션
  * /bin/sh 
    * RUN 명령
        ```dockerfile
        RUN echo 'hello'
        ```
  * 직접 실행 (스크립트 문법사용불가)
    * RUN ["실행파일", "매개변수1","매개변수2",...]
        ```dockerfile
        RUN ["echo", 'hello']
        ```
* VOLUMN
  * 호스트와 공유할 디렉토리를 위해 컨테이너에 저장하지않고 호스트에 저장
  * run 명령에서 -v 옵션으로 바인딩 -v $(pwd)/data:/data
    
    호스트의 현재 디렉토리/data 디렉토리를 컨테이너의 /data에 바인딩
        ```dockerfile
        VOLUMN ["/data", '/var/log/hello']
        ```
* CMD
  * 컨테이너가 시작되었을때 실행할 명령
  * 한번만 사용
  * docker run에서 실행 명령을 명시할 경우 무시됨
  * /bin/sh
    *  CMD 명령
        ```dockerfile
        CMD touch /home/hello/hello.txt
        ```
 * 직접 실행
    *  CMD ["실행파일", "매개변수1","매개변수2",...]
        ```dockerfile
        CMD ["nginx", "-g", "daemon off;"]
        ```
 * ENTRYPOINT 사용
    *  매개변수만 사용. CMD독자적으로 실행할 수 없음
        ```dockerfile
        ENTRYPOINT ["nginx"]
        CMD ["-g", "daemon off;"]
        ```

 * ENTRYPOINT 
    * CMD와 거의 같은 기능
    * 파라미터와 실행 체계도 같지만, CMD와 같이 사용할 경우 CMD는 파라미터로만 사용
    * docker run 에서 CMD 명령은 역시 파라미터로 사용 (entrypoint의 파라미터 뒤)
    * docker run --entrypoint="명령" 으로 무시
* EXPOSE
  * 호스트와 연결할 포트번호
  * 외부 노출되지 않음
    * 외부 노출을 위해서는 docker run -p 노출포트:연결포트
* ENV
  * 환경변수
  * RUN, CMD, ENTRYPOINT에 적용
  * docker run -e 환경변수=값 으로 동일하게 적용
    ```dockerfile
    ENV PATH /go/bin:$PATH
    ENV AWS_BUCKETS exambucket
    ```
    이것은

    ```bash
    docker run -e PATH="/go/bin:$PATH" -e AWS_BUCKETS="exambucket" example
    ```
    과 같음
* ADD
  * 파일을 이미지에 추가
  * 파일의 경로는 컨텍스트 범위에서만 유효하며 절대경로 및 바깥범주의 파일은 사용할 수 없음
  * 대상 경로는 절대경로이며 마지막이 / 일경우 디렉토리가 생성되고 복사
  * 소유자, 그룹 0으로 설정되고 권한은 파일의 권한을 따르게됨. URL파일은 600
    ```dockerfile
    ADD ../hello.txt /home/hello (x)
    ADD /home/hello.txt /home/hello (x)
    ADD txts/*.txt /home/hello (o)
    ADD http://example.com/hello.txt /home/hello (o)
    ADD hello.tar.gz /home/extracted (o:압축해제 후 tar가 풀리며 복사)
    ADD http://example.com/hello.tar.gz /home/extracted (o: 압축해제 후 tar를 복사)

    ```
  * URL의 파일은 압축해제만 하고 tar해제는 하지않기 때문에 `RUN` curl을 사용  
* COPY
  * ADD와 비슷하지만 압축해제 하지 않고 그대로 복사
  * URL경로 불가능

* USER
  * 명령(`RUN`,`CMD`,`ENTRYPOINT`)에 적용될 사용자 설정
  
    ```dockerfile
    USER nobody
    RUN touch /tmp/hello.txt

    USER root
    RUN touch /hello.txt
    ENTRYPOINT /hello-entrypoint.sh
    ``` 

* WORKDIR
  * 명령(`RUN`,`CMD`,`ENTRYPOINT`)이 실행되는 작업디렉토리
  * 상대 경로가 가능하며 동작 정의는 cd 와 같다
    ```dockerfile
    WORKDIR /tmp
    RUN touch hello.txt

    WORKDIR /
    RUN touch /hello.txt
    ENTRYPOINT /hello-entrypoint.sh
    ``` 
* ONBUILD
  * 현재 이미지를 기반으로 자식 이미지를 빌드할때 호출되는 트리거
  * `ONBUILD dockfile명령 명령매개변수`
    * FROM , MAINTAINER, ONBUILD 를 제외한 모든 명령
  * 자신이 빌드될때 호출되지 않음
  * 손자 이미지 빌드시에도 호출되지 않음 (상속x)
## build

docker build 옵션 dockerfile경로
```bash
$docker build --tag hello_nginx:0.1 .
```

# run
```bash
$docker run --name hello-nginx -d -p 8080:80 -v $(pwd)/data:/data hello_nginx:0.1 
```

* -d: 컨테이너를 백그라운드로 실행
* -p 호스트포트:컨테이너포트 
  * 호스트의 포트 (http://localhost:8080)로 접속하면 컨테이너의 포트 (http://localhost:80)으로 접속
* -v 호스트의 디렉토리:컨테이너의 공유디렉토리
  * 호스트의 디렉토리를 컨테이너 디렉토리와 바인딩
  * 호스트 디렉토리에 파일을 넣으면 컨테이너에서 접근가능
  * 절대경로(pwd) 사용