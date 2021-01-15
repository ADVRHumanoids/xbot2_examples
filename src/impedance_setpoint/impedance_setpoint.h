#ifndef IMPEDANCE_SETPOINT_H
#define IMPEDANCE_SETPOINT_H

// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The ImpedanceSetpoint class is a ControlPlugin
 * that sets the joint impedance to a setpoint
 */
class ImpedanceSetpoint : public ControlPlugin
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

    Eigen::VectorXd _k_home, _k_start, _k_ref;
    Eigen::VectorXd _d_home, _d_start, _d_ref;
    double _trj_time;
    double _fake_time;

};

#endif // IMPEDANCE_SETPOINT_H
