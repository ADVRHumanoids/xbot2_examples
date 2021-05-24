#include "albero_cartesio_rt.h"


#define MAX_FC 0.99
#define LOW_FC 0.80
#define MIN_FC 0.10
#define ZERO   1e-5


using namespace XBot;
using namespace XBot::Cartesian;


double in_range(double value, double min, double max)
{
    return std::max(std::min(value, max), min);
}

bool AlberoCartesioRt::on_initialize()
{
    if (!CartesioRt::on_initialize())
    {
        return false;
    }

    /* ros stuff */
    // _gcomp_srv = _ros->advertiseService("gravity_compensation", &AlberoCartesioRt::trig_srv_handler, this, &_queue);

    /* get friction compensation gains */

    std::map<std::string, double> fc_map;
    
    double high_fc = MAX_FC, low_fc = LOW_FC;

    if (getParam("~fc_map", fc_map))
    {
        if (fc_map.count("low")) {
            low_fc = in_range(fc_map.at("low"), MIN_FC, MAX_FC);
        }
        
        if (fc_map.count("high")) {
            high_fc = in_range(fc_map.at("high"), MIN_FC, MAX_FC);
        }
    }

    /* set control mode */

    _robot->setControlMode(ControlMode::PosImpedance() + ControlMode::Effort());

    /* define profiles */

    int dofs = _rt_model->getJointNum();

    _default.init(dofs);
    _torque. init(dofs);
    _gravity.init(dofs);

    /* default profile: initial impedance, current position */

    Eigen::VectorXd k(dofs), d(dofs);

    _robot->getDamping(d);
    _robot->getStiffness(k);

    _default.d. set(d, true);
    _default.k. set(k, true);
    _default.fc.set(high_fc, true);

    /* torque profile: no impedance, high fc */
    
    _torque.d. set(0.0, true);
    _torque.k. set(0.0, true);
    _torque.fc.set(high_fc, true);

    /* gravity compensation profile: only torque with low fc */

    _gravity.d. set(0.0, true);
    _gravity.k. set(0.0, true);
    _gravity.fc.set(low_fc, true);

    return true;
}


void AlberoCartesioRt::starting()
{
    /* in case of torque control set the joint impedance to zero */

    _torque.activate(_robot);

    CartesioRt::starting();
}

void AlberoCartesioRt::run()
{
    CartesioRt::run();
    
    XBOT2_INFO_EVERY(1s, "stiffness:\n{}\ndamping:\n{}\nfc:\n{}", _torque.k.value, _torque.d.value, _torque.fc.value);
}

// bool AlberoCartesioRt::gravity_switch(std_srvs::SetBoolRequest& req, std_srvs::SetBoolResponse& res)
// {
//     std::shared_ptr<CollaborativeTask> ct;

//     ct = std::dynamic_pointer_cast<CollaborativeTask>(_rt_ci);

//     if (!ct)
//     {
//         res.success = false;
//         res.message = "non-collaborative task: gravity mode not available"
        
//         return false;
//     }

//     if (req.data)
//     {
//         _gravity.activate(_robot);
//         ct->enable_gravity();

//         res.success = true;
//         res.message = "gravity mode enabled";
//     }

//     else
//     {
//         _torque.activate(_robot);
//         ct->disable_gravity();

//         ct->res.success = true;
//         res.message = "gravity mode disabled";
//     }

//     return ct->res.success;
// }

/**/

profile::vectorial_item::vectorial_item()
{
    /**/
}

void profile::vectorial_item::init(uint dofs)
{
    update = false;
    value.setZero(dofs);
}

void profile::vectorial_item::set(vector& val, bool upd = false)
{
    update = upd;
    value = val;
}

void profile::vectorial_item::set(double val, bool upd = false)
{
    update = upd;
    value.setConstant(val);
}

/**/

profile::profile()
{
    /**/
}

void profile::init(const uint dof)
{
    diff.setZero(dof); current.setZero(dof);

    q.init(dof); dq.init(dof); k.init(dof);
    d.init(dof); fc.init(dof); t.init(dof);
}

void profile::activate(robot_ptr robot)
{
    /* TODO: let's remove duplicated code */

    if (d.update) {
        robot->setDamping(d.value);
    }

    if (k.update) {
        robot->setStiffness(k.value);
    }

    if (q.update) {
        robot->setPositionReference(q.value);
    }

    if (dq.update) {
        robot->setVelocityReference(dq.value);
    }

    robot->move();

    if (fc.update) {
        double fc_target = fc.value(0);
        auto ec_joints = robot->getDevices<Hal::JointEc>();

        for (auto joint : ec_joints.get_device_vector())
        {
            /* now we just set the same fc for all the fc joints */
            joint->setFrictionCompensation(fc_target);
            joint->move();
        }
    }
}

bool profile::reached(robot_ptr robot)
{
    /* TODO: let's remove duplicated code */

    bool check = true;

    if (d.update)
    {
        robot->getDamping(current);
        diff = current - d.value;

        check &= diff.norm() < ZERO;
    }

    if (k.update)
    {
        robot->getStiffness(current);
        diff = current - k.value;

        check &= diff.norm() < ZERO;
    }

    if (q.update)
    {
        robot->getPositionReference(current);
        diff = current - q.value;

        check &= diff.norm() < ZERO;
    }

    if (dq.update)
    {
        robot->getVelocityReference(current);
        diff = current - dq.value;

        check &= diff.norm() < ZERO;
    }

    if (fc.update)
    {
        double fc_target = fc.value(0);
        auto ec_joints = robot->getDevices<Hal::JointEc>();

        for (auto joint : ec_joints.get_device_vector()) {
            double fc_current = joint->getFrictionCompensation();
            check &= abs(fc_current - fc_target) < ZERO;
        }
    }

    return check;
}

XBOT2_REGISTER_PLUGIN(AlberoCartesioRt, albero_cartesio_rt)

#undef MAX_FC
#undef LOW_FC
#undef MIN_FC
#undef ZERO
