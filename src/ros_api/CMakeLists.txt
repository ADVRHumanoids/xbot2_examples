find_package(xbot2_interface REQUIRED)
find_package(rclcpp REQUIRED)  # Change from roscpp to rclcpp #TODO Mod this file

add_executable(ros_api_tutorial ros_api_tutorial.cpp)
target_link_libraries(ros_api_tutorial 
  xbot2_interface::xbot2_interface 
  ${rclcpp_LIBRARIES})

# Add install for ROS 2
install(TARGETS ros_api_tutorial
  DESTINATION lib/${PROJECT_NAME})