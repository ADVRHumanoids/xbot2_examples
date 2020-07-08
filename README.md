# xbot2_examples
### Examples for the XBot2.0 middleware

This repository containes commented examples of use for the **XBot2.0** real-time middleware for robotics. The IIT-Teleop robot, a 5-dof robotic arm, is provided as testing platform.

## Contents

- [Simulating a robotic system with Gazebo](docs/gazebo-sim.md)
- [Writing a simple control module as an *XBot2 Plugin*](src/homing_example/README.md)
- [Configuring the middleware](config/README.md)
- Inter-plugin communication (data streaming, rpc-like)
- Using ROS from a real-time plugin
- Adding a custom device

## How to build

Standard CMake workflow

 - `mkdir build && cd build`
 - `ccmake <path-to-repo>`
 - select a build type and an install folder (must be visible to the dynamic linker), type `c` and then `g`
 - `make -j install`

 ## How to setup

  - make sure that the robot sdf and meshes are visible to Gazebo; for instance, you can add the following line to your `.bashrc`
   ```
   export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:<path-to-repo>/models/database
   ```
- set the XBot2 configuration file to the provided example with `set_xbot_config <path-to-repo>/config/teleop_simple_example.yaml`
- point the `XBOT_ROOT` environment variable to the repository folder with `export XBOT_ROOT=<path-to-repo>` (this can also go to the `.bashrc` for convenience)

 ## How to run

- load the provided `.world` file to Gazebo with the following command:
  ```
  gazebo <path-to-repo>/world/teleop_xbot2.world
  ```
  you should now see the robot inside Gazebo
- run XBot2 with `xbot2-core` or `xbot2-core --verbose` 


You should now be able to (for instance)
 
 - get the list of loaded plugins -> `rosservice call /xbotcore/get_plugin_list`
 - monitor execution time -> `rostopic echo /xbotcore/statistics`
 - monitor joint state -> `rostopic echo /xbotcore/joint_states`

 
