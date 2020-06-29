#ifndef ROCKET_ROS_H
#define ROCKET_ROS_H

#include <xbot2/ros/ros_device.h>
#include <std_msgs/Float64.h>

#include "rocket_device.h"

namespace XBot
{

class RocketRos : public RosDeviceRt
{

public:

    RocketRos(const Args& a);

private:

    void run_impl() override;

    std::map<std::string, ros::Publisher> _ref_pubs, _state_pubs;

    Hal::RocketBase* _rocket_group;
    std::map<std::string, Hal::RocketInstanceBase::Ptr> _rocket_map;

};

}
#endif // ROCKET_ROS_H
