// Include the ROS 2 specific XBot2 interface header
#include <xbot2_interface/robotinterface2.h>

// Include the ROS 2 specific config_from_param
#include <xbot2_interface/ros2/config_from_param.hpp>

// Include base ROS 2 headers
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
/**
 * This executable replicates the python example "ros_api_tutorial.ipynb"
 * in the C++ language, updated for ROS 2 Jazzy.
 */
int main(int argc, char **argv) {
    // Initialize rclcpp
    rclcpp::init(argc, argv);
    
    // Create a ROS 2 node with namespace "xbotcore" for parameter access
    auto node = rclcpp::Node::make_shared("xbot2_ros_tutorial", "xbotcore");
    
    // Use the ROS 2 specific config options function
    // Note: ConfigOptionsFromParams is the ROS 2 equivalent to ConfigOptionsFromParamServer
    auto cfg = XBot::ConfigOptionsFromParams(node);
    
    // Set floating base parameter
    cfg.set_parameter("is_model_floating_base", false);
    
    // Create robot (xbot2 should be up and running)
    auto robot = XBot::RobotInterface::getRobot(cfg);
    
    // Create a separate model instance for computations
    auto model_copy = XBot::ModelInterface::getModel(cfg);


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
    
    // Use the simpler Rate format for ROS 2
    rclcpp::Rate rate(1.0 / dt);  // 100 Hz
    
    Eigen::VectorXd q, v, a, tau;
    
    std::cout << "Trajectory started! \n";
    
    
    while (time < 5 * period && rclcpp::ok()) {
        // Compute trajectory point
        q = q0 * 0.5 * (std::cos(omega * time) + 1);
        v = -q0 * 0.5 * omega * std::sin(omega * time);
        a = -q0 * 0.5 * omega * omega * std::cos(omega * time);
        
        // Compute inverse dynamics torque
        model_copy->setJointPosition(q);
        model_copy->setJointVelocity(v);
        model_copy->setJointAcceleration(a);
        model_copy->update();
        model_copy->computeInverseDynamics(tau);
        
        // Set reference to robot
        robot->setPositionReference(q);
        robot->setVelocityReference(v);
        robot->setEffortReference(tau);
        
        // move() does the publishing to /xbotcore/command
        robot->move();

        
        // Sync the loop to the target frequency
        time += dt;
        rate.sleep();
    }
    
    std::cout << "Trajectory ended!\n";
    
    // Shutdown rclcpp at end
    rclcpp::shutdown();
    return 0;
}