#include "server.h"

bool Server::on_initialize()
{
    _srv = advertiseService("set_gain",
                            &Server::srv_handler, this);

    _gain.setZero();

    return bool(_srv);
}


void Server::starting()
{
    start_completed();
}

void Server::run()
{
    _srv->run();
}

bool Server::srv_handler(const Eigen::Matrix6d& req, bool& res)
{
    _gain = req;
    res = true;

    jhigh().jok("successfully set gain to \n{}\n", req);

    return true;
}

XBOT2_REGISTER_PLUGIN(Server, server)
