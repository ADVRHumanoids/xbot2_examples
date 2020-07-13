// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The Client class is a ControlPlugin
 * implementing a simple homing motion.
 */
class Client : public ControlPlugin
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

    ServiceClientPtr<Eigen::Matrix6d, bool> _cli;
    chrono::steady_clock::time_point _last_call_time;
    std::chrono::nanoseconds _period_between_calls;

};

