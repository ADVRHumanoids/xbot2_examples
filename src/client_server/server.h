// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The Server class is a ControlPlugin
 * implementing a simple homing motion.
 */
class Server : public ControlPlugin
{

public:

    // we don't do anything special inside the
    // constructor, so just inherit the base class
    // implementation
    using ControlPlugin::ControlPlugin;

    // initialization method; the plugin won't be run
    // if this returns 'false'
    bool on_initialize() override;

    // callback for the 'Starting' state
    // start_completed() must be called to switch
    // to 'Run' state
    void starting() override;

    // callback for 'Run' state
    void run() override;

private:

    // callback to handle incoming requests
    bool srv_handler(const Eigen::Matrix6d& req,
                     bool& res);

    // variable for service server with input (request) of type
    // Eigen::Matrix6d and output (response) of type bool
    ServiceServerPtr<Eigen::Matrix6d, bool> _srv;

    Eigen::Matrix6d _gain;

};

