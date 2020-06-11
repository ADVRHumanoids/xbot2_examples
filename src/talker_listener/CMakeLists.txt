find_package(xbot2 REQUIRED)

# talker
add_xbot2_plugin(talker
    talker.cpp)

target_link_libraries(talker
    PRIVATE
    xbot2::xbot2)

install(
    TARGETS talker
    DESTINATION lib
    )


# listener
add_xbot2_plugin(listener
    listener.cpp)

target_link_libraries(listener
    PRIVATE
    xbot2::xbot2)

install(
    TARGETS listener
    DESTINATION lib
    )

