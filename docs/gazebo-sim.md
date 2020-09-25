# Simulate a robotic system with Gazebo

[Back to home](../README.md)

## Prerequisites

- a URDF/SRDF description of your robot that you can load inside Gazebo (even though without controller it will just collapse to the ground)

## Adding a clock driver
To enable the clock synchronization on the `XBot2` side according to Gazebo's simulation time, you can use the following `WorldPlugin`
```xml
<world>

    ...

    <plugin name='xbot2_gz_clock' filename='libxbot2_gz_clock.so'/>
    
    ...

</world>
```

## Adding a joint device driver
To enable the joint device, add the following `ModelPlugin` to your robot
```xml
<model>
    
    ...

    <plugin name='xbot2_gz_joint_server' filename='libxbot2_gz_joint_server.so'>
        <pid>
            <gain name="small_mot"  p="250"  d="5"/>
            <gain name="medium_mot" p="1000" d="10"/>
            <gain name="big_mot"    p="3000" d="10"/>
            <gain name="wheel_mot"  p="0" d="30"/>

            <gain name="j_arm1_1" profile="medium_mot"/>
            <gain name="j_arm1_2" profile="medium_mot"/>
            <gain name="j_arm1_3" profile="medium_mot"/>
            <gain name="j_arm1_4" profile="medium_mot"/>
            <gain name="j_arm1_5" profile="small_mot"/>
            <gain name="j_arm1_6" profile="small_mot"/>
            <gain name="j_arm1_7" profile="small_mot"/>
        </pid>
    </plugin>

    ...

</model>
```

## Adding FT and IMU drivers
To enable the ready-to-use FT and IMU devices, add the following `ModelPlugin`s to your robot
```xml
<model>

    ...

    <plugin name="xbot2_ft_driver" filename="libxbot2_gz_ft_server.so"/>

    <plugin name="xbot2_imu_driver" filename="libxbot2_gz_imu_server.so"/>

    ...

</model>
```


