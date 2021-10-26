# Configuring the XBot2 middleware

[Back to home](../README.md)

The XBot2 framework is configured through a set of configuration files, i.e.

 - the robot URDF
     - kinematic structure and dynamic properties
 - the robot SRDF
     - organization of joint vector into a set of kinematic chains
     - define robot states (such as a joint space homing, or some impedance profiles, ...)
 - an additional YAML file
     - specify URDF/SRDF path
     - define devices
     - define threads to distribute workload
     - define plugins to be loaded
     - define parameters to be set

Check the [example YAML file](teleop_complete_example.yaml) for a commented example!
