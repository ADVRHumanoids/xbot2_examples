find_package(xbot2 REQUIRED)

add_xbot2_plugin(homing_example
    homing_example.cpp)

target_link_libraries(homing_example
    PRIVATE
    xbot2::xbot2)

install(
    TARGETS homing_example
    DESTINATION lib
    )
