// main XBot2 include
#include <xbot2/xbot2.h>

// needed for ROS support from real-time domain
#include <xbot2/ros/ros_support.h>

// include this since we'll be publishing this
// message to ROS from the real-time domain
#include <sensor_msgs/JointState.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Trigger.h>

using namespace XBot;

/**
 * @brief The HomingExample class is a ControlPlugin
 * implementing a simple homing motion.
 */
class RosFromRt : public ControlPlugin
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

    void on_flag_recv(const std_msgs::Bool& msg);

    bool trig_srv_handler(const std_srvs::TriggerRequest& req,
                          std_srvs::TriggerResponse& res);

    Eigen::VectorXd _q;

    RosSupport::UniquePtr _ros;

    CallbackQueue _queue;
    PublisherPtr<sensor_msgs::JointState> _js_pub;
    SubscriberPtr<std_msgs::Bool> _flag_sub;
    ServiceServerPtr<std_srvs::TriggerRequest,
                     std_srvs::TriggerResponse> _trig_srv;
};
