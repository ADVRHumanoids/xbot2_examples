#ifndef PARTITION_H
#define PARTITION_H

#include <xbot2/journal/journal.h>
#include <xbot2/robot_interface/robot_interface_xbot_rt.h>

/**/

namespace partition {

/*************************************************/


class state  ;
class context;

/*************************************************/

typedef Eigen::VectorXd                  vector   ;
typedef std::shared_ptr<state>           state_ptr;
typedef std::weak_ptr<context>           ctx_wptr ;
typedef XBot::ModelInterface::Ptr        model_ptr;
typedef XBot::RobotInterfaceXBot2Rt::Ptr robot_ptr;

/**************************************************/

class control_params
{

public:

    /**/

    double _fc;
    vector _k, _d, _q, _dq, _t;

    /**/

    control_params() = delete;
    control_params(uint dofs);

    /**/

    void apply(robot_ptr robot);

};

/**************************************************/

class interface
{

public:

    virtual void run                  () = 0;
    virtual bool enable_steady_mode   () = 0;
    virtual bool enable_safety_mode   () = 0;
    virtual bool enable_gravity_mode  () = 0;
    virtual bool enable_operative_mode() = 0;

};

/**************************************************/

class context : public interface
{

private:

    state_ptr _state;

public:

    context() = delete         ;
    context(robot_ptr robot    ,
            model_ptr model    ,
            /* create the states once */
            state_ptr operative,
            state_ptr safety   ,
            state_ptr gravity  ,
            state_ptr steady  );

    /**/

    void run                  () override;
    bool enable_steady_mode   () override;
    bool enable_safety_mode   () override;
    bool enable_gravity_mode  () override;
    bool enable_operative_mode() override;

    /**/

    void go_to(state_ptr state);

    /**/

    robot_ptr _robot;
    model_ptr _model;
    state_ptr _operative, _safety, _gravity, _steady;

};

/**************************************************/

class state : public interface
{

protected:

    ctx_wptr       _context;
    control_params _params ;

public:

    state() = delete             ;
    state(ctx_wptr ctx, uint dofs);

    /**/

    virtual void run                  () override;
    virtual bool enable_steady_mode   () override;
    virtual bool enable_safety_mode   () override;
    virtual bool enable_gravity_mode  () override;
    virtual bool enable_operative_mode() override;

    /**/

    virtual void enter();
    virtual void exit ();

};

namespace states {

class steady : public state
{

public:

    using state::state;

    steady(ctx_wptr ctx, uint dofs, vector k, vector d, double fc);

    /**/

    void run               () override;
    bool enable_steady_mode() override;
    bool enable_safety_mode() override;

    /**/

    void enter() override;

};


class gravity : public state
{

public:

    using state::state;

    gravity(ctx_wptr ctx, uint dofs, double fc);

    /**/

    void run                () override;
    bool enable_safety_mode () override;
    bool enable_gravity_mode() override;

};


class operative : public state
{

public:

    using state::state;

    operative(ctx_wptr ctx, uint dofs, double fc);

    /**/

    void run                  () override;
    bool enable_operative_mode() override;

    /**/

    void enter() override;
    void exit () override;

};


class safety : public state
{

public:

    using state::state;

    safety(ctx_wptr ctx, uint dofs, double fc);

    /**/

    void run                  () override;
    bool enable_safety_mode   () override;
    bool enable_operative_mode() override;

};

/**************************************************/

} // namespace states
} // namespace partition


#endif // PARTITION_H
