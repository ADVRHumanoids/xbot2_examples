find_package(xbot2 REQUIRED)

add_xbot2_plugin(impedance_setpoint
    impedance_setpoint.cpp)

install(
    TARGETS impedance_setpoint
    DESTINATION lib
    )
