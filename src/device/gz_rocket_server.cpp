#include "gz_rocket_server.h"

#include <random>

using namespace XBot;
using namespace XBot::Hal;

class RocketInstanceGz : public Hal::DeviceInstanceTplCommon<RocketPacket::Rx,
                                                             RocketPacket::Tx>
{

public:

    typedef DeviceInstanceTplCommon<RocketPacket::Rx,
                                    RocketPacket::Tx> BaseType;

    RocketInstanceGz(Hal::DeviceInstanceInfo devinfo,
                     gz::physics::LinkPtr gz_joint);

    bool sense() override;

    bool move() override;

private:

    gz::physics::LinkPtr _gz_link;

    float _force_to_gz;

    std::default_random_engine _generator;

    std::normal_distribution<float> _distribution;


};

GzRocketServer::GzRocketServer()
{

}

void XBot::GzRocketServer::Load(gz::physics::ModelPtr model,
                                sdf::ElementPtr sdf)
{
    auto rocket_link = sdf->GetElement("link_name")->GetValue()->GetAsString();

    // NOTE: hardcoded name and id
    DeviceInstanceInfo devinfo{"rocket_0", "rocket", 100};

    auto rocket_instance = std::make_shared<RocketInstanceGz>(
        devinfo,
        model->GetLink(rocket_link));

    _rocket_vec.push_back(rocket_instance);

    /* Create joint server manager */
    _srv =  std::make_unique<ServerManager>(_rocket_vec,
                                           "shm",
                                           "rocket");


    /* Register update callback */
    _gz_world_upd_begin_connection = gz::event::Events::ConnectWorldUpdateBegin(
        [this](const auto& info)
        {
            this->on_gz_world_upd_begin(info);
        });

}

void GzRocketServer::on_gz_world_upd_begin(const gz::common::UpdateInfo& /* info */)
{
    for(auto& rock : _rocket_vec)
    {
        rock->sense();
    }

    _srv->run();

    _srv->send();

    for(auto& rock : _rocket_vec)
    {
        rock->move();
    }
}



RocketInstanceGz::RocketInstanceGz(DeviceInstanceInfo devinfo,
                                   gz::physics::LinkPtr gz_link):
    BaseType(devinfo),
    _gz_link(gz_link),
    _force_to_gz(0.0),
    _distribution(0.0, 5.0)
{
}

bool RocketInstanceGz::sense()
{
    _rx.force_ref = _tx.force_ref;
    _rx.force_meas = _force_to_gz;
    return true;
}

bool RocketInstanceGz::move()
{
    _force_to_gz = _tx.force_ref + _distribution(_generator);

    _gz_link->SetForce(ignition::math::Vector3d(0, 0, _force_to_gz));

    return true;
}

GZ_REGISTER_MODEL_PLUGIN(GzRocketServer)
