# Adding support for a custom device
[Back to home](../../README.md)

These commented examples show how to integrate a custom device (a rocket attached to the robot end-effector!) into the XBot2.0 framework, at all supported levels. More specifically:

 - [`rocket_device.h`](rocket_device.h) defines an abstract, high-level API for the device; this API is used by high-level users (i.e. plugin implementers)
 - [`rocket_packet.h`](rocket_packet.h) defines the low level structure for RT and TX messages to be exchanged (i) between gazebo and XBot2 and (ii) between XBot2 components
 - [`gz_rocket_server.h`](gz_rocket_server.h) / [`.cpp`](gz_rocket_server.cpp) integrates the device inside gazebo, and provides the server side of the gazebo <-> XBot2 communication; the rocket will apply a force about the end-effector *z*-axis according to the value inside the TX field
 - [`rocket_device.cpp`](rocket_device.cpp) provides the client side of the gazebo <-> XBot2 communication, plus integrates the device inside the XBot2 HAL system
 - [`rocket_plugin.h`](rocket_plugin.h) / [`.cpp`](rocket_plugin.cpp) implements an example plugin using the rocket API 

