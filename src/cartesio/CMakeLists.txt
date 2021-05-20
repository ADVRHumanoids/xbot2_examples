find_package(xbot2 REQUIRED)
find_package(cartesian_interface REQUIRED)

# client
add_xbot2_plugin(cartesio_rt
    cartesio_rt.cpp)

add_xbot2_plugin(albero_cartesio_rt
    albero_cartesio_rt.cpp
    cartesio_rt.cpp)

target_link_libraries(cartesio_rt PRIVATE ${cartesian_interface_LIBRARIES})
target_link_libraries(albero_cartesio_rt PRIVATE ${cartesian_interface_LIBRARIES})

install(
    TARGETS cartesio_rt
    DESTINATION lib
)

install(
    TARGETS albero_cartesio_rt
    DESTINATION lib
)
