find_package(xbot2 REQUIRED)
find_package(gazebo 8.0 REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})

# rocket client endpoint
add_xbot2_device(rocket_cs rocket_cs_device.cpp)
install(TARGETS rocket_cs
    DESTINATION lib)

# rocket high level implementation
add_xbot2_device(rocket_rt rocket_rt_device.cpp)
install(TARGETS rocket_rt
    DESTINATION lib)

# rocket server endpoint (gazebo plugin)
add_library(xbot2_gz_rocket_server SHARED gz_rocket_server.cpp)
target_link_libraries(xbot2_gz_rocket_server
    PRIVATE
    xbot2::xbot2
    )
install(TARGETS xbot2_gz_rocket_server
    DESTINATION lib)

# an example plugin
add_xbot2_plugin(rocket_commander rocket_plugin.cpp)
install(TARGETS rocket_commander
    DESTINATION lib)

# a ros interface
add_library(xbotdev_ros_rocket_rt SHARED rocket_ros.cpp)
target_link_libraries(xbotdev_ros_rocket_rt xbot2::xbot2 xbot2::xbot2_ros_support)
install(TARGETS xbotdev_ros_rocket_rt
    DESTINATION lib)
