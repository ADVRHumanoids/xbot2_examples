#include "velocity_gesture_control.h"

void VelocityGestureControl::on_gesture_recv(const std_msgs::String& msg) 
{
    jhigh().jprint(fmt::fg(fmt::terminal_color::magenta),
                   "received gesture {} \n",
                   msg.data
                   );
    
    if(msg.data == "Go") {
        _stop_control.store(true);
    }
    else {
         _stop_control.store(false);
    }
}

bool VelocityGestureControl::on_initialize()
{

    ros::NodeHandle nh(getName());
    _ros = std::make_unique<RosSupport>(nh);

    _gesture_sub = _ros->subscribe("/gesture/gesture_name",
                                &VelocityGestureControl::on_gesture_recv,
                                this,
                                1,  // queue size
                                &_queue);

    _robot->setControlMode(ControlMode::Position() + ControlMode::Velocity());
    
    set_control_mode();

    _stop_control.store(false);

    return true;
}

void VelocityGestureControl::set_control_mode()
{
    std::map<std::string, ControlMode> ctrl_map;
    
    for(auto j : _robot->getEnabledJointNames())
    {
        ControlMode ctrl;
        if(!getParam("/hal/joint/control_mode/" + j, ctrl))
        {
            continue;
        }
        
        ctrl_map[j] = ctrl;
    }
    
    _robot->setControlMode(ctrl_map);
}

void VelocityGestureControl::starting()
{
    // do some on-start initialization
    _robot->sense();

    // initialize our fake time variable
    // this will increment by the nominal control
    // period at each iteration
    _fake_time = 0.0;

    _vel_ref_wheels["j_wheel_1"] = 0.5;
    _vel_ref_wheels["j_wheel_2"] = -0.5;
    _vel_ref_wheels["j_wheel_3"] = 0.5;
    _vel_ref_wheels["j_wheel_4"] = -0.5;

    // we can switch to run
    start_completed();
}

void VelocityGestureControl::run()
{

    // process callbacks
    _queue.run();

    if(!_stop_control.load()) {
        // move wheels
        _robot->setVelocityReference(_vel_ref_wheels);
        _robot->move();
    }

    // increment fake time
    // note: getPeriodSec() returns the nominal period
    _fake_time += getPeriodSec();
}

XBOT2_REGISTER_PLUGIN(VelocityGestureControl, velocity_gesture_control)
