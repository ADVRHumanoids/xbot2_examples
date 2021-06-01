#include "controllers.h"


namespace XBot { namespace albero { namespace controllers {


cartesio::configurator::configurator(const xtask & task, model::Ptr model)

    : _model (model )
{
    /* get task name */

    _name   = task.getName();
    _period = task.getPeriodSec();

    /* get problem description */

    if (!task.getParam("~problem_description/content", _problem))
    {
        /* std::string problem_source = task.getParamOr <std::string> ("~problem_param", "cartesian/problem_description");

        if (!node.getParam(problem_source, _problem))
        {
            throw;
        } */

        throw;
    }

    /* get solver type (default OpenSot) */

    _solver = task.getParamOr <std::string> ("~solver", "OpenSot");

    /* get ros server parameters */

    _tf_prefix     = task.getParamOr <std::string> ("~tf_prefix", "ci"       );
    _ros_namespace = task.getParamOr <std::string> ("~ros_ns"   , "cartesian");
}


std::string cartesio::configurator::get_name() const
{
    return _name;
}


std::string cartesio::configurator::get_solver() const
{
    return _solver;
}


model::Ptr cartesio::configurator::get_model() const
{
    return _model;
}


double cartesio::configurator::get_period() const
{
    return _period;
}


model::Ptr cartesio::configurator::copy_model() const
{
    auto cfg = _model->getConfigOptions();

    /**/

    return model::getModel(cfg);
}


cartesio::context::Ptr cartesio::configurator::get_context() const
{
    auto model = get_model();
    auto param = std::make_shared <params> (_period);

    /**/

    return std::make_shared <context> (param, model);
}


cartesio::context::Ptr cartesio::configurator::copy_context() const
{
    auto model = copy_model();
    auto param = std::make_shared <params> (_period);

    /**/

    return std::make_shared <context> (param, model);
}


cartesio::options cartesio::configurator::get_server_options() const
{
    options opt;

    opt.tf_prefix = _tf_prefix;
    opt.ros_namespace = _ros_namespace;

    /**/

    return opt;
}


cartesio::description cartesio::configurator::get_problem_description() const
{
    auto ctx = get_context();
    auto yaml = YAML::Load(_problem);

    /**/

    return description(yaml, ctx);
}


/**/


cartesio::cartesio(const cartesio::configurator & cfg)

    : _on(true)
{
    double t = 0.0, dt = cfg.get_period();

    _rt_ci = cart_ifc::MakeInstance(cfg.get_solver(), cfg.get_problem_description(), cfg.get_context());

    _rt_ci->enableOtg(dt);
    _rt_ci->update(t, dt);

    /* create ros api server */

    _nrt_ci = std::make_shared <lock_free > (_rt_ci.get(), cfg.copy_context());
    _server = std::make_shared <ros_server> (_nrt_ci, cfg.get_server_options());

    /* spin nrt thread */

    _nrt_thread = std::make_unique <xthread> (/*&cartesio::nrt_worker, this);*/

    []()
    {
        this_thread::set_name("cartesio_nrt");
        for (int i = 0; i < 10; i++)
        {
            this_thread::sleep_for(1s);

            std::cout << "aaaaaaaaaaaaaa" << std::endl;

        }

    });

    //_nrt_thread->set_name(cfg.get_name().append("_cartesio_nrt"));
}


void cartesio::nrt_worker()
{
    while (is_on())
    {
        this_thread::sleep_for(std::chrono::milliseconds(10));

        _nrt_ci->updateState();
        _server->run();
    }
}


void cartesio::update(double t, double dt)
{
    auto rt_ci  = _rt_ci.get();
    auto rt_mdl = _rt_ci->getModel().get();

    /* Receive commands from nrt */

    _nrt_ci->callAvailable(rt_ci);

    /* solve sot */

    if (!rt_ci->update(t, dt))
    {
        return;
    }

    /* Send state to nrt */

    _nrt_ci->pushState(rt_ci, rt_mdl);
}


void cartesio::enable(double t)
{
    _rt_ci->reset(t);

    // _rt_ci->set_active(); todo
}

void cartesio::disable(double t)
{
    // _rt_ci->set_inactive(); todo
}

void cartesio::shutdown(double t)
{
    disable(t);

    /**/

    _on = false;
}

bool cartesio::is_on()
{
    return _on;
}

} // namespace controllers
} // namespace albero
} // namespace XBot
