#include "periodic_motion.h"

bool PeriodicMotion::on_initialize()
{

    bool home_start_val_found = getParam("~q_home_start", _q_home_start);
    bool home_end_val_found = getParam("~q_home_end", _q_home_end);

    // we did not find neither the home start name, nor the home start value
    if(!home_start_val_found && !home_start_val_found)
    {
        jerror("please set q_home_start and q_home_end \n");
        return false;
    }

    // same for the homing time
    _motion_time = getParamOr("~time", 20.0);  // default to 5.0s

    // check valid time
    if(_motion_time <= 0)
    {
        jerror("got invalid homing time {} s \n",
               _motion_time);

        return false;
    }

    // check size of q refs
    if((_q_home_start.size() != _robot->getJointNum()) ||
        (_q_home_end.size() != _robot->getJointNum()) )
    {
        jerror("requested home value has wrong size != {} \n", _robot->getJointNum());
        return false;
    }
    

    // just preallocate variables
    _q_start = _q_ref = _q_home = _q_home_start;

    // set default control mode:
    // upon start, the framework will try to acquire the specified
    // resource from the underlying device
    // on failure, plugin cannot start
    setDefaultControlMode(ControlMode::Position());

    return true;
}

void PeriodicMotion::on_start()
{

    // do some on-start initialization
    _robot->sense();
    _robot->getPositionReference(_q_start);
    _robot->getVelocityReference(_q_dot_ref);

    _robot->setControlMode(XBot::ControlMode::Position() + XBot::ControlMode::Velocity());

    // initialize our fake time variable
    // this will increment by the nominal control
    // period at each iteration
    _fake_time = 0.0;
}


void PeriodicMotion::run()
{
    // define a simplistic linear trajectory
    double tau = _fake_time/_motion_time;

    // quintic poly 6t^5 - 15t^4 + 10t^3
    double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

    //double ang_vel = 0.05;
    //double alpha = ang_vel * tau;

    // interpolate based on the motion needed
    if(_start_to_end) {
        _q_home = _q_home_end; 
    }
    else{
        _q_home = _q_home_start;
    }
    _q_ref = _q_start + alpha * (_q_home - _q_start);
    //_q_dot_ref = ang_vel * (_q_home - _q_start);

    // send reference
    _robot->setPositionReference(_q_ref);
    //_robot->setVelocityReference(_q_dot_ref);
    _robot->move();
    
    if(tau >= 1.0)
    {
        _fake_time = 0.0;
        _start_to_end = !_start_to_end;
        _robot->getPositionReference(_q_start);
        _robot->getVelocityReference(_q_dot_ref);

        jinfo("Inverting trajectory\n");
        return;
    }

    // increment fake time
    // note: getPeriodSec() returns the nominal period
    _fake_time += getPeriodSec();
}

XBOT2_REGISTER_PLUGIN(PeriodicMotion, periodic_motion)
