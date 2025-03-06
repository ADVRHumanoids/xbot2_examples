find_package(xbot2_interface REQUIRED)
find_package(rclcpp REQUIRED)  # Change from roscpp to rclcpp #TODO Mod this file
find_package(std_msgs REQUIRED)

add_executable(ros_api_tutorial ros_api_tutorial.cpp)

ament_target_dependencies(ros_api_tutorial 
  rclcpp
  std_msgs)

target_link_libraries(ros_api_tutorial 
  xbot2_interface::xbot2_interface)

# Add install for ROS 2
install(TARGETS ros_api_tutorial
  DESTINATION lib/${PROJECT_NAME})