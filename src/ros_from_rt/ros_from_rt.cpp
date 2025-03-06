#include "ros_from_rt.h"

bool Ros2FromRt::on_initialize() {
    // (1) Create a "sub-node" of the main ROS 2 node,
    // using the plugin name as namespace.
    // This is the ROS2 equivalent of creating a namespaced NodeHandle in ROS1
    // and is essential for proper organization of topics/services under this plugin
    auto node = Ros2Support::get_main_node()->create_sub_node(getName());
    
    // (2) Construct the Ros2Support using that sub-node.
    // This helper class encapsulates ROS2 functionality for our plugin
    // Note: In ROS2, we don't need to check if ros::init has been called
    // as the node lifecycle is managed differently
    _ros = std::make_unique<Ros2Support>(node);
    
    // (3) Prepare a pre-allocated JointState message
    // This pre-allocates memory buffers to avoid malloc during runtime
    // which is crucial for real-time performance
    sensor_msgs::msg::JointState js_prealloc;
    js_prealloc.name = _robot->getJointNames();
    js_prealloc.position.resize(_robot->getJointNum());
    
    // (4) Your queue_size from parameter
    // Gets the queue size from ROS parameter or uses default value of 1
    int queue_size = getParamOr<int>("~queue_size", 1);
    
    // (5) Create a QoS for ROS 2
    // ROS2 uses Quality of Service settings instead of just queue size
    // KeepLast policy retains only the most recent n messages (similar to ROS1 queue size)
    rclcpp::KeepLast kl_policy(queue_size);
    rclcpp::QoS qos(kl_policy);
    
    // (6) Create the publisher (XBot2 => ROS 2 bridging)
    // This is a XBot2 internal publisher that forwards data to an actual ROS2 topic
    // We pass the pre-allocated message to avoid memory allocation in real-time
    _js_pub = _ros->advertise<sensor_msgs::msg::JointState>("my_js",
                                                          qos,
                                                          js_prealloc);
    
    // (7) Create the subscriber
    // The subscription callback goes to RT domain via CallbackQueue '_queue'
    // This ensures that callbacks are processed in the real-time thread
    _flag_sub = _ros->subscribe<std_msgs::msg::Bool>("my_flag",
                                                   &Ros2FromRt::on_flag_recv,
                                                   this,
                                                   queue_size,
                                                   &_queue);
    
    // (8) Create the service server - COMMENTED OUT DUE TO TEMPLATE ISSUE
    // TODO: Fix this when the ROS 2 support library is updated
    /*
    _trig_srv = _ros->advertiseService<std_srvs::srv::Trigger>("my_srv",
                                                             &Ros2FromRt::trig_srv_handler,
                                                             this,
                                                             &_queue);
    */
    
    // (9) Resize the internal joint vector
    // Pre-allocate memory for joint positions to avoid real-time allocations
    _q.resize(_robot->getJointNum());
    
    return true;
}

void Ros2FromRt::starting() {
    // must be called to switch from 'Starting' to 'Run' state
    // this is part of the XBot2 plugin lifecycle management
    start_completed();
}

void Ros2FromRt::run() {
    // process any incoming callbacks in RT domain
    // this executes pending callbacks in our real-time queue
    _queue.run();
    
    // read motor positions
    // get current joint state without updating the internal model
    // which is important for real-time performance
    _robot->sense(false); // no model update
    _robot->getJointPosition(_q);
    
    // loan a pre-allocated message
    // this avoids memory allocation in the real-time thread
    auto js_msg = _js_pub->loanMessage();
    
    if(js_msg)
    {
        // put motor positions
        // efficiently copy joint position data to the message
        js_msg->msg().position.assign(_q.data(), _q.data() + _q.size());
        
        // publish
        // publish the loaned message without additional memory allocation
        _js_pub->publishLoaned(std::move(js_msg));
    }
    else
    {
        // warn if we couldn't get a pre-allocated message
        jwarn("could not publish JointState message\n");
    }
}

void Ros2FromRt::on_flag_recv(const std_msgs::msg::Bool & msg) {
    // print received flag value with magenta color for visibility
    jhigh().jprint(fmt::fg(fmt::terminal_color::magenta),
                   "received flag: {} \n",
                   msg.data);
}

bool Ros2FromRt::trig_srv_handler(const std_srvs::srv::Trigger::Request &,
                                std_srvs::srv::Trigger::Response & res) {
    // print service handling message with cyan color for visibility
    jhigh().jprint(fmt::fg(fmt::terminal_color::cyan),
                   "handling Trigger service call..\n");
    
    // set appropriate response fields
    res.message = "trigger executed";
    res.success = true;
    
    return true;
}

// Register this plugin in XBot2
// This macro registers the plugin class with the plugin loader
XBOT2_REGISTER_PLUGIN(Ros2FromRt, ros_from_rt)