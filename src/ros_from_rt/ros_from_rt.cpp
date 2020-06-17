#include "ros_from_rt.h"

bool RosFromRt::on_initialize()
{
    // create a nodehandle with namespace equal to
    // the plugin name
    ros::NodeHandle nh(getName());

    // use it to create our 'RosSupport' class
    // note: this must run *after* ros::init, which
    // at this point is guaranteed to be true
    _ros = std::make_unique<RosSupport>(nh);

    /* Publisher */

    // define a message instance which is used to pre-allocate
    // buffers (avoiding malloc during runtime)
    sensor_msgs::JointState js_prealloc;
    js_prealloc.name = _robot->getEnabledJointNames();
    js_prealloc.position.resize(_robot->getJointNum());

    // create the publisher
    // this is a Xbot2 internal publisher, which under the
    // hood will be forwareded to a real ROS topic

    // queue size from parameter
    int queue_size = getParamOr<int>("~queue_size", 1);

    _js_pub = _ros->advertise<sensor_msgs::JointState>(
        "my_js", queue_size, js_prealloc);


    /* Subscriber */
    _flag_sub = _ros->subscribe("my_flag",
                                &RosFromRt::on_flag_recv,
                                this,
                                1,  // queue size
                                &_queue);

    /* Service server */
    _trig_srv = _ros->advertiseService(
        "my_srv",
        &RosFromRt::trig_srv_handler,
        this,
        &_queue);

    // preallocate _q
    _q.resize(_robot->getJointNum());

    return true;
}

void RosFromRt::starting()
{
    start_completed();
}

void RosFromRt::run()
{
    // process callbacks
    _queue.run();

    // read motor position
    _robot->sense(false);  // no model update
    _robot->getJointPosition(_q);

    // loan a pre-allocate message
    auto js_msg = _js_pub->loanMessage();

    // if it could be done..
    if(js_msg)
    {
        // put motor position
        js_msg->msg().position.assign(_q.data(),
                                      _q.data() + _q.size());

        // publish
        _js_pub->publishLoaned(std::move(js_msg));
    }
    else
    {
        jwarn("could not publish message \n");
    }
}

void RosFromRt::on_flag_recv(const std_msgs::Bool& msg)
{
    jhigh().jprint(fmt::fg(fmt::terminal_color::magenta),
                   "received flag {} \n",
                   msg.data
                   );
}

bool RosFromRt::trig_srv_handler(const std_srvs::TriggerRequest&,
                                 std_srvs::TriggerResponse& res)
{
    jhigh().jprint(fmt::fg(fmt::terminal_color::cyan),
                   "handling service.. \n");

    res.message = "trigger executed";
    res.success = true;

    return true;
}

XBOT2_REGISTER_PLUGIN(RosFromRt, ros_from_rt)
