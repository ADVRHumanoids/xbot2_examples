find_package(xbot2 REQUIRED)
find_package(cartesian_interface REQUIRED)
find_package(cartesio-integration REQUIRED)

# client
add_xbot2_plugin(cartesio_rt
    cartesio_rt.cpp)

add_xbot2_plugin(albero_cartesio_rt
    albero_cartesio_rt.cpp
    cartesio_rt.cpp
    partition.cpp)

#include_directories(${cartesio-integration_INCLUDE_DIRS})

target_link_libraries(cartesio_rt PRIVATE ${cartesian_interface_LIBRARIES})
target_link_libraries(albero_cartesio_rt PRIVATE
    ${cartesian_interface_LIBRARIES}
    ${cartesio-integration_LIBRARIES}
    xbot2::xbot2_ros_support)

install(
    TARGETS cartesio_rt
    DESTINATION lib
)

install(
    TARGETS albero_cartesio_rt
    DESTINATION lib
)
