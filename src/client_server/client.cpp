#include "client.h"
#include "fmt/chrono.h"

using namespace std::chrono_literals;

bool Client::on_initialize()
{
    // declare a service client
    _cli = serviceClient<Eigen::Matrix6d, bool>(
        "set_gain");

    // take period between two service calls from params
    _period_between_calls = 500ms;
    getParam("~period_between_calls", _period_between_calls);

    return bool(_cli);
}

void Client::starting()
{
    start_completed();
}

void Client::run()
{
    // steady clock is used for periodic task scheduling
    // this clock is influenced by the simulated time
    // (e.g. runs slower if simulation is slow)
    auto now = chrono::steady_clock::now();

    // not enough time has passed, return
    if(now < _last_call_time + _period_between_calls)
    {
        return;
    }

    _last_call_time = now;

    // high resolution clock is the system highest precision
    // clock, so we use it for profiling
    using timer_clock = chrono::high_resolution_clock;

    // set the service input
    Eigen::Matrix6d mat;
    mat.setRandom();

    jhigh().jinfo("calling service with matrix: \n{}\n",
                  mat);

    auto tic = timer_clock::now();
    bool result = false;

    // call the service
    // the call is actually executed by the server, and
    // the result is finally copied to us
    if(!_cli->call(mat, result, 500ms))
    {
        // call failed (probably server not running)
        jerror("call failed \n");
        return;
    }
    std::chrono::duration<double> dt = timer_clock::now() - tic;

    jhigh().jinfo("returned after {} with result {}\n",
                  dt, result);
}

XBOT2_REGISTER_PLUGIN(Client, client)
