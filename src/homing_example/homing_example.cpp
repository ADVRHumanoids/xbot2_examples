#include "homing_example.h"

bool HomingExample::on_initialize()
{

    // to make this plugin minimally configurable,
    // we take the homing state name from two internal
    // XBot2 parameters named '~home' and '~qhome'

    std::string home_name = "home";
    bool home_name_found = getParam("~home", home_name);
    bool home_val_found = getParam("~qhome", _q_home);

    // we did not find neither the home name, nor the home value
    if(!home_name_found && !home_val_found)
    {
        // print a warning (only in verbose mode)
        jwarn("home parameters ['~home', '~qhome'] not found, "
              "using default home '{}' \n",
              home_name);
    }

    // we found both, issue a warning
    if(home_name_found && home_val_found)
    {
        // a high priority warning will show up even
        // in non-verbose mode
        jhigh().jwarn("found both '~home' and '~qhome' parameters, "
                      "will use '~qhome' \n");
    }

    // same for the homing time
    _homing_time = getParamOr("~time", 5.0);  // default to 5.0s

    // check valid time
    if(_homing_time <= 0)
    {
        jerror("got invalid homing time {} s \n",
               _homing_time);

        return false;
    }

    // take home from srdf if we did not get the value
    if(!home_val_found)
    {
        // if invalid, print error and exit
        if(!_robot->getRobotState(home_name, _q_home))
        {
            jerror("requested home name '{}' unavailable \n", home_name);
            return false;
        }
    }
    else  // we got the value from the user, check dimension
    {
        if(_q_home.size() != _robot->getJointNum())
        {
            jerror("requested home value has wrong size {} != {} \n",
                   _q_home.size(), _robot->getJointNum());
            return false;
        }
    }

    // just preallocate variables
    _q_start = _q_ref = _q_home;

    // we must explicitly set the control mode for our robot
    // in this case, we will only send positions
    _robot->setControlMode(ControlMode::Position());

    return true;
}

void HomingExample::starting()
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

void HomingExample::run()
{
    // define a simplistic linear trajectory
    double alpha = _fake_time/_homing_time;
    _q_ref = _q_start + alpha * (_q_home - _q_start);

    // send reference
    _robot->setPositionReference(_q_ref);
    _robot->move();
    
    // if trajectory ended, we stop ourselves
    if(alpha >= 1.0)
    {
        stop();
        return;
    }

    // increment fake time
    _fake_time += getPeriodSec();
}

XBOT2_REGISTER_PLUGIN(HomingExample, homing_example)
