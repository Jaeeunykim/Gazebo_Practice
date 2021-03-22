cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(motor_control SHARED motor_control.cpp)
target_link_libraries(motor_control ${GAZEBO_LIBRARIES})

add_executable(prop_start motor_start.cpp)
target_link_libraries(prop_start ${GAZEBO_LIBRARIES})

add_executable(left_elevon_start left_elevon_start.cpp)
target_link_libraries(left_elevon_start ${GAZEBO_LIBRARIES})


add_executable(right_elevon_start right_elevon_start.cpp)
target_link_libraries(right_elevon_start ${GAZEBO_LIBRARIES})