# Xbot2 ROS API
[Back to home](../../README.md)

Integration between Xbot2 and ROS is made possible by two plugins, namely `ros_io` and `ros_control`, that come with the Xbot2 package itself.
They are responsible for providing the following functionalities:
  
  - `ros_io` offers plugin management funcionalities and robot state broadcasting, such as:
    - `get_plugin_list` service to get the list of initialized plugins
    - `<plugin_name>/switch` to enable or disable a plugin 
    - `<plugin_name>/state` to monitor its state (among a defined plugin lifecycle state machine)
    - `<plugin_name>/abort` to abruptly stop a plugin
    - joint state broadcast to the `joint_states` topic
    - transforms broadcast to the `/tf` topic
    - execution statistics broadcast to the `statistics` topic
    - joint device safety management, such as:
      - enabling/disabling joint reference filtering (`enable_joint_filter`)
      - changing its cutoff frequency (`set_filter_profile_*`)
      - enabing/disabling the joint device  (`joint_master/set_control_mask`)
  - `ros_control` forwards any message received on the `command` topic to the motor control API

Note that, by default, all ROS resource names live inside the `/xbotcore` namespace.

## Python 
Follow the [provided *Jupyter Notebook*](ros_api_tutorial.ipynb) (install with `pip install notebook` if needed) to get a grasp on how to control an Xbot2 robot in joint space from a python ROS node. Just type the command

```bash
jupyter notebook ros_api_tutorial.ipynb
```

---

*Note: to run a jupyter notebook from inside a **docker** container, use the following command*

```
jupyter notebook --no-browser --ip=0.0.0.0 <notebook-file>. 
```

*and make sure that port `8888` is being published to the host machine*. Our example docker provides the `notebook_docker` alias for the sake of convenience.

## C++
The same behavior can be equivalently implemented in C++, as shown by [this example](ros_api_tutorial.cpp).
After compilation, it can be executed with

```bash
cd <build-dir> && ./src/ros_api/ros_api_tutorial 
```

