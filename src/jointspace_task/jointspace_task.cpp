#include "jointspace_task.h"

#include <XBotBlock/Utils.h>
#include <boost/container/set.hpp>


using namespace UtilsComm;


bool JointSpaceTask::on_initialize()
{
    CommonUtils::setXBotCoreNodePresentVar(true);
    
    CommonUtils::setRobot("DefaultRobot",_robot);

    _robot->setControlMode(ControlMode::Position());

    // we must explicitly set the control mode for our robot
    // in this case, we will only send positions
    //set_control_mode();

    return true;
}

void JointSpaceTask::set_control_mode()
{
    std::map<std::string, ControlMode> ctrl_map;
    
    for(auto j : _robot->getEnabledJointNames())
    {
        ControlMode ctrl;
        if(!getParam("/hal/joint/control_mode/" + j, ctrl))
        {
            jwarn("could not find control mode for joint '{}', setting to idle \n", j);
        }
        
        ctrl_map[j] = ctrl;
    }
    
    _robot->setControlMode(ctrl_map);
}

void JointSpaceTask::starting()
{
    _plugin_started=false;
    
    _model_Obj.reset();
    _model_Obj = std::make_shared<modelModelClass>();
    
    _model_Obj->initialize();
    
    _plugin_started=true;

    start_completed();
}

void JointSpaceTask::run()
{
    _model_Obj->step();
}

void JointSpaceTask::on_close()
{
    if(_plugin_started)
    {
    _model_Obj->terminate();
    }
}


XBOT2_REGISTER_PLUGIN(JointSpaceTask, jointspace_task)
