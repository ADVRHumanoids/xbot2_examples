find_package(xbot2 REQUIRED)
find_package(matlogger2 REQUIRED)

add_xbot2_plugin(logger_plugin
    logger_plugin.cpp)

target_link_libraries(logger_plugin PRIVATE matlogger2::matlogger2)

install(
    TARGETS logger_plugin
    DESTINATION lib
    )

