#ifndef ROCKET_DEVICE_H
#define ROCKET_DEVICE_H

#include <xbot2/hal/device.h>

namespace XBot { namespace Hal {

/**
 * @brief The RocketInstanceBase class defines the abstract
 * API for the device instance. This is used by plugin
 * developers.
 */
class RocketInstanceBase : virtual public DeviceInstanceBase
{

public:

    XBOT2_DECLARE_SMART_PTR(RocketInstanceBase)

    virtual void setReference(double thrust) = 0;
    virtual double getReference() const = 0;
    virtual double getThrust() const = 0;

};

/**
 * @brief The RocketBase class is here in case we need some
 * API to cover the whole group of rocket device instances
 * in a coupled way (usually it is just empty)
 */
class RocketBase : virtual public DeviceBaseTpl<RocketInstanceBase>
{

};

} }

#endif // ROCKET_DEVICE_H
