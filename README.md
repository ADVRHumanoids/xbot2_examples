# xbot2_examples
### Examples for the XBot2.0 middleware

This repository containes commented examples of use for the **XBot2.0** real-time middleware for robotics.

## Contents

- [Simulating a robotic system with Gazebo](docs/gazebo-sim)
- Writing a simple control module as an *XBot2 Plugin*
- Inter-plugin communication (data streaming, rpc-like)
- Using ROS from a real-time plugin
- Adding a custom device

## How to build

Standard CMake workflow

 - `mkdir build && cd build`
 - `ccmake <path-to-repo>`
 - select a build type and an install folder (must be visible to the dynamic linker), type `c` and then `g`
 - `make -j install`
