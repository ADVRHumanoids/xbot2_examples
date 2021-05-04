#ifndef LOGGERPLUGIN_H
#define LOGGERPLUGIN_H

#include <xbot2/xbot2.h>
#include <matlogger2/matlogger2.h>
#include <xbot2/gazebo/dev_link_state_sensor.h>
#include <ros/time.h>

using namespace XBot;

class LoggerPlugin : public ControlPlugin
{

public:

    // we don't do anything special inside the
    // constructor, so just inherit the base class
    // implementation
    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;

    // callback for the 'Starting' state
    // start_completed() must be called to switch
    // to 'Run' state
//    void starting() override;

    // callback for 'Run' state
    void run() override;

private:

    MatLogger2::Ptr _logger;
    Hal::LinkStateSensor* _fb;

    std::vector<Hal::ForceTorque*> _ft_map;

    std::vector<Hal::Imu*> _imu_vec;

    Eigen::VectorXd _joint_pos, _joint_vel, _joint_effort;
//    std::string _fb_name;
//    Eigen::Affine3d _fb_pose;
//    Eigen::Vector6d _fb_vel;

};

#endif // LOGGER_H
