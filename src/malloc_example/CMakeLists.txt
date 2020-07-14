find_package(xbot2 REQUIRED)

add_xbot2_plugin(malloc_example
    malloc_example.cpp)

install(
    TARGETS malloc_example
    DESTINATION lib
    )
