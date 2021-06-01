#ifndef ALBERO_CONTROLLERS_H
#define ALBERO_CONTROLLERS_H

#include <xbot2/xbot2.h>
#include <xbot2/system/clock.h>
#include <xbot2/journal/journal.h>
#include <cartesian_interface/ros/RosServerClass.h>
#include <cartesian_interface/CartesianInterfaceImpl.h>
#include <cartesian_interface/sdk/rt/LockfreeBufferImpl.h>

/**/

namespace XBot { namespace albero {

/*****************************************/

typedef Eigen::VectorXd             vector;
typedef Eigen::MatrixXd             matrix;
typedef XBot::ModelInterface        model ;
typedef XBot::RobotInterfaceXBot2Rt robot ;

/*****************************************/

namespace controllers {

class interface
{

public:

    virtual void enable  (double t) = 0;
    virtual void disable (double t) = 0;
    virtual void shutdown(double t) = 0;

    virtual void update(double t, double dt) = 0;

};


class cartesio : public interface
{

public:

    XBOT2_DECLARE_SMART_PTR(cartesio)

private:

    /*****************************************************/

    typedef Cartesian::Context                 context    ;
    typedef Cartesian::LockfreeBufferImpl      lock_free  ;
    typedef Cartesian::CartesianInterfaceImpl  cart_ifc   ;
    typedef Cartesian::ProblemDescription      description;
    typedef Cartesian::RosServerClass::Options options    ;
    typedef Cartesian::RosServerClass          ros_server ;
    typedef Cartesian::Parameters              params     ;
    typedef ros::NodeHandle                    nhandle    ;
    typedef XBot::RunnableTask                 xtask      ;
    typedef XBot::thread                       xthread    ;

    /*****************************************************/

    bool _on;

    /**/

    cart_ifc  ::Ptr _rt_ci ;
    lock_free ::Ptr _nrt_ci;
    ros_server::Ptr _server;

    /**/

    std::unique_ptr <xthread> _nrt_thread;

    /* methods */

    bool is_on     ();
    void nrt_worker();

public:

    /* internal class */

    class configurator
    {

    public:

        XBOT2_DECLARE_SMART_PTR(configurator)

    private:

        double      _period;
        std::string _problem, _solver, _tf_prefix, _ros_namespace, _name;
        model::Ptr  _model ;

    public:

        configurator(const xtask & task, model::Ptr model);

        /**/

        model::Ptr   get_model              () const;
        model::Ptr   copy_model             () const;

        context::Ptr get_context            () const;
        context::Ptr copy_context           () const;

        std::string  get_name               () const;
        std::string  get_solver             () const;

        double       get_period             () const;

        options      get_server_options     () const;
        description  get_problem_description() const;

    };

public:

    /* public methods */

    cartesio() {} // todo

    cartesio(const configurator & cfg);

    /* ifc methods */

    void enable  (double t) override;
    void disable (double t) override;
    void shutdown(double t) override;

    void update(double t, double dt) override;

};


} // namespace controllers
} // namespace albero
} // namespace XBot

#endif // ALBERO_CARTESIO_UTILS_H
