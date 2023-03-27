#ifndef XBOT2_GZ_ROCKET_SERVER_H
#define XBOT2_GZ_ROCKET_SERVER_H

#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>

#include <xbot2/client_server/server_manager.h>

#include "rocket_packet.h"

namespace XBot {

class GzRocketServer : public gazebo::ModelPlugin
{

public:

    GzRocketServer();

    /* ModelPlugin interface */
    void Load(gazebo::physics::ModelPtr model,
              sdf::ElementPtr sdf) override;

private:

    void on_gz_world_upd_begin(const gazebo::common::UpdateInfo& _info);

    gazebo::event::ConnectionPtr _gz_world_upd_begin_connection;

    std::vector<Hal::DeviceRt::Ptr> _rocket_vec;
    ServerManager::UniquePtr _srv;
};

}
#endif // XBOT2_GZ_JOINT_SERVER_H
