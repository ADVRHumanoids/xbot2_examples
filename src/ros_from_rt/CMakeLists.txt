find_package(xbot2 REQUIRED)

add_xbot2_plugin(ros_from_rt
    ros_from_rt.cpp)

target_link_libraries(ros_from_rt
    PRIVATE
    xbot2::xbot2_ros_support)

install(
    TARGETS ros_from_rt
    DESTINATION lib
    )
