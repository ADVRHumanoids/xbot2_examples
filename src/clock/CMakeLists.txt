find_package(xbot2 REQUIRED)

add_xbot2_plugin(clock_example
    clock.cpp)

install(
    TARGETS clock_example
    DESTINATION lib
    )
