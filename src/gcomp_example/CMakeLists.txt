cmake_minimum_required(VERSION 3.0)

option(XBOT2_ENABLE_XENO OFF)

find_package(xbot2 REQUIRED)

add_xbot2_plugin(gcomp_example gcomp_example.cpp)

install(TARGETS gcomp_example
    DESTINATION lib)
