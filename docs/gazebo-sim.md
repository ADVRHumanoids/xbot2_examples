# Simulate a robotic system with Gazebo

[Back to home](../README)

## Prerequisites

- a URDF/SRDF description of your robot that you can load inside Gazebo (even though without controller it will just collapse to the ground)

## Adding a clock driver
To enable the clock synchronization on the `XBot2` side according to Gazebo's simulation time, you can use the following `WorldPlugin`
```xml
<world>

    ...

    <plugin name='xbot2_gz_clock' filename='libxbot2_gz_clock.
  so'/>
    
    ...

</world>
```

## Adding a joint device driver
To enable the joint device, add the following `ModelPlugin` to your robot
```xml
<model>
    
    ...

   <plugin name='xbot2_gz_joint_server' filename='libxbot2_gz_joint_server.so'/>
    
    ...

</model>
```



