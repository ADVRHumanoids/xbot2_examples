#ifndef MODEL_UTILS_H
#define MODEL_UTILS_H

#define MAX_ITERATIONS 4
#define FLEXIBILITY 0.00023

#include <xbot2/journal/journal.h>
#include <xbot2/robot_interface/robot_interface_xbot_rt.h>

/**/

namespace model_utils {

/*************************************************/

typedef Eigen::VectorXd                  vector   ;
typedef Eigen::MatrixXd                  matrix   ;
typedef XBot::ModelInterface::Ptr        model_ptr;

/**************************************************/

class elastic_joints
{

public:

    /**/
    
    matrix _Gj;
    vector _theta, _qprev, _qnew, _g, _temp;

    /**/

    elastic_joints() = delete;
    elastic_joints(model_ptr model)
    {
        /* todo: not hardcoded values... */

        int dofs = model->getJointNum();

        _Gj = FLEXIBILITY * matrix::Identity(dofs, dofs);
        _theta.setZero(dofs); _qprev.setZero(dofs); _qnew.setZero(dofs); _g.setZero(dofs); _temp.setZero(dofs);
    }

    /**/

    void apply(model_ptr model)
    {
        model->getJointPosition(_theta);
        
        for (unsigned char iteration = 0; iteration < MAX_ITERATIONS; iteration++)
        {
            model->getJointPosition(_qprev);
            model->computeGravityCompensation(_g);
    
            _temp.noalias() = - _Gj * _g;
            _qnew.noalias() = _temp + _theta;

            model->setJointPosition(_qnew);
            model->update();
        }
    }

};

} // namespace model_utils

#undef MAX_ITERATIONS
#undef FLEXIBILITY

#endif // MODEL_UTILS_H
