# Hello world Plugin

## 목표
- plugin의 기본 코드 구조 파악

## 디렉토리 생성 
```
> mkdir ~/projects/hello_plugin
> cd ~/project
```
- [hello_world.cpp](./hello_world.cpp) 생성
- [CMakeLists.txt](./CMakeLists.txt) 생성

## build 방법 
- build 디렉토리 생성
```bash
> cd ~/projects/hello_plugin
> cd build
> cmake ..
> make
```
## 환경변수 설정
```bash
> export GAZEBO_PLUGIN_PATH=$HOME/projects/hello_plugin/build:$GAZEBO_PLUGIN_PATH 
```
## 실행 
```bash
> cd ~/projects/hello_plugin
> gzserver --verbose ./hello.world
```

## 결과
![](./result_image.png)
