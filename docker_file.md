# Dockerfile

도커 이미지 설정파일

dockerfile 에 설정된 내용으로 이미지를 생성

```bash
$touch Dockerfile
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
  * 기반 이미지
* MAINTAINER
  * 메인테이너 정보
* RUN
  * 명령 실행
  * 사용자 입력이 있는 명령에 -y옵션이나 쉘명령으로 대응
* VOLUMN
  * 호스트와 공유할 디렉토리
  * run 명령에서 -v 옵션으로 바인딩 -v $(pwd)/data:/data
    
    호스트의 현재 디렉토리/data 디렉토리를 컨테이너의 /data에 바인딩
* CMD
  * 컨테이너가 시작되었을때 실행할 명령
* WORKDIR
  * CMD에서 설정한 명령이 실행되는 작업디렉토리
* EXPOSE
  * 호스트와 연결할 포트번호
* COPY
  * copy

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