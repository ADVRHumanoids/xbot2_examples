# xbot2_examples
### Examples for the XBot2.0 middleware

This repository containes commented examples of use for the [**XBot2.0**](https://advrhumanoids.github.io/xbot2_wip/quickstart.html) real-time middleware for robotics. The IIT-Teleop robot, a 5-dof robotic arm, is provided as testing platform.

## Contents

- [Simulating a robotic system with Gazebo](docs/gazebo-sim.md)
- [Writing a simple control module as an *XBot2 Plugin*](src/homing_example/README.md)
- [Configuring the middleware](config/README.md)
- Inter-plugin communication ([data streaming](src/talker_listener/README.md), [rpc-like](src/client_server/README.md))
- [Using ROS from a real-time plugin](src/ros_from_rt/README.md)
- [Adding a custom device](src/device/README.md)
- [Controlling the robot from ROS](src/ros_api/README.md)

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
- set the XBot2 configuration file to the provided example with `set_xbot2_config <path-to-repo>/config/teleop_complete_example.yaml` *(note: this is optional as this information can be provided later as a command line argument)*


 ## How to run

- load the provided `.world` file to Gazebo with the following command:
  ```
  gazebo <path-to-repo>/world/teleop_xbot2.world
  ```
  you should now see the robot inside Gazebo
- run XBot2 with `xbot2-core` or `xbot2-core --verbose` *(note: add `--config <path-to-repo>/config/teleop_complete_example.yaml` if you did not use the  `set_xbot2_config` command during the setup phase)*


You should now be able to (for instance)
 
 - get the list of loaded plugins -> `rosservice call /xbotcore/get_plugin_list`
 - monitor execution time -> `rostopic echo /xbotcore/statistics`
 - monitor joint state -> `rostopic echo /xbotcore/joint_states`

<h2>Running inside Docker container <img src="https://www.docker.com/sites/default/files/d8/styles/role_icon/public/2019-07/horizontal-logo-monochromatic-white.png" alt="drawing" width="100"/> </h2>

 - [install docker](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository)
   and set it up so that it [does not require sudo permissions](https://docs.docker.com/engine/install/linux-postinstall/)
 - [install nvidia container toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html#docker) if you have an nvidia card
 - `./docker/run.sh` runs the container (the first time it will also download a crazy amount of data!)
 - to spawn more `bash` sessions inside the same container instance, do `./docker/attach.sh`
 - open three `bash` sessions
 - terminal #1: `./build-examples.sh` (compiles the source code of this repository; **NOTE** that the source code is shared with the host machine!)
 - terminal #1: `./start.sh` (starts `roscore` and `gazebo`)
 - terminal #2: `xbot2-core` (XBot2 executable)
 - terminal #3: `xbot2-gui` (GUI should appear)

