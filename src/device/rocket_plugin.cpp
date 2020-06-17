#include "rocket_plugin.h"

using namespace XBot;
using namespace std::chrono_literals;

bool RocketCommander::on_initialize()
{
    // read parameters or take default
    _duty_cycle = getParamOr<double>("~duty_cycle", 0.5);
    _pulse_period = getParamOr<double>("~pulse_period", 1.0);
    _thrust = getParamOr<double>("~thrust", 100.0);

    // get out high level api for a rocket instance
    _rocket = _robot->getDeviceInstance<Hal::RocketInstanceBase>("rocket_0");

    // initialization succeeded only if rocket_0 exists and has
    // the correct type
    return bool(_rocket);
}

void RocketCommander::starting()
{
    _start_time = clock_t::now();

    start_completed();
}

void RocketCommander::run()
{
    double time_since_start = chrono::to_sec(clock_t::now() - _start_time);

    double unused = -1.0;

    // if the fractional part of time_since_start/period is
    // greater than the duty cycle, fire!
    if(std::modf(time_since_start/_pulse_period, &unused) > _duty_cycle)
    {
        _rocket->setReference(_thrust);
    }
    else
    {
        _rocket->setReference(0.0);
    }

    // note: _robot->move() will NOT call move on custom devices
    _rocket->move();
}


void RocketCommander::stopping()
{
    // we should send zero reference on stop command
    // we don't do it to test the timeout functionality
//    _rocket->setReference(0.0);
//    _rocket->move();

    stop_completed();
}

XBOT2_REGISTER_PLUGIN(RocketCommander, rocket_commander)

