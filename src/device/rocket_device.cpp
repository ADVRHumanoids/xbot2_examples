#include "rocket_device_driver.h"
#include "rocket_device_client.h"

using namespace XBot;

Hal::RocketDriverContainer::RocketDriverContainer(std::vector<Hal::DeviceInfo> devinfo):
    DeviceContainer(devinfo),
    _srv_alive(false)
{
    std::vector<DeviceRt::Ptr> devs;

    std::copy(get_device_vector().begin(),
              get_device_vector().end(),
              std::back_inserter(devs));

    _cli = std::make_unique<ClientManager>(
        devs,
        "shm",
        "rocket"
        );

}

bool Hal::RocketDriverContainer::sense_all()
{
    if(!_srv_alive)
    {
        _srv_alive = _cli->check_server_alive();
        return false;
    }

    bool ret = _cli->recv();

    return ret && DeviceContainer::sense_all();
}

bool Hal::RocketDriverContainer::move_all()
{
    DeviceContainer::move_all();

    _cli->send();

    return true;
}

Hal::RocketDriver::RocketDriver(Hal::DeviceInfo devinfo):
    DeviceDriverTpl(devinfo),
    _timeout(2s)
{

}

bool Hal::RocketDriver::move_impl()
{
    if(chrono::steady_clock::now() >= _tx_recv_time + _timeout)
    {
        _tx.force_ref = 0.0;
    }

    return true;
}

bool Hal::RocketDriver::sense_impl()
{
    // do stuff with _rx
    return true;
}

void Hal::RocketClient::setReference(double thrust)
{
    _tx.force_ref = thrust;
}

double Hal::RocketClient::getReference() const
{
    return _rx.force_ref;
}

double Hal::RocketClient::getThrust() const
{
    return _rx.force_meas;
}

XBOT2_REGISTER_DEVICE(Hal::RocketDriverContainer,
                      Hal::RocketClientContainer,
                      rocket)

