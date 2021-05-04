#include "logger_plugin.h"

bool LoggerPlugin::on_initialize()
{

    XBot::MatLogger2::Options opt;
    //    opt.enable_compression = true;
    opt.default_buffer_size = 1000;
    _logger = MatLogger2::MakeLogger("/tmp/logger_plugin_log", opt);
    _logger->set_buffer_mode(XBot::VariableBuffer::Mode::circular_buffer);


    auto ft = _robot->getDevices<Hal::ForceTorque>();

    for(auto d : ft.get_device_vector())
    {
        _ft_map.emplace_back(d.get());  /// TODO remove map
        //            std::cout << d << std::endl;
        //            jinfo("advertised ft topic for '{}' \\n", d->get_name());
    }

    auto imu = _robot->getDevices<Hal::Imu>();
    for(auto d : imu.get_device_vector())
    {
        _imu_vec.emplace_back(d.get());

        //            jinfo("advertised imu topic for '{}' \n", d->get_name());
    }

    auto lss = _robot->getDevices<Hal::LinkStateSensor>();

    std::string fb_name;
    _robot->model().getFloatingBaseLink(fb_name);

    for(auto d : lss.get_device_vector())
    {
        if (d->getLinkName() == fb_name)
            _fb = d.get();
    }


    // autostart?
    if(getParamOr("~autostart", true))
    {
        jinfo("setting autostart \n");
        setAutostart(true);
    }

    return true;
}

void LoggerPlugin::run()
{

    for(auto& ft : _ft_map)
    {
        ft->sense();
        _logger->add(ft->get_name(), ft->getWrench());
    }

    for(auto& imu : _imu_vec)
    {
        imu->sense();
        _logger->add(imu->get_name() + "_omega", imu->getAngularVelocity());
        _logger->add(imu->get_name() + "_lin_acc", imu->getLinearAcceleration());
        _logger->add(imu->get_name() + "_rot_xyzw", imu->getOrientation().coeffs());
    }

    _robot->sense();

    _robot->getJointPosition(_joint_pos);
    _robot->getJointVelocity(_joint_vel);
    _robot->getJointEffort(_joint_effort);

    _logger->add("joint_pos", _joint_pos);
    _logger->add("joint_vel", _joint_vel);
    _logger->add("joint_effort", _joint_effort);

    _fb->sense();

    _logger->add(_fb->getLinkName() + "_pos", _fb->getPose().translation());
    _logger->add(_fb->getLinkName() + "_rot", Eigen::Quaterniond(_fb->getPose().linear()).coeffs());
    _logger->add(_fb->getLinkName() + "_vel", _fb->getTwist());

    _logger->add("time", ros::Time::now().toSec());

}

XBOT2_REGISTER_PLUGIN(LoggerPlugin, logger_plugin)

