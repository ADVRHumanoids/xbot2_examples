#ifndef GCOMPEXAMPLE_H
#define GCOMPEXAMPLE_H

#include <xbot2/rt_plugin/control_plugin.h>

namespace XBot {

class GcompExample : public ControlPlugin
{

public:

    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;
    void on_start() override;
    void starting() override;
    void run() override;
    void on_stop() override;
    void stopping() override;
    void on_abort() override;

private:

    enum State {
        CONNECT_QREF,
        RUNNING
    };

    State _state;

    std::map<std::string, ControlMode> _ctrl_map;

    double _imp_ramp_time;
    double _time;
    Eigen::VectorXd _qmin, _qmax;
    Eigen::VectorXd _k0, _d0;
    Eigen::VectorXd _kf, _df;
    Eigen::VectorXd _k, _d;
    Eigen::VectorXd _qref, _qref0, _q;
    Eigen::VectorXd _tauref;

};

}

#endif // GCOMPEXAMPLE_H
