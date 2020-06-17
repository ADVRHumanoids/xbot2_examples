#ifndef GZ_ROCKET_PACKET_H
#define GZ_ROCKET_PACKET_H

namespace XBot { namespace Hal {

/**
 * @brief The RocketPacket struct defines Rx and Tx
 * data to be exchanged between client and server,
 * and inside the internals of the XBot2 framework.
 * This data structure is not visible to high level
 * users (such as plugin developers), as it will be
 * abstracted away by the device abstract API
 * (see 'rocket_device.h')
 */
struct RocketPacket
{
    struct Rx
    {
        float force_ref;
        float force_meas;
    };

    struct Tx
    {
        float force_ref;
    };

};


}
}


#endif // GZ_ROCKET_PACKET_H
