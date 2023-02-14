find_package(xbot2 REQUIRED)

add_xbot2_plugin(velocity_gesture_control
    velocity_gesture_control.cpp)

target_link_libraries(velocity_gesture_control
    PRIVATE
    xbot2::xbot2_ros_support)    

install(
    TARGETS velocity_gesture_control
    DESTINATION lib
    )
