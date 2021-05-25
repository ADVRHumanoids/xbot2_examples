#include "partition.h"


using namespace partition;


control_params::control_params(uint dofs)
{
    _fc = 0.0;

    _t.setZero(dofs);
    _k.setZero(dofs); _d.setZero (dofs);
    _q.setZero(dofs); _dq.setZero(dofs);
}


void control_params::apply(robot_ptr robot)
{
    robot->setDamping          (_d );
    robot->setStiffness        (_k );
    robot->setEffortReference  (_t );
    robot->setPositionReference(_q );
    robot->setVelocityReference(_dq);

    // robot->setFrictionCompensation(_fc);
}


/*******************************************/


partition::context::context(robot_ptr robot    ,
                            model_ptr model    ,
                            state_ptr operative,
                            state_ptr safety   ,
                            state_ptr gravity  ,
                            state_ptr steady   )
    : _state    (steady   )
    , _robot    (robot    )
    , _model    (model    )
    , _safety   (safety   )
    , _gravity  (gravity  )
    , _steady   (steady   )
    , _operative(operative)
{
    /* we pre-define all the states to avoid memory allocation in the control loop. */
}

void partition::context::go_to(state_ptr state)
{
    _state->exit ();

    /**/

    _state = state ;
    _state->enter();
}


void partition::context::run()
{
    _state->run();
}


bool partition::context::enable_steady_mode()
{
    return _state->enable_steady_mode();
}


bool partition::context::enable_safety_mode()

{
    return _state->enable_safety_mode();
}


bool partition::context::enable_gravity_mode()

{
    return _state->enable_gravity_mode();
}


bool partition::context::enable_operative_mode()

{
    return _state->enable_operative_mode();
}


/*******************************************/


state::state(ctx_wptr ctx, uint dofs)
    : _context(ctx)
    , _params(dofs)
{
    /**/
}


void state::enter()
{
    /* default: pass */
}


void state::run()
{
    /* default: pass */
}


void state::exit()
{
    /* default: pass */
}


bool state::enable_steady_mode()
{
    if (auto ctx = _context.lock())
    {
        ctx->go_to(ctx->_steady);
        return true;
    }

    return false;
}


bool state::enable_safety_mode()
{
    if (auto ctx = _context.lock())
    {
        ctx->go_to(ctx->_safety);
        return true;
    }

    return false;
}


bool state::enable_gravity_mode()
{
    if (auto ctx = _context.lock())
    {
        ctx->go_to(ctx->_gravity);
        return true;
    }

    return false;
}


bool state::enable_operative_mode()
{
    if (auto ctx = _context.lock())
    {
        ctx->go_to(ctx->_operative);
        return true;
    }

    return false;
}


/*******************************************/


states::steady::steady(ctx_wptr ctx, uint dofs, vector k, vector d, double fc = 0.99)
    : state(ctx, dofs)
{
    _params._k  = k ;
    _params._d  = d ;
    _params._fc = fc;
}


void states::steady::enter()
{
    if (auto ctx = _context.lock())
    {
        /* take the current position of the joints... */

        ctx->_model->getJointPosition(_params._q);
    }
}


void states::steady::run()
{
    if (auto ctx = _context.lock())
    {
        /* compute the torque to compensate the gravity */

        ctx->_model->computeGravityCompensation(_params._t);

        /* update the robot! */

        _params.apply(ctx->_robot);
    }
}


bool states::steady::enable_steady_mode()
{
    return false;
}


bool states::steady::enable_safety_mode()
{
    return false;
}


/*******************************************/


states::gravity::gravity(ctx_wptr ctx, uint dofs, double fc = 0.80)
    : state(ctx, dofs)
{
    _params._fc = fc;
}


void states::gravity::run()
{
    if (auto ctx = _context.lock())
    {
        /* compute the torque to compensate the gravity */

        ctx->_model->computeGravityCompensation(_params._t);

        /* update the robot! */

        _params.apply(ctx->_robot);
    }
}


bool states::gravity::enable_safety_mode()
{
    return false;
}


bool states::gravity::enable_gravity_mode()
{
    return false;
}


/*******************************************/


states::operative::operative(ctx_wptr ctx, uint dofs, double fc = 0.99)
    : state(ctx, dofs)
{
    _params._fc = fc;
}


void states::operative::enter()
{
    if (auto ctx = _context.lock())
    {
        /* todo! */

        /* move the reference on the current pose */

        // ctx->_sot->reset();

        /* set effort control mode */

        // ctx->_robot->setControlMode(XBot::ControlMode::Effort());
    }
}


void states::operative::run()
{
    if (auto ctx = _context.lock())
    {
        /* extract the effort reference from the model and synchronize with the robot */

        ctx->_model->getJointEffort(_params._t);

        /* update the robot! */

        _params.apply(ctx->_robot);
    }
}


void states::operative::exit()
{
    if (auto ctx = _context.lock())
    {
        // ctx->sot->leave();
    }
}


bool states::operative::enable_operative_mode()
{
    return false;
}


/*******************************************/


states::safety::safety(ctx_wptr ctx, uint dofs, double fc = 0.80)
    : state(ctx, dofs)
{
    _params._fc = fc;
}


void states::safety::run()
{
    if (auto ctx = _context.lock())
    {
        /* compute the torque to compensate the gravity */

        ctx->_model->computeGravityCompensation(_params._t);

        /* update the robot! */

        _params.apply(ctx->_robot);
    }
}


bool states::safety::enable_safety_mode()
{
    return false;
}


bool states::safety::enable_operative_mode()
{
    return false;
}
