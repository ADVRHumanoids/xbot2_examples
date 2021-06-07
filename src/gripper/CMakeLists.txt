find_package(xbot2 REQUIRED)

# client
add_xbot2_plugin(albero_gripper_rt
    albero_gripper.cpp)

#include_directories(${cartesio-integration_INCLUDE_DIRS})

target_link_libraries(albero_gripper_rt PRIVATE
    xbot2::xbot2_ros_support)

install(
    TARGETS albero_gripper_rt
    DESTINATION lib
)
