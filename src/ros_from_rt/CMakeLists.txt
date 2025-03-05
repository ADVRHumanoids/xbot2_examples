find_package(xbot2 REQUIRED)
find_package(rclcpp REQUIRED)  # Add ROS 2 dependency explicitly

add_xbot2_plugin(ros_from_rt
    ros_from_rt.cpp) #TODO Mod this file

target_link_libraries(ros_from_rt
    PRIVATE
    xbot2::xbot2_ros2_support)

install(
    TARGETS ros_from_rt
    DESTINATION lib
    )
