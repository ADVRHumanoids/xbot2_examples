#include "albero_gripper.h"

#define MIN_CLICK_TIME 50
#define MAX_CLICK_TIME 500

using namespace XBot;
using namespace std::chrono_literals;

bool AlberoGripperRt::on_initialize()
{
    setJournalLevel(Journal::Level::Low);

    _grippers = _robot->getDevices <Hal::GripperBase> ();
    _buttons_boards = _robot->getDevices <Hal::ButtonsBoardBase> ();

    if (_grippers.empty())
    {
        XBOT2_WARN("albero gripper not found among devices");
        return false;
    }

    const double CRITICAL_DAMPING = 1.0;
    const double CUTOFF_FREQUENCY = 3.0;
    const double PERIOD = 0.001;

    for (const auto& gripper : _grippers.get_device_vector())
    {
        auto name = gripper->get_name();

        _filters[name] = std::make_shared <filter> ();

        _filters[name]->setTimeStep(PERIOD);
        _filters[name]->setDamping(CRITICAL_DAMPING);
        _filters[name]->setOmega(2.0 * M_PI * CUTOFF_FREQUENCY);
    }

    setup_ros();
    return true;
}

void AlberoGripperRt::set_closure_target(const std::string& name, const std_msgs::Float32& closure)
{
    XBOT2_INFO("closure reference for gripper {}: {}", name, closure.data);

    _targets[name] = closure.data;
}

void AlberoGripperRt::publish_state(const Hal::GripperBase::Ptr gripper) const
{
    auto name = gripper->get_name();
    auto state_msg = _state_publishers.at(name)->loanMessage();

    /* publish... if it could be done.. */
    if (state_msg)
    {
        /* todo: add link vel and other fields to published state! */
        state_msg->msg().motor_position = gripper->getMotorPosition();
        state_msg->msg().torque = gripper->getEffort();
        state_msg->msg().closure_reference = gripper->getClosureReference();

        _state_publishers.at(name)->publishLoaned(std::move(state_msg));
    }
}

void AlberoGripperRt::setup_ros()
{
    ros::NodeHandle nh(getName());

    _ros = std::make_unique<RosSupport>(nh);

    for (const auto& gripper : _grippers.get_device_vector())
    {
        gripper_state state_msg;

        auto name = gripper->get_name();
        auto function = std::bind(&AlberoGripperRt::set_closure_target, this, name, std::placeholders::_1);

        _closure_setters.push_back(_ros->subscribe <gripper_command> (name + "/closure", function, 1, &_queue));
        _state_publishers.emplace(name, _ros->advertise <gripper_state> (name + "/state", 1, state_msg));
    }

    for (const auto& board : _buttons_boards.get_device_vector())
    {
        auto btns_board = std::make_shared<Albero::GripperButtonsBoard> (_ros, MIN_CLICK_TIME, MAX_CLICK_TIME, board);

        _gripper_buttons_boards.push_back(btns_board);
    }

}

void AlberoGripperRt::starting()
{
    _start_time = clock_t::now();

    for (const auto& gripper : _grippers.get_device_vector())
    {
        auto name = gripper->get_name();
        auto target = gripper->getMotorPosition();

        _targets[name] = target;
        _filters[name]->reset(target);
    }

    start_completed();
}

void AlberoGripperRt::run()
{
    double time_since_start = chrono::to_sec(clock_t::now() - _start_time);

    _queue.run();

    for (const auto& gripper : _grippers.get_device_vector())
    {
        auto name = gripper->get_name();
        double target = _targets[name];

        gripper->sense();
        publish_state(gripper);

        double reference = _filters[name]->process(target);

        gripper->setClosureReference(reference);
        gripper->move();
    }

    for (const auto& buttons_board : _gripper_buttons_boards)
    {
        buttons_board->update(time_since_start);
    }
}

void AlberoGripperRt::stopping()
{
    stop_completed();
}

XBOT2_REGISTER_PLUGIN(AlberoGripperRt, albero_gripper_rt)

#undef MIN_CLICK_TIME
#undef MAX_CLICK_TIME
