find_package(xbot2 REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp albero_gripper_msgs visualization_msgs)

#compile messages
#add_subdirectory(msg/gripper_msgs)

# client
add_xbot2_plugin(albero_gripper_rt
    button_event.cpp
    buttons.cpp
    albero_gripper.cpp)

target_link_libraries(albero_gripper_rt PRIVATE
    xbot2::xbot2_ros_support)

install(
    TARGETS albero_gripper_rt
    DESTINATION lib
)

