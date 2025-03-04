#include <XBotInterface/RobotInterface.h>
#include <RobotInterfaceROS/ConfigFromParam.h>

// **Change**: Use rclcpp, not ros/ros.h
#include <rclcpp/rclcpp.hpp>

/**
 * This executable replicates the python example "ros_api_tutorial.ipynb"
 * in the C++ language, but for ROS 2.
 */
int main(int argc, char **argv)
{
    // **Change**: Initialize rclcpp
    rclcpp::init(argc, argv);

    // **Change**: Create a ROS 2 node
    auto node = rclcpp::Node::make_shared("xbot2_ros_tutorial");

    // **Change**: Get config object from ROS 2 param server
    // (Adapt to your actual signature if needed)
    auto cfg = XBot::ConfigOptionsFromParamServer(node);
    cfg.set_parameter("is_model_floating_base", false);

    // Create robot (xbot2 should be up and running)
    auto robot = XBot::RobotInterface::getRobot(cfg);

    // This model is automatically kept in sync with robot
    auto& model = robot->model();

    // Set a default control mode (applied to all joints)
    auto default_ctrl_mode = XBot::ControlMode::Position() + XBot::ControlMode::Effort();
    robot->setControlMode(default_ctrl_mode);

    // Trajectory parameters
    double q_range = 0.1;
    double period = 2.0;
    double omega = 2 * M_PI / period;

    // Get starting position
    Eigen::VectorXd q0;
    robot->sense();
    robot->getJointPosition(q0);

    // Looping utils
    double time = 0.0;
    double dt = 0.01;

    // **Change**: ros::Rate -> rclcpp::Rate
    rclcpp::Rate rate(1.0 / dt);

    Eigen::VectorXd q, v, a, tau;

    std::cout << "Trajectory started! \n";

    // **Change**: while(ros::ok()) -> while(rclcpp::ok())
    while (time < 5 * period && rclcpp::ok())
    {
        // compute trajectory point
        q = q0 * 0.5 * (std::cos(omega * time) + 1);
        v = -q0 * 0.5 * omega * std::sin(omega * time);
        a = -q0 * 0.5 * omega * omega * std::cos(omega * time);

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

    std::cout << "Trajectory ended!\n";

    // **Change**: shutdown rclcpp at end
    rclcpp::shutdown();
    return 0;
}
