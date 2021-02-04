#ifndef CARTESIANIMPEDANCE_TASK_H
#define CARTESIANIMPEDANCE_TASK_H

// main XBot2 include
#include <xbot2/xbot2.h>

#include "CartesianImpedance_Task_ert_rtw/CartesianImpedance_Task.h"
#include "CartesianImpedance_Task_ert_rtw/CartesianImpedance_Task_private.h"
#include "CartesianImpedance_Task_ert_rtw/CartesianImpedance_Task_types.h"
#include "CartesianImpedance_Task_ert_rtw/rtGetInf.h"
#include "CartesianImpedance_Task_ert_rtw/rtGetNaN.h"
#include "CartesianImpedance_Task_ert_rtw/rt_nonfinite.h"
#include "CartesianImpedance_Task_ert_rtw/rtwtypes.h"

using namespace XBot;

/**
 * @brief The HomingExample class is a ControlPlugin
 * implementing a simple homing motion.
 */
class CartesianImpedanceTask : public ControlPlugin
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
    bool _plugin_started=false;
    std::shared_ptr<modelModelClass>  _model_Obj;
    ModelInterface::Ptr _rt_model;

};

#endif // CARTESIANIMPEDANCE_TASK_H

