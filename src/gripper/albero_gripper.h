#ifndef ALBERO_GRIPPER_RT_H
#define ALBERO_GRIPPER_RT_H

#include <xbot2/xbot2.h>
#include <xbot2/hal/dev_button.h>
#include <xbot2/hal/dev_gripper.h>
#include <xbot2/ros/ros_support.h>

#include <XBotInterface/Utils.h>

#include <std_msgs/Float32.h>

#include "buttons.hpp"
#include <albero_gripper_msgs/Gripper.h>

namespace XBot {

class AlberoGripperRt : public ControlPlugin
{

private:

    typedef albero_gripper_msgs::Gripper gripper_state;
    typedef std_msgs::Float32 gripper_command;
    typedef Utils::SecondOrderFilter <double> filter;

public:

    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;
    void starting() override;
    void run() override;
    void stopping() override;

private:

    void setup_ros();
    void publish_state(const Hal::GripperBase::Ptr gripper) const;
    void set_closure_target(const std::string& name, const std_msgs::Float32& closure);

private:

    using clock_t = chrono::steady_clock;

    clock_t::time_point _start_time;

    Hal::DeviceContainer <Hal::GripperBase> _grippers;
    Hal::DeviceContainer <Hal::ButtonsBoardBase> _buttons_boards;

    std::vector <Albero::GripperButtonsBoard::Ptr> _gripper_buttons_boards;

    std::map <std::string, double> _targets;
    std::map <std::string, filter::Ptr> _filters;
    std::map <std::string, PublisherPtr <gripper_state>> _state_publishers;

    std::vector <SubscriberPtr <gripper_command>> _closure_setters ;

    RosSupport::UniquePtr _ros;
    CallbackQueue _queue;

};


}

#endif // ALBERO_GRIPPER_RT_H
