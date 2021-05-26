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

void AlberoCartesioRt::get_fc_values(double & low_fc, double & high_fc)
{
    std::map<std::string, double> fc_map;

    high_fc = MAX_FC; low_fc  = LOW_FC;

    if (getParam("~fc_map", fc_map))
    {
        if (fc_map.count("low")) {
            low_fc = in_range(fc_map.at("low"), MIN_FC, MAX_FC);
        }

        if (fc_map.count("high")) {
            high_fc = in_range(fc_map.at("high"), MIN_FC, MAX_FC);
        }
    }
}


void AlberoCartesioRt::create_ros_services(std::string partition_name)
{
    using setter = std::function <bool(const trequest&, tresponse&)>;

    setter gravity_setter  = std::bind(&AlberoCartesioRt::gravity_switch2 , this, std::placeholders::_1, std::placeholders::_2, partition_name);
    setter cartesio_setter = std::bind(&AlberoCartesioRt::cartesio_switch2, this, std::placeholders::_1, std::placeholders::_2, partition_name);

    _gravity_setter  = _ros->advertiseService(partition_name + "/" + "gravity_mode"       , gravity_setter , &_queue);
    _cartesio_setter = _ros->advertiseService(partition_name + "/" + "cartesian_task_mode", cartesio_setter, &_queue);
}


bool AlberoCartesioRt::on_initialize()
{
    if (!CartesioRt::on_initialize())
    {
        return false;
    }

    /* get friction compensation gains */

    double low_fc, high_fc;

    get_fc_values(low_fc, high_fc);

    /////////////////////// currently not used ////////////////////////

    for (auto partition_name : {std::string("robot_1")})
    {
        /* now we consider just one hardcoded partition, but in the future we may want more robots... */

        int dofs = _rt_model->getJointNum();

        partition::vector k(dofs), d(dofs);

        _robot->getDamping(d); _robot->getStiffness(k);

        auto steady_st    = std::make_shared<partition::states::steady   >(dofs, k, d, high_fc);
        auto safety_st    = std::make_shared<partition::states::safety   >(dofs,       low_fc );
        auto gravity_st   = std::make_shared<partition::states::gravity  >(dofs,       low_fc );
        auto operative_st = std::make_shared<partition::states::operative>(dofs,       high_fc);

        auto ctx = std::make_shared<partition::context>(_robot, _rt_model, operative_st, safety_st, gravity_st, steady_st);

        _partitions.emplace(partition_name, ctx);

        create_ros_services(partition_name);
    }

    ////////////////////////////////////////////////////////////////////

    int dofs = _rt_model->getJointNum();

    /* set control mode */

    _robot->setControlMode(ControlMode::PosImpedance() + ControlMode::Effort());

    /* define profiles */

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
    
//    XBOT2_INFO_EVERY(1s, "stiffness:\n{}\ndamping:\n{}\nfc:\n{}", _torque.k.value, _torque.d.value, _torque.fc.value);
}

bool AlberoCartesioRt::gravity_switch2(const trequest&, tresponse& res, std::string partition_name)
{
    res.success = false;
    res.message = "invalid partition";

    if (_partitions.count(partition_name))
    {
        auto partition = _partitions.at(partition_name);

        res.success = partition->enable_gravity_mode();
        res.message = res.success ? "transition succeded" : "invalid transition";
    }

    XBOT2_INFO("gravity switch:\npartition: {}\nsuccess: {}\nmessage: {}", partition_name, res.success, res.message);

    return res.success;
}

bool AlberoCartesioRt::cartesio_switch2(const trequest&, tresponse& res, std::string partition_name)
{
    res.success = false;
    res.message = "invalid partition";

    if (_partitions.count(partition_name))
    {
        auto partition = _partitions.at(partition_name);

        res.success = partition->enable_operative_mode();
        res.message = res.success ? "transition succeded" : "invalid transition";
    }

    XBOT2_INFO("cartesio switch:\npartition: {}\nsuccess: {}\nmessage: {}", partition_name, res.success, res.message);

    return res.success;
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

    robot->setControlMode(ControlMode::Effort());
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
