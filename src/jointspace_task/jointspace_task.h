#ifndef CYCLIC_MOTION_H
#define CYCLIC_MOTION_H

// main XBot2 include
#include <xbot2/xbot2.h>

#include "JointSpace_Task_ert_rtw/JointSpace_Task.h"
#include "JointSpace_Task_ert_rtw/JointSpace_Task_private.h"
#include "JointSpace_Task_ert_rtw/JointSpace_Task_types.h"
#include "JointSpace_Task_ert_rtw/rtGetInf.h"
#include "JointSpace_Task_ert_rtw/rtGetNaN.h"
#include "JointSpace_Task_ert_rtw/rt_nonfinite.h"
#include "JointSpace_Task_ert_rtw/rtwtypes.h"

using namespace XBot;

/**
 * @brief The HomingExample class is a ControlPlugin
 * implementing a simple homing motion.
 */
class JointSpaceTask : public ControlPlugin
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
    void on_close() override;

    // callback for 'Run' state
    void run() override;

private:
    
    void set_control_mode();
    bool _plugin_started;
    std::shared_ptr<modelModelClass>  _model_Obj;

};

#endif // CYCLIC_MOTION_H

