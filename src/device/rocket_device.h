#ifndef ROCKET_DEVICE_H
#define ROCKET_DEVICE_H

#include <xbot2/hal/device.h>

namespace XBot { namespace Hal {

/**
 * @brief The RocketInstanceBase class defines the abstract
 * API for the device instance. This is used by plugin
 * developers.
 */
class RocketBase : virtual public DeviceBase
{

public:

    XBOT2_DECLARE_SMART_PTR(RocketBase)

    virtual void setReference(double thrust) = 0;
    virtual double getReference() const = 0;
    virtual double getThrust() const = 0;

};

} }

#endif // ROCKET_DEVICE_H
