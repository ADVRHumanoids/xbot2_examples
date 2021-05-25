#ifndef ALBERO_CARTESIO_RT_H
#define ALBERO_CARTESIO_RT_H


#include "partition.h"
#include "cartesio_rt.h"
#include <ec_xbot2/joint_ec.h>
#include <xbot2/ros/ros_support.h>
#include <xbot2/robot_interface/robot_interface_xbot_rt.h>

#include <std_srvs/SetBool.h>
#include <std_srvs/Empty.h>

namespace XBot {

class profile
{
    private:

        /* typedefs */

        typedef Eigen::VectorXd vector;
        typedef RobotInterfaceXBot2Rt::Ptr robot_ptr;

        /* internal structure */

        struct vectorial_item
        {
            /* data members */

            bool   update;
            vector value ;

            /* constructors */

            vectorial_item();

            /* methods */

            void init(uint dofs);

            void set(vector & val, bool upd);
            void set(double   val, bool upd);
        };

        /* data members */

        vector current, diff;

    public:

        /* data members */

        vectorial_item q, dq, k, d, fc, t;

        /* constructor */

        profile();

        /* methods */

        void init(const uint dof);
        void activate(robot_ptr robot);
        bool reached(robot_ptr robot);
};

class AlberoCartesioRt : public CartesioRt
{

public:
    
    using CartesioRt::CartesioRt;

    bool on_initialize() override;
    void starting() override;
    void run() override;

private:

    /* data members */

    profile _default, _torque, _gravity;

    /* ros from rt */

    CallbackQueue _queue;
    RosSupport::UniquePtr _ros;
    ServiceServerPtr<std_srvs::SetBoolRequest, std_srvs::SetBoolResponse> _gcomp_srv;

    /* methods */
    
    void update_model();
    bool gravity_switch(std_srvs::SetBoolRequest& req, std_srvs::SetBoolResponse& res);
    void get_fc_values(double & low_fc, double & high_fc);

    /* new stuff...*/

    std::vector<partition::context::ptr> _partitions;

};

}

#endif // CARTESIO_RT_H
