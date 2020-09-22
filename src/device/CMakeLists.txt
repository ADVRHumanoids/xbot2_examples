find_package(xbot2 REQUIRED)
find_package(gazebo REQUIRED)

if(${GAZEBO_VERSION} VERSION_LESS 8.0)
    message(FATAL "Gazebo >=8.0 required")
endif()


include_directories(${GAZEBO_INCLUDE_DIRS})

# rocket xbot2 endpoint
add_xbot2_device(rocket rocket_device.cpp)
install(TARGETS rocket
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
