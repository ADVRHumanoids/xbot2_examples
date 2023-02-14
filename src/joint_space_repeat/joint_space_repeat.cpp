#include "joint_space_repeat.h"

bool JointSpaceRepeat::on_initialize()
{

    bool a_found = getParam("~q_a", _q_a);
    bool b_found = getParam("~q_b", _q_b);

    _motion_time = getParamOr("~time", 5.0);  // default to 5.0s

    // check valid time
    if(_motion_time <= 0)
    {
        jerror("got invalid homing time {} s \n",
               _motion_time);

        return false;
    }


    if( _q_a.size() != _robot->getJointNum() || 
        _q_b.size() != _robot->getJointNum()) {
        {
            jerror("requested home value has wrong size {} or {} != {} \n",
                   _q_a.size(), _q_b.size(), _robot->getJointNum());
            return false;
        }
    }

    for(int i = 0; i < _robot->getJointNum(); i++){
        std::cout << _robot->getEnabledJointNames()[i] << std::endl;
    }

    // just preallocate variables
    _q_start = _q_ref = _q_a;

    // we must explicitly set the control mode for our robot
    // in this case, we will only send positions
    _robot->setControlMode(ControlMode::Position());
    
    set_control_mode();

    return true;
}

void JointSpaceRepeat::set_control_mode()
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

void JointSpaceRepeat::starting()
{
    // do some on-start initialization
    _robot->sense();
    _robot->getPositionReference(_q_start);

    // initialize our fake time variable
    // this will increment by the nominal control
    // period at each iteration
    _fake_time = 0.0;

    // we can switch to run
    start_completed();
}

void JointSpaceRepeat::run()
{
    // define a simplistic linear trajectory
    double tau = _fake_time/_motion_time;

    // quintic poly 6t^5 - 15t^4 + 10t^3
    double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

    // interpolate
    if(_one_way_motion_in_execution)
        _q_ref = _q_start + alpha * (_q_a - _q_start);
    else
        _q_ref = _q_start + alpha * (_q_b - _q_start);

    // send reference
    _robot->setPositionReference(_q_ref);
    _robot->move();
    
    // if trajectory ended, we stop ourselves
    if(tau >= 1.0)
    {
        if(_one_way_motion_in_execution){
            _q_start = _q_a;
        }
        else{
            _q_start = _q_b;
        }
        
        _one_way_motion_in_execution = ! _one_way_motion_in_execution;
        _fake_time = 0.0;
        return;
    }

    // increment fake time
    // note: getPeriodSec() returns the nominal period
    _fake_time += getPeriodSec();
}

XBOT2_REGISTER_PLUGIN(JointSpaceRepeat, joint_space_repeat)
