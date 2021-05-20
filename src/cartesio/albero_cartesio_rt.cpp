#include "albero_cartesio_rt.h"

using namespace XBot;
using namespace XBot::Cartesian;


bool AlberoCartesioRt::on_initialize()
{
    if (!CartesioRt::on_initialize()) {
        return false;
    }

    _robot->setControlMode(ControlMode::PosImpedance() + ControlMode::Effort());

    int dofs = _rt_model->getJointNum();

    _k.setZero(dofs);
    _d.setZero(dofs);
}

void AlberoCartesioRt::starting()
{
    // _robot->sense(false);

    // /* get the starting values of the joint impedance */

    // _robot->getDamping(_d);
    // _robot->getStiffness(_k);

    // /* in case of torque control set the joint impedance to zero */

    // if (_enable_feedback)
    // {
    //     _robot->setDamping(_k * 0.0);
    //     _robot->setStiffness(_d * 0.0);
    // }

    // _robot->move();

    // _robot->getDamping(_d);
    // _robot->getStiffness(_k);

    // XBOT2_INFO("stiffness:\n{}\ndamping:\n{}", _k, _d);

    CartesioRt::starting();
}

void AlberoCartesioRt::run()
{
    CartesioRt::run();
    
    // _robot->getDamping(_d);
    // _robot->getStiffness(_k);

    XBOT2_INFO_EVERY(10s, "stiffness:\n{}\ndamping:\n{}", 3, 2);
}

XBOT2_REGISTER_PLUGIN(AlberoCartesioRt,
                      albero_cartesio_rt);
