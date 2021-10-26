#include <XBotInterface/RobotInterface.h>
#include <RobotInterfaceROS/ConfigFromParam.h>

#include <ros/ros.h>

/**
 * This executable replicates the python example "ros_api_tutorial.ipynb"
 * in the C++ language.
 */

int main(int argc, char **argv)
{
    // initialize ros node
    ros::init(argc, argv, "xbot2_ros_tutorial");

    // get config object
    ros::NodeHandle nh("xbotcore");
    auto cfg = XBot::ConfigOptionsFromParamServer(nh);
    cfg.set_parameter("is_model_floating_base", false);

    // create robot (note: xbot2 should be up and running)
    auto robot = XBot::RobotInterface::getRobot(cfg);

    // this model is automatically kept in sync with robot
    auto& model = robot->model();

    // set a default control mode (applied to all joints)
    auto default_ctrl_mode = XBot::ControlMode::Position() + XBot::ControlMode::Effort();
    robot->setControlMode(default_ctrl_mode);

    // trajectory parameters
    double q_range = 0.1;
    double period = 2.0;
    double omega = 2*M_PI/period;

    // get starting position
    Eigen::VectorXd q0;
    robot->sense();
    robot->getJointPosition(q0);

    // ooping utils
    double time = 0.0;
    double dt = 0.01;
    ros::Rate rate(1./dt);
    Eigen::VectorXd q, v, a, tau;

    std::cout << "Trajectory started! \n";

    while(time < 5*period && ros::ok())
    {
        // compute trajectory point
        q = q0*0.5*(std::cos(omega*time) + 1);
        v = -q0*0.5*omega*std::sin(omega*time);
        a = -q0*0.5*omega*omega*std::cos(omega*time);

        // compute inverse dynamics torque
        model.setJointPosition(q);
        model.setJointVelocity(v);
        model.setJointAcceleration(a);
        model.update();
        model.computeInverseDynamics(tau);

        // set reference to robot
        robot->setPositionReference(q);
        robot->setVelocityReference(v);
        robot->setEffortReference(tau);

        // move() does the publishing to /xbotcore/command
        robot->move();

        // sync the loop to the target frequency
        time += dt;
        rate.sleep();
    }

    std::cout << "Trajectory ended! \n";
    
}