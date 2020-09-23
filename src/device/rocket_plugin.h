#ifndef ROCKET_PLUGIN_H
#define ROCKET_PLUGIN_H

// main XBot2 include
#include <xbot2/xbot2.h>

// include rocket abstract api
#include "rocket_device.h"

using namespace XBot;

/**
 * @brief The RocketCommander class is a ControlPlugin
 * which will send thrust pulses to our rocket device,
 * in order to demonstrate the usage of a custom device
 */
class RocketCommander : public ControlPlugin
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

    // callback for 'Stopping' state
    // stop_completed() must be called to switch
    // to the 'Initialized' state
    void stopping() override;


private:

    using clock_t = chrono::steady_clock;
    clock_t::time_point _start_time;

    double _pulse_period;
    double _duty_cycle;
    double _thrust;

    Hal::RocketBase * _rocket;

};


#endif // ROCKET_PLUGIN_H
