#include "gcomp_example.h"

using namespace XBot;

bool GcompExample::on_initialize()
{
    // get impedance ramping time from yaml parameters
    _imp_ramp_time = getParamOr<double>("~impedance_ramp_time", 2.0);

    // save initial impedance
    _robot->getStiffness(_k0);
    _robot->getDamping(_d0);

    // final impedance is zero
    _kf.setConstant(_k0.size(), 0.0);
    _df.setConstant(_d0.size(), 0.0);

    // save joint limits
    _robot->getJointLimits(_qmin, _qmax);

    // paranoid: decrease the joint range a bit
    _qmin = _qmin.array() + 0.01;
    _qmax = _qmax.array() - 0.01;

    // set control mode
    // in this example, we provide the possibility to customize the set of joints
    // that this plugin actually commands
    std::vector<std::string> enabled_chains;
    if(!getParam("~enabled_chains", enabled_chains))
    {
        jerror("no chain enabled (parameter ~enabled_chains is empty)");
        return false;
    }

    // note: we just send feedforward torque -> control mode is 'effort'
    for(auto ch : enabled_chains)
    {
        for(auto jn : _robot->chain(ch).getJointNames())
        {
            jinfo("enabling joint {}", jn);
            _ctrl_map[jn] = ControlMode::Effort();
        }
    }

    for (auto jn: _robot->getEnabledJointNames())
    {
        jinfo("joint {} in {} mode", jn, _ctrl_map[jn].getName());
    }

    // set default control mode:
    // upon start, the framework will try to acquire the specified
    // resource from the underlying device
    // on failure, plugin cannot start
    setDefaultControlMode(_ctrl_map);

    return true;

}

void GcompExample::on_start()
{
    // set time to 0
    _time = 0;

    // save initial qref
    _robot->sense();
    _robot->getPositionReference(_qref0);

    // print
    jhigh().jinfo("ramping down impedance in {} seconds", _imp_ramp_time);
}

void GcompExample::starting()
{
    // normalized time
    double tau = _time/_imp_ramp_time;

    if(tau > 1.0)
    {
        jhigh().jinfo("ramping down impedance completed");
        start_completed();
        _state = CONNECT_QREF;
        _time = 0;
        return;
    }

    // quintic poly 6t^5 - 15t^4 + 10t^3
    double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

    // compute impedance trajectory
    _k.noalias() = (1 - alpha)*_k0 + alpha*_kf;
    _d.noalias() = (1 - alpha)*_d0 + alpha*_df;

    // compute gcomp torque
    _robot->model().computeGravityCompensation(_tauref);
    _tauref *= alpha;
    _robot->model().setJointEffort(_tauref);

    // send to robot
    _robot->setStiffness(_k);
    _robot->setDamping(_d);
    _robot->setReferenceFrom(_robot->model(), Sync::Effort);
    _robot->move();

    // increment time
    _time += getPeriodSec();
}

void GcompExample::run()
{
    // keep qref updated
    _robot->sense();
    _robot->getJointPosition(_q);

    if(_state == CONNECT_QREF)
    {
        // normalized time
        double tau = _time/_imp_ramp_time;

        if(tau >= 1.0)
        {
            _state = RUNNING;
        }

        // quintic poly 6t^5 - 15t^4 + 10t^3
        double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

        // compute smooth qref
        _qref = (1 - alpha)*_qref0 + alpha*_q;

        // increment time
        _time += getPeriodSec();
    }
    else
    {
        _qref = _q;
    }

    // keep always qref inside range
    _qref = _qref.cwiseMin(_qmax).cwiseMax(_qmin);
    
    // compute gcomp torque
    _robot->model().computeGravityCompensation(_tauref);
    _robot->model().setJointEffort(_tauref);

    // send to robot
    _robot->setPositionReference(_qref);
    _robot->setStiffness(_k);
    _robot->setDamping(_d);
    _robot->setReferenceFrom(_robot->model(), Sync::Effort);
    _robot->move();
}

void GcompExample::on_stop()
{
    // set time to 0
    _time = 0;

    jhigh().jinfo("ramping up impedance in {} seconds", _imp_ramp_time);
}

void GcompExample::stopping()
{
    // normalized time
    double tau = _time/_imp_ramp_time;

    if(tau > 1.0)
    {
        jhigh().jinfo("ramping up impedance completed");
        stop_completed();
        return;
    }

    // quintic poly 6t^5 - 15t^4 + 10t^3
    double alpha = ((6*tau - 15)*tau + 10)*tau*tau*tau;

    // compute impedance
    _k.noalias() = (1 - alpha)*_kf + alpha*_k0;
    _d.noalias() = (1 - alpha)*_df + alpha*_d0;

    // compute gcomp torque
    _robot->sense();
    _robot->model().computeGravityCompensation(_tauref);
    _tauref *= std::min(1.0, 4*(1 - alpha));
    _robot->model().setJointEffort(_tauref);

    // send to robot
    _robot->setPositionReference(_qref);
    _robot->setStiffness(_k);
    _robot->setDamping(_d);
    _robot->setReferenceFrom(_robot->model(), Sync::Effort);
    _robot->move();

    // increment time
    _time += getPeriodSec();
}

void XBot::GcompExample::on_abort()
{
    // send to robot
    _robot->setStiffness(_k0);
    _robot->setDamping(_d0);
    _robot->move();
}

XBOT2_REGISTER_PLUGIN(GcompExample, gcomp_example)
