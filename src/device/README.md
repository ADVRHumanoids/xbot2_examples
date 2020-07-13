# Adding support for a custom device
[Back to home](../../README.md)

These commented examples show how to integrate a custom device (a rocket attached to the robot end-effector!) into the XBot2.0 framework, at all supported levels. More specifically:

 - [`rocket_packet.h`](rocket_packet.h) defines the low level structure for RT and TX messages to be exchanged (i) between gazebo and XBot2 and (ii) between XBot2 components
 - [`gz_rocket_server.h`](gz_rocket_server.h) / [`.cpp`](gz_rocket_server.cpp) integrates the device inside gazebo, and provides the server side of the gazebo <-> XBot2 communication; the rocker will apply a force about the end-effector *z*-axis according to the value inside the TX field
 - [`rocket_cs_device.h`](rocket_cs_device.h) / [`.cpp`](rocket_cs_device.cpp) provides the client side of the gazebo <-> XBot2 communication, plus integrates the device inside the XBot2 HAL system
 - [`rocket_device.h`](rocket_device.h) defines an abstract, high-level API for the device; this API is used by high-level users (i.e. plugin implementers)
 - [`rocket_rt_device.h`](rocket_rt_device.h) / [`.cpp`](rocket_rt_device.cpp) implements the previously defined high level API in terms of RX/TX packet
 - [`rocket_ros.h`](rocket_ros.h) / [`.cpp`](rocket_ros.cpp) implements a ROS api for the device 

