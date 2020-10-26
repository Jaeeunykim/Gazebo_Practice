# Subak Quad만들기

## 목표
Custom 비행체가 있는 경우 PX4 SITL에 추가하여 사용하기


## 결과 
```bash
> make px4_sitl gazebo_subak
```
![](./subak_quad.png)

## Subak Model 추가하기 
- 위치 : Firmware/Tools/models
- 추가 : solo 디렉터리 복사하여 subak으로 변경 
  
## init.d-posix 
- 위치 : Firmware/ROMFS/px4fmu_common/init.d-posix/
- 추가 :  1014_solo 복사하여 1114_subak으로 변경 
  
## Build target 추가 
- 위치 : Firmware/platforms/posix/cmake/sitl_target.cmake
- 수정 : set(models ...)에 subak 추가 
