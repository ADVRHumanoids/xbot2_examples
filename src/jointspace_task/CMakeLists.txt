find_package(xbot2 REQUIRED)

add_xbot2_plugin(jointspace_task
    jointspace_task.cpp
    JointSpace_Task_ert_rtw/JointSpace_Task.cpp
    JointSpace_Task_ert_rtw/JointSpace_Task_data.cpp
    JointSpace_Task_ert_rtw/rtGetInf.cpp
    JointSpace_Task_ert_rtw/rtGetNaN.cpp
    JointSpace_Task_ert_rtw/rt_nonfinite.cpp)

find_library(XBotBlock_Utils NAMES XBotBlock_Utils PATH /home/embedded/xbot2_ws/install/lib)

find_package(BlockFactory REQUIRED COMPONENTS Core SimulinkCoder)
# Link the library with the Core component containing the core classes
target_link_libraries(jointspace_task PRIVATE BlockFactory::Core BlockFactory::SimulinkCoder ${XBotBlock_Utils})
# Setup the include directories
target_include_directories(jointspace_task PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)  

install(
    TARGETS jointspace_task
    DESTINATION lib
    )
