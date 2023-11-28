#ifndef PERIODIC_MOTION_H
#define PERIODIC_MOTION_H

// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The PeriodicMotion class is a ControlPlugin
 * implementing a simple homing motion.
 */
class PeriodicMotion : public ControlPlugin
{

public:

    // we don't do anything special inside the
    // constructor, so just inherit the base class
    // implementation
    using ControlPlugin::ControlPlugin;

    // initialization method; the plugin won't be run
    // if this returns 'false'
    bool on_initialize() override;

    // callback for switching to the 'Starting' state
    void on_start() override;

    // callback for 'Run' state
    void run() override;

private:
    
    Eigen::VectorXd _q_home_start, _q_home_end, _q_home, _q_start, _q_ref, _q_dot_ref;
    double _motion_time;
    double _fake_time;
    bool _start_to_end = true;

};

#endif // PERIODIC_MOTION_H
