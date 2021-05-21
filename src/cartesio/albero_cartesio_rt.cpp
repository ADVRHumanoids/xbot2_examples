#include "albero_cartesio_rt.h"


using namespace XBot;
using namespace XBot::Cartesian;


bool AlberoCartesioRt::on_initialize()
{
    if (!CartesioRt::on_initialize()) {
        return false;
    }

    std::map<std::string, double> fc_map;

    double high_fc = 0.99, low_fc = 0.80;
    if (getParam("~fc_map", fc_map))
    {
        if (fc_map.count("high"))
        fc_map.
        fc_map.at("high")
    }

    _robot->setControlMode(ControlMode::PosImpedance() + ControlMode::Effort());

    int dofs = _rt_model->getJointNum();

    _start.init (dofs);
    _torque.init(dofs);

    _torque.d.update(0, true);
    _torque.k.update(0, true);

    return true;
}


void AlberoCartesioRt::starting()
{
    /* in case of torque control set the joint impedance to zero */

    if (_enable_feedback)
    {
        _robot->setDamping  (_z);
        _robot->setStiffness(_z);
        _robot->move();
    }

    CartesioRt::starting();
}

void AlberoCartesioRt::run()
{
    CartesioRt::run();

    XBOT2_INFO_EVERY(1s, "stiffness:\n{}\ndamping:\n{}", _k, _d);
}

XBOT2_REGISTER_PLUGIN(AlberoCartesioRt,
                      albero_cartesio_rt);

#undef ZERO