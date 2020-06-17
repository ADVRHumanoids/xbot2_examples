find_package(xbot2 REQUIRED)

# client
add_xbot2_plugin(client
    client.cpp)

install(
    TARGETS client
    DESTINATION lib
    )


# server
add_xbot2_plugin(server
    server.cpp)

install(
    TARGETS server
    DESTINATION lib
    )

