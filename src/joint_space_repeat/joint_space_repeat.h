#ifndef JOINT_SPACE_REPEAT_H
#define JOINT_SPACE_REPEAT_H

// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The HomingExample class is a ControlPlugin
 * implementing a simple joint space motion repeatedly.
 */
class JointSpaceRepeat : public ControlPlugin
{

public:

    // we don't do anything special inside the
    // constructor, so just inherit the base class
    // implementation
    using ControlPlugin::ControlPlugin;

    // initialization method; the plugin won't be run
    // if this returns 'false'
    bool on_initialize() override;

    // callback for the 'Starting' state
    // start_completed() must be called to switch
    // to 'Run' state
    void starting() override;

    // callback for 'Run' state
    void run() override;

private:
    
    void set_control_mode();

    Eigen::VectorXd _q_a, _q_b, _q_start, _q_ref;
    double _motion_time;
    double _fake_time;
    bool _one_way_motion_in_execution = true;

};

#endif // JOINT_SPACE_REPEAT_H
