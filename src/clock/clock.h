// main XBot2 include
#include <xbot2/xbot2.h>

using namespace XBot;

/**
 * @brief The ClockExample class is a ControlPlugin
 * which showcases the difference between all available
 * clocks
 */
class ClockExample : public ControlPlugin
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

    chrono::steady_clock::time_point _st_time;
    chrono::wall_clock::time_point _wall_time;
    chrono::system_clock::time_point _sys_time;
    chrono::high_resolution_clock::time_point _hr_time;

};

