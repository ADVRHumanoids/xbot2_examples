#include "CartesianImpedance_Task.h"

#include <XBotBlock/Utils.h>
#include <boost/container/set.hpp>


using namespace UtilsComm;


bool CartesianImpedanceTask::on_initialize()
{
    CommonUtils::setXBotCoreNodePresentVar(true);

    CommonUtils::setRobot("DefaultRobot",_robot);

    _rt_model = ModelInterface::getModel(_robot->getConfigOptions());

    CommonUtils::setModel("DefaultModel",_rt_model);
    CommonUtils::setModelwithRobotConf();

    _robot->setControlMode(ControlMode::Effort()+ControlMode::Stiffness()+ControlMode::Damping());

    // we must explicitly set the control mode for our robot
    // in this case, we will only send positions
    //set_control_mode();

    return true;
}

void CartesianImpedanceTask::set_control_mode()
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

void CartesianImpedanceTask::starting()
{
    _model_Obj.reset();

    //std::cout << "init plugin" << std::endl;
    _model_Obj = std::make_shared<modelModelClass>();

    _model_Obj->initialize();


    start_completed();
}

void CartesianImpedanceTask::run()
{
    _model_Obj->step();
}

void CartesianImpedanceTask::on_close()
{
    if(_model_Obj)
    {
        _model_Obj->terminate();
    }
    else
    {
        CommonUtils::clearModelMap();
        CommonUtils::clearRobotMap();
    }
    
}


XBOT2_REGISTER_PLUGIN(CartesianImpedanceTask, cartesian_impedance_task)
