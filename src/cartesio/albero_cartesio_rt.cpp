#include "albero_cartesio_rt.h"


#define MAX_FC 0.99
#define LOW_FC 0.80
#define MIN_FC 0.10
#define ZERO   1e-5


using namespace XBot;
using namespace XBot::Cartesian;


/* parsing parameters... */

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


void AlberoCartesioRt::setup_ros()
{
    ros::NodeHandle nh(getName());
    _ros = std::make_unique<RosSupport>(nh);

    _gravity_setter  = _ros->advertiseService("gcomp_switch", &AlberoCartesioRt::gcomp_switch_callback, this, &_queue);
    _gravity_getter  = _ros->advertiseService("gcomp_state", &AlberoCartesioRt::gcomp_get_callback, this, &_queue);
}


bool AlberoCartesioRt::gcomp_switch_callback(const std_srvs::SetBoolRequest& req, std_srvs::SetBoolResponse& res)
{
    std::shared_ptr <Cartesian::CartesioImpedance> ci = std::dynamic_pointer_cast<Cartesian::CartesioImpedance> (_rt_ci);

    if (!ci)
    {
        res.success = false;
        res.message = "INVALID CI";

        return false;
    }

    res.success = ci->userCommand(req.data);

    /* When the service is called, the state on the ci is changed.
       The state is read on every control loop and the FC is set accordingly.
       We don't change the FC here because we experienced that sometimes it is
       not set on all the joints. That's why we update it every control loop. */

    if(req.data) {
        res.message = "GCOMP_MODE";

        XBOT2_INFO("gcomp mode enabled");

        _gravity.activate(_robot);
    }

    else {
        res.message = "IMPEDANCE_MODE";

        XBOT2_INFO("impedance mode enabled");

        _rt_ci->reset(_fake_time);
        _torque.activate(_robot);
    }

    return true;
}

bool AlberoCartesioRt::gcomp_get_callback(const xbot_msgs::PluginStatusRequest& req, xbot_msgs::PluginStatusResponse& res)
{
    std::shared_ptr <Cartesian::CartesioImpedance> ci = std::dynamic_pointer_cast<Cartesian::CartesioImpedance> (_rt_ci);

    if (!ci)
    {
        res.status = "UNAVAILABLE";
        return false;
    }

    res.status = ci->getState();
    return true;
}

/* plugin methods... */

bool AlberoCartesioRt::on_initialize()
{
    if (!CartesioRt::on_initialize())
    {
        return false;
    }

    /* get friction compensation gains */

    double low_fc, high_fc;

    get_fc_values(low_fc, high_fc);

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

    setup_ros();

    return true;
}


void AlberoCartesioRt::starting()
{
    /* we use a fake time, and integrate it by the expected dt */
    _fake_time = 0;

    /* update the model */
    CartesioRt::update_model();

    /* reset ci */
    _rt_ci->reset(_fake_time);

    /* in case of torque control set the joint impedance to zero */
    _torque.activate(_robot);

    /* signal nrt thread that rt is active */
    _rt_active = true;

    /* transit to run */
    start_completed();
}

void AlberoCartesioRt::run()
{
    CartesioRt::run();

    _queue.run();
}

/*
void AlberoCartesioRt::stopping()
{
    XBOT2_INFO("stopping");

    CartesioRt::update_model();

    _robot->getJointPosition(_default.q.value);
    _default.q.update = true;

    _default.activate(_robot);

    CartesioRt::stopping();
}


void AlberoCartesioRt::on_abort()
{
    XBOT2_INFO("abort");

    CartesioRt::update_model();

    _robot->getJointPosition(_default.q.value);
    _default.q.update = true;

    _default.activate(_robot);

    CartesioRt::on_abort();
}


void AlberoCartesioRt::on_close()
{
    XBOT2_INFO("close");

    CartesioRt::update_model();

    _robot->getJointPosition(_default.q.value);
    _default.q.update = true;

    _default.activate(_robot);

    CartesioRt::on_close();
}

*/

/*************************************************************/

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

profile::profile() : Journal("profile logger")
{
    setJournalLevel(Journal::Level::Low);
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
        XBOT2_INFO("damp updated: {}", d.value);
        robot->setDamping(d.value);
    }

    if (k.update) {
        XBOT2_INFO("stiff updated: {}", k.value);
        robot->setStiffness(k.value);
    }

    if (q.update) {
        XBOT2_INFO("pos updated: {}", q.value);
        robot->setPositionReference(q.value);
    }

    if (dq.update) {
        XBOT2_INFO("vel updated: {}", dq.value);
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
