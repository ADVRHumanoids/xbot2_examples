find_package(xbot2 REQUIRED)

add_xbot2_plugin(homing_example
    homing_example.cpp)

install(
    TARGETS homing_example
    DESTINATION lib
    )
