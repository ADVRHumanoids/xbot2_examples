#include "ros_from_rt.h"

bool RosFromRt::on_initialize()
{
    // (1) Create a "sub-node" of the main ROS 2 node,
    // using the plugin name as namespace.
    auto node = Ros2Support::get_main_node()->create_sub_node(getName());

    // (2) Construct the Ros2Support using that sub-node.
    _ros = std::make_unique<Ros2Support>(node);

    // (3) Prepare a pre-allocated JointState message
    sensor_msgs::msg::JointState js_prealloc;
    js_prealloc.name = _robot->getEnabledJointNames();
    js_prealloc.position.resize(_robot->getJointNum());

    // (4) Typically your queue_size from parameter
    int queue_size = getParamOr<int>("~queue_size", 1);

    // (5) Create a QoS for ROS 2
    rclcpp::QoS qos(queue_size);

    // (6) Create the publisher (XBot2 => ROS 2 bridging)
    _js_pub = _ros->advertise<sensor_msgs::msg::JointState>("my_js",
                                                            qos,
                                                            js_prealloc);

    // (7) Create the subscriber
    // The subscription callback goes to RT domain via CallbackQueue '_queue'
    _flag_sub = _ros->subscribe<std_msgs::msg::Bool>("my_flag",
                                                     &Ros2FromRt::on_flag_recv,
                                                     this,
                                                     queue_size,
                                                     &_queue);

    // (8) Create the service server
    _trig_srv = _ros->advertiseService<std_srvs::srv::Trigger>("my_srv",
                                                               &Ros2FromRt::trig_srv_handler,
                                                               this,
                                                               &_queue);

    // (9) Resize the internal joint vector
    _q.resize(_robot->getJointNum());

    return true;
}

void RosFromRt::starting()
{
    // must be called to switch from 'Starting' to 'Run'
    start_completed();
}

void RosFromRt::run()
{
    // process any incoming callbacks in RT domain
    _queue.run();

    // read motor positions
    _robot->sense(false); // no model update
    _robot->getJointPosition(_q);

    // loan a pre-allocated message
    auto js_msg = _js_pub->loanMessage();

    if(js_msg)
    {
        // put motor positions
        js_msg->msg().position.assign(_q.data(), _q.data() + _q.size());

        // publish
        _js_pub->publishLoaned(std::move(js_msg));
    }
    else
    {
        jwarn("could not publish JointState message\n");
    }
}

void RosFromRt::on_flag_recv(const std_msgs::msg::Bool & msg)
{
    jhigh().jprint(fmt::fg(fmt::terminal_color::magenta),
                   "received flag: {} \n",
                   msg.data);
}

bool RosFromRt::trig_srv_handler(const std_srvs::srv::Trigger::Request &,
                                  std_srvs::srv::Trigger::Response & res)
{
    jhigh().jprint(fmt::fg(fmt::terminal_color::cyan),
                   "handling Trigger service call..\n");

    res.message = "trigger executed";
    res.success = true;

    return true;
}

// Register this plugin in XBot2
XBOT2_REGISTER_PLUGIN(RosFromRt, ros_from_rt)
