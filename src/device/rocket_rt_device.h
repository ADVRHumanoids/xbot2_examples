#ifndef ROCKET_RT_DEVICE_H
#define ROCKET_RT_DEVICE_H

#include "rocket_packet.h"
#include "rocket_device.h"

/* This files contains the implementation of the RT endpoint
 * for the device, i.e. the code that is actually called by
 * implementers of XBot2 plugins.
 */

namespace XBot { namespace Hal {

using RocketRtInstanceBase = RobotInterfaceDeviceInstanceTpl<RocketPacket::Rx,
                                                             RocketPacket::Tx>;

/**
 * @brief The RocketRtInstance class implements the device instance
 * abstract interface (RocketInstanceBase) in terms of the packet
 * rx and tx
 */
class RocketRtInstance : public RocketRtInstanceBase,
                         public virtual RocketInstanceBase
{

public:

    using RocketRtInstanceBase::RocketRtInstanceBase;

    void setReference(double thrust) override;
    double getReference() const override;
    double getThrust() const override;

};

/**
 * @brief The RocketRt class builds a device out of the
 * RocketRtInstance defined before.
 */
class RocketRt : public DeviceTpl<RocketRtInstance>,
                 public virtual RocketBase
{

public:

    using DeviceTpl<RocketRtInstance>::DeviceTpl;

};

}
}

#endif // ROCKET_RT_DEVICE_H
