find_package(xbot2 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(std_msgs REQUIRED)

add_xbot2_plugin(ros_from_rt ros_from_rt.cpp)

target_include_directories(ros_from_rt PRIVATE
  ${rclcpp_INCLUDE_DIRS}
  ${sensor_msgs_INCLUDE_DIRS}
  ${std_srvs_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS})

target_link_libraries(ros_from_rt
  PRIVATE
  xbot2::xbot2_ros2_support
  ${rclcpp_LIBRARIES}
  ${sensor_msgs_LIBRARIES}
  ${std_srvs_LIBRARIES}
  ${std_msgs_LIBRARIES})

install(
  TARGETS ros_from_rt
  DESTINATION lib
)