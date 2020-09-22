#ifndef JOINT_IMPEDANCE_H
#define JOINT_IMPEDANCE_H

// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The JointImpedance class is a ControlPlugin
 * implementing a simple joint impedance control on top
 * of the robot torque interface
 */
class JointImpedance : public ControlPlugin
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

    // callback for the 'Stopping' state
    void stopping() override;

private:

    Eigen::VectorXd _q, _qref, _dq, _kp, _kd, _tau;

};

#endif // HOMING_EXAMPLE_H
