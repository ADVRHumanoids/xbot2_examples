#include "impedance_setpoint.h"

bool ImpedanceSetpoint::on_initialize()
{

    // same for the homing time
    _trj_time = getParamOr("~time", 5.0);  // default to 5.0s

    // check valid time
    if(_trj_time <= 0)
    {
        jerror("got invalid homing time {} s \n",
               _trj_time);

        return false;
    }

    // set home to zero
    if(getParamOr("~restore_impedance", false))
    {
        _robot->sense();
        _robot->getStiffness(_k_home);
        _robot->getDamping(_d_home);
    }
    else
    {
        _k_home.setZero(_robot->getJointNum());
        _d_home.setZero(_robot->getJointNum());
    }

    jinfo("home is k = {}, d = {}",
          _k_home.transpose(), _d_home.transpose());

    // just preallocate variables
    _k_start = _k_ref = _k_home;
    _d_start = _d_ref = _d_home;

    setDefaultControlMode(ControlMode::Stiffness() +
                          ControlMode::Damping());

    return true;
}

void ImpedanceSetpoint::on_start()
{
    // do some on-start initialization
    _robot->sense();
    _robot->getStiffness(_k_start);
    _robot->getDamping(_d_start);

    // initialize our fake time variable
    // this will increment by the nominal control
    // period at each iteration
    _fake_time = 0.0;

}

void ImpedanceSetpoint::run()
{
    // define a simplistic linear trajectory
    double tau = _fake_time/_trj_time;

    // quintic poly 6t^5 - 15t^4 + 10t^3
    double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

    // interpolate
    _k_ref = _k_start + alpha * (_k_home - _k_start);
    _d_ref = _d_start + alpha * (_d_home - _d_start);

    // send reference
    _robot->setStiffness(_k_ref);
    _robot->setDamping(_d_ref);
    _robot->move();
    
    // if trajectory ended, we stop ourselves
    if(tau >= 1.0)
    {
        stop();
        return;
    }

    // increment fake time
    // note: getPeriodSec() returns the nominal period
    _fake_time += getPeriodSec();
}

XBOT2_REGISTER_PLUGIN(ImpedanceSetpoint, impedance_setpoint)
