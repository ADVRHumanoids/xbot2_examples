find_package(xbot2 REQUIRED)

add_xbot2_plugin(joint_space_repeat
    joint_space_repeat.cpp)

install(
    TARGETS joint_space_repeat
    DESTINATION lib
    )
