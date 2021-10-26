find_package(XBotInterface REQUIRED)
find_package(roscpp REQUIRED)

add_executable(ros_api_tutorial ros_api_tutorial.cpp)
target_link_libraries(ros_api_tutorial 
    XBotInterface::XBotInterface
    ${roscpp_LIBRARIES})