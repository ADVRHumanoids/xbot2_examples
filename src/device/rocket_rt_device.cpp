#include "rocket_rt_device.h"

using namespace XBot;

using namespace std::chrono_literals;

void Hal::RocketRtInstance::setReference(double thrust)
{
    _tx.force_ref = thrust;
}

double Hal::RocketRtInstance::getReference() const
{
    return _rx.force_ref;
}

double Hal::RocketRtInstance::getThrust() const
{
    return _rx.force_meas;
}

// NOTE: name must be ${device_genric_name}_rt
XBOT2_REGISTER_DEVICE(Hal::RocketRt, rocket_rt)
