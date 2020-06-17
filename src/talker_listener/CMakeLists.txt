find_package(xbot2 REQUIRED)

# talker
add_xbot2_plugin(talker
    talker.cpp)

install(
    TARGETS talker
    DESTINATION lib
    )


# listener
add_xbot2_plugin(listener
    listener.cpp)

install(
    TARGETS listener
    DESTINATION lib
    )

