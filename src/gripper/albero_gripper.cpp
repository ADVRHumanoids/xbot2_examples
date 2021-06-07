#include "albero_gripper.h"

using namespace XBot;
using namespace std::chrono_literals;

bool AlberoGripperRt::on_initialize()
{
    setJournalLevel(Journal::Level::Low);

    _grippers = _robot->getDevices <Hal::GripperBase> ();

    if (_grippers.empty())
    {
        XBOT2_WARN("albero gripper not found among devices");
        return false;
    }

    setup_ros();
    return true;
}

void AlberoGripperRt::set_closure_reference(const std::string name, const std_msgs::Float32& closure)
{
    XBOT2_INFO("closure reference for gripper {}: {}", name, closure);

    auto gripper = _grippers.get_device(name);

    gripper->setClosureReference(closure.data);
    gripper->move();
}

void AlberoGripperRt::setup_ros()
{
    ros::NodeHandle nh(getName());

    _ros = std::make_unique<RosSupport>(nh);

    for (const auto& gripper : _grippers.get_device_vector())
    {
        auto name = gripper->get_name();
        auto function = std::bind(&AlberoGripperRt::set_closure_reference, this, name, std::placeholders::_1);

        _closure_setters.push_back(_ros->subscribe <std_msgs::Float32> (name + "/closure", function, 1, &_queue));
    }
}

void AlberoGripperRt::starting()
{
    _start_time = clock_t::now();

    start_completed();
}

void AlberoGripperRt::run()
{
    double time_since_start = chrono::to_sec(clock_t::now() - _start_time);

    _queue.run();

    XBOT2_INFO_EVERY(2s, "albero gripper plugin is running");

    for (const auto& gripper : _grippers.get_device_vector())
    {
        gripper->sense();

        XBOT2_INFO_EVERY(2s, "motor position: {}\nmotor reference: {}", gripper->getMotorPosition(), gripper->getClosureReference());
    }
}

void AlberoGripperRt::stopping()
{
    stop_completed();
}

XBOT2_REGISTER_PLUGIN(AlberoGripperRt, albero_gripper_rt)
