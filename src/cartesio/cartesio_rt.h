#ifndef CARTESIO_RT_H
#define CARTESIO_RT_H

#include <xbot2/xbot2.h>
#include <cartesian_interface/CartesianInterfaceImpl.h>
#include <cartesian_interface/sdk/rt/LockfreeBufferImpl.h>
#include <cartesian_interface/ros/RosServerClass.h>

namespace XBot {

class CartesioRt : public ControlPlugin
{

public:

    using ControlPlugin::ControlPlugin;

    bool on_initialize() override;
    void starting() override;
    void run() override;
    void stopping() override;
    void on_abort() override;
    void on_close() override;

protected:

    std::unique_ptr<ros::NodeHandle> _nh;

    bool _enable_feedback;

    JointIdMap _qmap;
    Eigen::VectorXd _q, _qdot;
    ModelInterface::Ptr _rt_model;
    Cartesian::CartesianInterfaceImpl::Ptr _rt_ci;
    Cartesian::LockfreeBufferImpl::Ptr _nrt_ci;
    std::atomic_bool _rt_active;
    std::atomic_bool _nrt_exit;
    double _fake_time;

    std::unique_ptr<thread> _nrt_th;

    /* contraction mapping vars */

    Eigen::MatrixXd _Gj;
    Eigen::VectorXd _temp, _theta, _qprev, _qnew, _l, _g;

    /* methods */

    void update_model();
    void apply_contraction_mapping();
};


}

#endif // CARTESIO_RT_H
