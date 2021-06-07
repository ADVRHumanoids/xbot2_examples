#ifndef ALBERO_GRIPPER_RT_H
#define ALBERO_GRIPPER_RT_H

#include <xbot2/xbot2.h>
#include <xbot2/hal/dev_gripper.h>
#include <xbot2/ros/ros_support.h>

#include <std_msgs/Float32.h>

namespace XBot {

class AlberoGripperRt : public ControlPlugin
{

public:

    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;
    void starting() override;
    void run() override;
    void stopping() override;
//    void on_abort() override;
//    void on_close() override;

private:

    void setup_ros();
    void set_closure_reference(const std::string name, const std_msgs::Float32& closure);

private:

    using clock_t = chrono::steady_clock;

    clock_t::time_point _start_time;
    Hal::DeviceContainer <Hal::GripperBase> _grippers;

    CallbackQueue _queue;

//    PublisherPtr<sensor_msgs::JointState> _js_pub;
    std::vector <SubscriberPtr <std_msgs::Float32>> _closure_setters;
    RosSupport::UniquePtr _ros;

};


}

#endif // ALBERO_GRIPPER_RT_H
