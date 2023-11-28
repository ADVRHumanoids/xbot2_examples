find_package(xbot2 REQUIRED)

add_xbot2_plugin(periodic_motion
periodic_motion.cpp)

install(
    TARGETS periodic_motion
    DESTINATION lib
    )
