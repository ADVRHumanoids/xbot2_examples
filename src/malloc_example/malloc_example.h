// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The MallocExample class is a ControlPlugin
 * which allocates some memory at runtime to illustrate
 * the XBot2 memory tracing tools
 */
class MallocExample : public ControlPlugin
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

    Eigen::MatrixXd _A, _B, _C;

};

