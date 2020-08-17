#ifndef ROCKET_RT_DEVICE_H
#define ROCKET_RT_DEVICE_H

#include "rocket_packet.h"
#include "rocket_device.h"

/* This files contains the implementation of the RT endpoint
 * for the device, i.e. the code that is actually called by
 * implementers of XBot2 plugins.
 */

namespace XBot { namespace Hal {

using RocketClientBase = DeviceClientTpl<RocketPacket::Rx,
                                         RocketPacket::Tx>;

/**
 * @brief The RocketRtInstance class implements the device instance
 * abstract interface (RocketInstanceBase) in terms of the packet
 * rx and tx
 */
class RocketClient : public RocketClientBase,
                     public virtual RocketBase
{

public:

    using RocketClientBase::RocketClientBase;

    void setReference(double thrust) override;
    double getReference() const override;
    double getThrust() const override;

};

/**
 * @brief The RocketClientContainer class implements optional API
 * methods referring to multiple rockets together.
 */
class RocketClientContainer : public DeviceContainer<RocketClient>
{

public:

    using DeviceContainer::DeviceContainer;

};

}
}

#endif // ROCKET_RT_DEVICE_H
