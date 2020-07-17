#include "clock.h"
#include "fmt/chrono.h"

using namespace std::chrono_literals;

bool ClockExample::on_initialize()
{
    return true;
}

void ClockExample::starting()
{
    // wall clock is the global ntp-adjusted time
    _wall_time = chrono::wall_clock::now();

    // high_resolution_clock is the system most precise
    // steady clock, and it is useful for profiling
    _hr_time = chrono::high_resolution_clock::now();

    // steady clock is used for measuring time intervals
    // (e.g. periodic tasks, timeouts, etc)
    // uses simulation time if available, otherwise
    // it is the same as high_resolution_clock
    _st_time = chrono::steady_clock::now();

    // system clock is used for timestamps that must be
    // synchronized across multiple machines
    // uses simulation time if available, otherwise
    // it is the same as wall_clock
    _sys_time = chrono::system_clock::now();

    start_completed();
}

void ClockExample::run()
{
    using namespace std::chrono;

    auto st_elapsed = chrono::steady_clock::now() - _st_time;
    auto sys_elapsed = chrono::system_clock::now() - _sys_time;
    auto wall_elapsed = chrono::wall_clock::now() - _wall_time;
    auto hr_elapsed = chrono::high_resolution_clock::now() - _hr_time;

    jhigh().jprint(fmt::fg(fmt::terminal_color::cyan),
                   "steady_clock         : {} elapsed ({} absolute) \n",
                   duration<double>(st_elapsed),
                   duration<double>(chrono::steady_clock::now().time_since_epoch()));

    jhigh().jprint(fmt::fg(fmt::terminal_color::blue),
                   "system_clock         : {} elapsed ({} absolute) \n",
                   duration<double>(sys_elapsed),
                   duration<double>(chrono::system_clock::now().time_since_epoch()));

    jhigh().jprint(fmt::fg(fmt::terminal_color::magenta),
                   "wall_clock           : {} elapsed ({} absolute) \n",
                   duration<double>(wall_elapsed),
                   duration<double>(chrono::wall_clock::now().time_since_epoch()));

    jhigh().jprint(fmt::fg(fmt::terminal_color::red),
                   "high_resolution_clock: {} elapsed ({} absolute) \n",
                   duration<double>(hr_elapsed),
                   duration<double>(chrono::high_resolution_clock::now().time_since_epoch()));

    jhigh().jprint("--- \n");


}

XBOT2_REGISTER_PLUGIN(ClockExample, clock_example)
