// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The Talker class is a ControlPlugin
 * implementing a simple homing motion.
 */
class Talker : public ControlPlugin
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

    Eigen::MatrixXd _big_msg;

    PublisherPtr<Eigen::MatrixXd> _big_pub;
    PublisherPtr<int> _small_pub;

    int _iter;

};

