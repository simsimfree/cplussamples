# Docker Repositories
* 도커 이미지 저장소
* 기본적으론 Docker Hub를 사용
  

# Local Repository

docker의 실행을 --insecure-registry 옵션으로 실행

/etc/init.d/docker

DOCKER_OPTS=--insecure-reigstry localhost:8888 이라는데....

최신 & macOS의 경우 docker configuration의 daemon.json 항목의 속성을 추가하면됨

```json
{
  "insecure-reigstries": ["localhost:8888"],
}
```


## docker registry server

로컬 이미지를 저장하기 위한 서버도 docker이미지로 제공

```bash
$docker pull registry:latest
```

registry 컨테이너 실행

```bash
$docker run -d -p 8888:8888 --name my-registry \
        -v /tmp/registry:/tmpregistry \
        registry
```

이미지 파일은 호스트의 /tmp/registry에 저장

### S3

docker registry를 실행할때 S3 정보를 구성하면 S3에 저장

속성은 -e 옵션으로 지정

```bash
$docker run -d -p 8888:8888 --name s3-registry \
        -e SETTINGS_FLAVOR=s3 \
        -e AWS_BUCKETS=exambucket \
        -e STORAGE_PATH=/dockerregistry \
        -e AWS_KEY=AKIAWSSAMPLEKEY  \
        -e AWS_SECRET=sAWSSAMPLESECRET  \
        registry

```
* SETTINGS_FLAVOR: 이미지 저장 방법
* AWS_BUCKETS: S3 버킷
* STORAGE_PATH: 저장 경로
* AWS_KEY: 액세스키
* AWS_SECRET: 시크릿 키


## docker push

```bash
$docker tag hello:0.1 localhost:8888/hello:0.1
$docker push localhost:8888/hello:0.1

```

도커의 이미지 태그를 생성
docker tag 이미지:태그 도커저장소url/이미지:태그


## pull 수정  push

도커 컨테이너 수정 후 태그로 새로운 이미지를 생성한 후 저장소에 push


# TODO
- (저장소에 올라갈 수정된)컨테이너와 (로컬)컨테이너의 비교?
- pull 후 수정 후 새로운 컨테이너, 따라서 작업시마다 컨테이너 태그가 쌓여가는데?
  - 어떻게 하는가? latest 적용?
- 로컬에서 작업한 이미지를 허브에 올릴때
- 충돌 대응 (CI관리자의 역할)
- base 이미지들이 업데이트 되었을때?
- 실무응용 로컬저장소와 stage
- latest 관리
- 볼륨 컨테이너를 여러개 등록할 수 있는가?
- run의 옵션들을 정리
- 스크래치 이미지는 활용되는가? 어디까지 가능한가? (시스템콜, 네트워크..)
  - --privileged로 해결?
- 배포 docker 에서 docker실행


# link

컨테이너와 컨테이너의 연결

포트포워딩을 통한 외부 연결이 아닌 컨테이너로 직접 연결

docker run --link 옵션으로 수행

### sample
몽고 db 컨테이너 실행
```bash
$docker run --name db -d mongo
```

웹 컨테이너를 db컨테이너와 연결하며 실행

```bash
$docker run --name web -p 80:80 --link db:db nginx
```

ps 명령으로 조회시

NAMES에 db, web/db로 나타난다

web 컨테이너에서 db 컨테이너로 접속이 가능

web컨테이너에서 db컨테이너로 접속
```
mongodb://db:27017/exampledb
```

`컨테이너에서 다른 컨테이너로 접속할때 <컨테이너별칭>:<포트>`

컨테이너의  hosts 파일에 별칭이 선언되어있다.
```bash
$cat `docker inspect -f "{{ .HostsPath }}" web`
```
macOS에서는 vm에서 돌아가기 때문에 안됨
 
# ambassador pattern

앰버서더 컨테이너를 이용하여 컨테이너와 `다른 서버`의 컨테이너를 연결할때

컨테이너의 목적주소를 고정<앰버서더 컨테이너로만 접근>하고 바뀔 수 있는 목적주소는 앰버서더 컨테이너에서 설정