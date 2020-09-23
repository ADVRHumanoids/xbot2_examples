find_package(xbot2 REQUIRED)

add_xbot2_plugin(joint_impedance
    joint_impedance.cpp)

install(
    TARGETS joint_impedance
    DESTINATION lib
    )
