#include "listener.h"

bool Listener::on_initialize()
{
    /* Subscribe to int topic */
    _small_sub = subscribe("input_small",
                           &Listener::on_small_msg_recv, this,
                           getParamOr<int>("~queue_size", 1),
                           &_queue);
    // queue size taken from parameter
    // _queue pointer is used to run multiple subscribers at once


    /* Subscribe to Eigen::MatrixXd topic */
    // advertise topic with optional argument
    _big_sub = subscribe("input_big",
                         &Listener::on_big_msg_recv, this,
                         getParamOr<int>("~queue_size", 1),
                         &_queue);


    // success if we could advertise both topics
    return _small_sub && _big_sub;
}

void Listener::starting()
{
    start_completed();
}

void Listener::run()
{
    // process callbacks
    _queue.run();
}

void Listener::on_small_msg_recv(const int& msg)
{
    // print in blue with high prio
    jhigh().jprint(fmt::fg(fmt::terminal_color::blue),
                   "{}: received int = {} \n",
                   getName(), msg);
}

void Listener::on_big_msg_recv(const Eigen::MatrixXd& msg)
{
    // print in blue with high prio
    jhigh().jprint(fmt::fg(fmt::terminal_color::blue),
                   "{}: received matrix = {} @{} \n",
                   getName(), msg(999,999), (void*)&msg);
}

XBOT2_REGISTER_PLUGIN(Listener, listener)
