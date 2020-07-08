#include "rocket_cs_device.h"

using namespace XBot;

Hal::RocketDev::RocketDev(std::string name,
                          std::vector<Hal::DeviceInstanceInfo> devinfo):
    BaseType(name, devinfo),
    _srv_alive(false)
{
    std::vector<DeviceInstanceRt::Ptr> devs;

    std::copy(get_device_instance_typed_vector().begin(),
              get_device_instance_typed_vector().end(),
              std::back_inserter(devs));

    _cli = std::make_unique<ClientManager>(
        devs,
        getParamOr<std::string>("/client_manager/transport", "shm"),
        "rocket"
        );

}

bool Hal::RocketDev::sense()
{
    if(!_srv_alive)
    {
        _srv_alive = _cli->check_server_alive();
        return false;
    }

    bool ret = _cli->recv();

    return ret && BaseType::sense();
}

bool Hal::RocketDev::move()
{
    BaseType::move();

    _cli->send();

    return true;
}

Hal::RocketInstance::RocketInstance(Hal::DeviceInstanceInfo devinfo):
    DeviceInstanceTpl<RocketPacket::Rx, RocketPacket::Tx>(devinfo),
    _timeout(2s)
{

}

bool Hal::RocketInstance::move_impl()
{
    if(chrono::steady_clock::now() >= _tx_recv_time + _timeout)
    {
        _tx.force_ref = 0.0;
    }

    return true;
}

bool Hal::RocketInstance::sense_impl()
{
    // do stuff with _rx
    return true;
}

XBOT2_REGISTER_DEVICE(Hal::RocketDev, rocket_cs)

