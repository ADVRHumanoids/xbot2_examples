#include "joint_impedance.h"

bool JointImpedance::on_initialize()
{

    /* Initialize variables */
    _robot->getMotorPosition(_q);
    _robot->getPositionReference(_qref);
    _kp = _kd = _tau = _dq.setZero(_robot->getJointNum());


    /* Manage control mode */
    _robot->setControlMode(ControlMode::Idle());

    auto control_joints = getParamOrThrow<std::vector<std::string>>("~control_joints");

    jinfo("will control joints {} \n",
          fmt::join(control_joints, ", "));



    for(auto j : control_joints)
    {
        if(!_robot->hasJoint(j))
        {
            jerror("invalid joint '{}' \n", j);
            return false;
        }

        _ctrl_map[j] = ControlMode::Effort();
    }

    setDefaultControlMode(_ctrl_map);


    /* Gains */
    double kp = 100;
    double kd = 1.0;

    getParam("~kp", kp);
    getParam("~kd", kd);

    _kp.setConstant(_kp.size(), kp);
    _kd.setConstant(_kd.size(), kd);

    return true;
}

void JointImpedance::on_start()
{
    // initialize qref
    _robot->sense();
    _robot->getPositionReference(_qref);
}

void JointImpedance::run()
{
    _robot->sense(false);
    _robot->getMotorPosition(_q);
    _robot->getPositionReference(_qref);
    _robot->getMotorVelocity(_dq);

    _tau = _kp.cwiseProduct(_qref - _q) - _kd.cwiseProduct(_dq);
    _robot->setEffortReference(_tau);

    _robot->move();
}

void JointImpedance::stopping()
{
    _tau.setZero(_tau.size());
    _robot->setEffortReference(_tau);
    _robot->move();
    stop_completed();
}

XBOT2_REGISTER_PLUGIN(JointImpedance, joint_impedance)
