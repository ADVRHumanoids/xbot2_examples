find_package(xbot2 REQUIRED)

#compile messages
add_subdirectory(msg/gripper_msgs)
find_package(catkin REQUIRED COMPONENTS albero_gripper_msgs)

include_directories(
    ${albero_gripper_msgs_INCLUDE_DIRS}
    )

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

