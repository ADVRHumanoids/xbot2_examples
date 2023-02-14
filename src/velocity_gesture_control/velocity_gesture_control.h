#ifndef VELOCITY_GESTURE_CONTROL_H
#define VELOCITY_GESTURE_CONTROL_H

// main XBot2 include
#include <xbot2/xbot2.h>
#include <xbot2/ros/ros_support.h>

#include <std_msgs/String.h>

using namespace XBot;

class VelocityGestureControl : public ControlPlugin
{

public:

    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;


    void starting() override;


    void run() override;

private:

    void on_gesture_recv(const std_msgs::String& msg);
    
    void set_control_mode();

    Eigen::VectorXd __vel_ref;
    double _fake_time;

    RosSupport::UniquePtr _ros;

    CallbackQueue _queue;

    SubscriberPtr<std_msgs::String> _gesture_sub;

    std::atomic<bool> _stop_control;

    XBot::JointNameMap _vel_ref_wheels;


};

#endif // VELOCITY_GESTURE_CONTROL_H
