#include "rocket_ros.h"

using namespace XBot;

RocketRos::RocketRos(const RosDeviceRt::Args& a):
    RosDeviceRt(a)
{
    _rocket_group = dynamic_cast<Hal::RocketBase*>(_device);

    if(!_rocket_group)
    {
        throw std::runtime_error("Device is not of type Hal::RocketBase");
    }

    for(auto rn : _rocket_group->get_names())
    {
        auto r = _rocket_group->get_device_instance_base_typed(rn);

        _rocket_map[rn] = r;

        auto pubref = _nh.advertise<std_msgs::Float64>(
            "rocket/" + rn + "/current_reference",
            1);

        _ref_pubs[rn] = pubref;

        auto pubstate = _nh.advertise<std_msgs::Float64>(
            "rocket/" + rn + "/state",
            1);

        _state_pubs[rn] = pubstate;

    }
}


void XBot::RocketRos::run_impl()
{
    if(!_rocket_group->sense())
    {
        return;
    }

    for(const auto& p : _rocket_map)
    {
        std_msgs::Float64 msg;
        msg.data = p.second->getThrust();
        _state_pubs.at(p.first).publish(msg);

        msg.data = p.second->getReference();
        _ref_pubs.at(p.first).publish(msg);
    }
}

XBOT2_REGISTER_ROSDEV(RocketRos, rocket_rt)
