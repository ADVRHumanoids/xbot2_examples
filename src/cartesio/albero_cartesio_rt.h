#ifndef ALBERO_CARTESIO_RT_H
#define ALBERO_CARTESIO_RT_H

#define ZERO 1e-20

#include "cartesio_rt.h"
#include <ec_xbot2/joint_ec.h>
#include <xbot2/robot_interface/robot_interface_xbot_rt.h>

namespace XBot {

class AlberoCartesioRt : public CartesioRt
{

public:
    
    using CartesioRt::CartesioRt;

    bool on_initialize() override;
    void starting() override;
    void run() override;
    
    // void on_start() override;
    // void stopping() override;
    // void on_abort() override;
    // void on_close() override;

private:

    /* data members */

    profile _at_start, _at_run;

    /* methods */
    
    void updateModel();

    /* utils */

};

class profile
{
    private:

        typedef Eigen::VectorXd vector;
        typedef RobotInterfaceXBot2Rt::Ptr robot_ptr;
        
        struct vectorial_item
        {
            bool update;
            vector value;
            
            /* constructors */

            vectorial_item() {}

            init(uint dofs, bool upd = false)
            {
                update = upd;
                value.setZero(dofs);
            }

            init(vector& val, bool upd = false)
            {
                update = upd;
                value = val;
            }

            init(uint dofs, double val, bool upd = false)
            {
                update = upd;
                value.setConstant(dofs, val);
            }
        };

        /* data members */
        vector current, diff;
        
    public:
        
        /* data members */

        vectorial_item q, dq, k, d, fc, t;

        /* methods */
        
        profile() {}

        init(const uint dof)
            : q(dof), dq(dof), k(dof), d(dof), fc(dof), t(dof)
        {
            diff.setZero(dof); current.setZero(dof);
            q.init(dof); dq.init(dof); k.init(dof); d.init(dof); fc.init(dof); t.init(dof);
        }
        
        void update_robot(robot_ptr robot)
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
                robot->setPositionReference(dq.value);
            }
            
            if (fc.update) {
                double fc_target = fc.value(0);
                auto ec_joints = robot->getDevices<Hal::JointEc>();

                for (auto joint : ec_joints.get_device_vector()) {
                    /* kiss: now we just set the same fc for all the fc joints */
                    joint->setFrictionCompensation(fc_target);
                }
            }
        }

        bool reached(robot_ptr robot)
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
                    /* kiss: now we just set the same fc for all the fc joints */
                    double fc_current = joint->getFrictionCompensation();

                    check &= abs(fc_current - fc_target) < ZERO;
                }
            }

            return check;
        }
};

}

#undef ZERO
#endif // CARTESIO_RT_H
