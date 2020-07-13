#include "server.h"

bool Server::on_initialize()
{
    // advertise the service
    _srv = advertiseService("set_gain",
                            &Server::srv_handler, this);

    _gain.setZero();

    // true if we could advertise the service
    return bool(_srv);
}


void Server::starting()
{
    // nothing to do here, just complete
    start_completed();
}

void Server::run()
{
    // handle incoming requests
    _srv->run();
}

bool Server::srv_handler(const Eigen::Matrix6d& req, bool& res)
{
    _gain = req;
    res = true;

    // success message with high prio
    jhigh().jok("successfully set gain to \n{}\n", req);

    return true;
}

XBOT2_REGISTER_PLUGIN(Server, server)
