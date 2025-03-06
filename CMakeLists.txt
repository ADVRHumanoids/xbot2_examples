cmake_minimum_required(VERSION 3.8)
project(xbot2_examples)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ament_cmake which is required for ROS 2
find_package(ament_cmake REQUIRED)

option(XBOT2_ENABLE_XENO OFF "Compile against xenomai")
option(XBOT2_EXAMPLES_WITH_GZ ON "Compile gazebo examples")

add_subdirectory(src/clock)
add_subdirectory(src/malloc_example)
add_subdirectory(src/gcomp_example)
add_subdirectory(src/homing_example)
add_subdirectory(src/ros_from_rt)
add_subdirectory(src/talker_listener)
add_subdirectory(src/client_server)
if(${XBOT2_EXAMPLES_WITH_GZ})
    add_subdirectory(src/device)
endif()
add_subdirectory(src/joint_impedance)
add_subdirectory(src/impedance_setpoint)
add_subdirectory(src/ros_api)

ament_package()