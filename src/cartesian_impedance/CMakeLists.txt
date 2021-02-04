find_package(xbot2 REQUIRED)

add_xbot2_plugin(cartesian_impedance_task
    CartesianImpedance_Task.cpp
    CartesianImpedance_Task_ert_rtw/CartesianImpedance_Task.cpp
    CartesianImpedance_Task_ert_rtw/CartesianImpedance_Task_data.cpp
    CartesianImpedance_Task_ert_rtw/rtGetInf.cpp
    CartesianImpedance_Task_ert_rtw/rtGetNaN.cpp
    CartesianImpedance_Task_ert_rtw/rt_nonfinite.cpp)

find_library(XBotBlock_Utils NAMES XBotBlock_Utils PATH /home/embedded/xbot2_ws/install/lib)

find_package(BlockFactory REQUIRED COMPONENTS Core SimulinkCoder)



# Link the library with the Core component containing the core classes
target_link_libraries(cartesian_impedance_task PRIVATE BlockFactory::Core BlockFactory::SimulinkCoder ${XBotBlock_Utils})
# Setup the include directories
target_include_directories(cartesian_impedance_task PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)  

set_property(TARGET cartesian_impedance_task PROPERTY CXX_STANDARD 14)

install(
    TARGETS cartesian_impedance_task
    DESTINATION lib
    )

