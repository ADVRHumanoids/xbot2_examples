// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The Listener class is a ControlPlugin
 * implementing a topic subscriber
 */
class Listener : public ControlPlugin
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

    void on_small_msg_recv(const int& msg);
    void on_big_msg_recv(const Eigen::MatrixXd& msg);

    CallbackQueue _queue;
    SubscriberPtr<Eigen::MatrixXd> _big_sub;
    SubscriberPtr<int> _small_sub;

};

