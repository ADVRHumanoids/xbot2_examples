// main XBot2 include
#include <xbot2/xbot2.h>

// needed for ROS support from real-time domain
#include <xbot2/ros/ros2_support.h>

#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_srvs/srv/trigger.hpp>

using namespace XBot;

/**
 * @brief The Ros2FromRt class is a ControlPlugin
 * implementing ROS publishers, subscribers, and
 * service servers that can run on a real-time
 * thread
 */
class Ros2FromRt : public ControlPlugin
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

    // ROS topic callback
    void on_flag_recv(const std_msgs::msg::Bool& msg);  // Updated namespace

    
    // Update service callback signature
    bool trig_srv_handler(const std_srvs::srv::Trigger::Request& req,
        std_srvs::srv::Trigger::Response& res);  // Updated namespace


    Eigen::VectorXd _q;

    // Change to Ros2Support
    Ros2Support::UniquePtr _ros;


    // queue object to handle multiple subscribers/servers at once
    CallbackQueue _queue;

    
    // Update publisher/subscriber/service types to ROS 2
    PublisherPtr<sensor_msgs::msg::JointState> _js_pub;
    SubscriberPtr<std_msgs::msg::Bool> _flag_sub;
    ServiceServerPtr<std_srvs::srv::Trigger::Request,
                     std_srvs::srv::Trigger::Response> _trig_srv;

};
