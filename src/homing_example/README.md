# Implementing a control plugin

[Back to home](../../README.md)

This example is related to the implementation and execution of a simple control plugin, specifically a *homing* plugin which brings the robot to a given joint space position, within a specified time.

## Steps
A short outline of the required steps follows. Please refer to the inline comments inside the [header](homing_example.h) and [implementation](homing_example.cpp) files for more details!

1) define a class inheriting from `XBot::ControlPlugin`
2) override at least 
   - `on_initialize` for carrying out initialization and configuration
   - `on_start` to execute code on plugin start
   - `run` to run code inside the main loop
  
   optionally, also `on_stop`, and `on_close`

3) to configure the module, use the parameter API
4) use the `_robot` object to speak with the robot

## How to compile
Compilation of an XBot2 plugin is as easy as the following CMake snippet:

```cmake
find_package(xbot2 REQUIRED)

add_xbot2_plugin(homing_example
    homing_example.cpp)

install(
    TARGETS homing_example
    DESTINATION lib
    )
```
