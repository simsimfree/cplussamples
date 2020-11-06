# about docker
* 가상화 플랫폼
* OS의 가상화가 아닌 프로세스 격리만 수행
* 네트워크는 bridge로 구성되며, 성능이 중요하다면 --net=host 옵션 구성

## Image

* 컨테이너의 실행에 필요한 파일과 설정값등을 포함
* immutable
* 실행된 컨테이너의 변경사항은 컨테이너에 저장 
* like class?
* Docker Layer로 base image로부터 새로운 이미지를 구성
  * 수정된 이미지만 다운/적용하면 되기에 전체를 새로 받을 필요가 없음

## Container

* 독립된 격리된 프로세스
* like object of class?
* 사용자, apt,yum 설치등을 할 수 있음
* cpu, 메모리 제한
* 포트 포워딩, 호스트 디렉토리 공유
* 매우 빠른 생성속도
* Virtual machine같지만 아니다.
  * 격리된 프로세스로 명령을 실행만한다.

# Docker 설치


 [macOS 버전](https://hub.docker.com/editions/community/docker-ce-desktop-mac/)

# 이미 실행되어 있는 컨테이너에 연결?


# Command

```bash
$docker command [run , push, search, create, start, ...]

```

## search
[Docker Hub](https://hub.docker.com/)의 이미지 검색
    
```bash
$docker search ubuntu
```

## pull
[Docker Hub](https://hub.docker.com/)에서 이미지 받기
    
docker pull 이미지:태그

```bash
$docker pull ubuntu:10.4
```

## images
도커 이미지 목록 출력

```bash
$docker images
```

## run
도커 컨테이너를 생성한 뒤 실행

docker container run -옵션 이미지 실행할명령

```bash
$docker container run -it --name hello ubuntu /bin/bash
```

* -i : 표준입출력을 가능하게 한다
* -t : 터미널을 에뮬레이팅한다
* -d : 백그라운드 프로세스로 실행한다

도커는 명령을 실행하고 끝

i,t,d옵션 없다면 bash를 한번 실행하고 바로 종료

-it 로 실행된 컨테이너의 콘솔을 종료하면 해당명령이 종료된 시점이 되어 컨테이너도 종료

create + start와 같은 동작

## attach

실행된 컨테이너에 접속

docker container attach -옵션 컨테이너이름 or 컨테이너id

```bash
$docker attach hello
```
attach 된 콘솔을 종료한다면 컨테이너가 종료 

따라서 Ctrl+p , Ctrl+q 로 컨테이너를 정지하지 않고 detach

bash같은 쉘이 아닌 대부분의 경우 출력만을 보여지게 됨.

## ps

컨테이너 목록

ps -옵션

```bash
$docker ps -a
```

* -a : 정지된 컨테이너까지 모두 출력


## start

정지된 컨테이너를 시작

docker container start 컨테이너이름 or 컨테이너id

    ```bash
    $docker container start hello
    ```

## restart

컨테이너를 재시작

docker container restart 컨테이너이름 or 컨테이너id

    ```bash
    $docker container restart hello
    ```


## exec

실행되어 있는 컨테이너의 명령 실행

docker exec 컨테이너이름 명령 매개변수

```bash
$docker container exec hello echo 'Hello world'
```

이미 실행된 컨테이너에 npm, apt-get같은 패키지 설치와 관리등을 할 수 있음

ex) docker container exec -it nginx_hello /bin/bash 

실행되어있는 컨테이너에 bash 쉘을 실행

## stop

실행되어 있는 컨테이너 정지

```bash
$docker container stop hello
```

## rm

컨테이너 삭제

실행중인 컨테이너는 실패 (-f로 강제삭제)

```bash
$docker rm hello
```

## rmi

이미지 삭제

```bash
$docker rmi ubuntu:lastest
```

태그 없이 이미지만 지정하면 모든 이미지이름에 대응하는 이미지 삭제

## ls

like ps

ps와 달리 image에서도 사용

# Docker hub

## diff

## commit

## push

## build