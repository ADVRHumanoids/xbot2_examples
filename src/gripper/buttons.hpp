#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <string>
#include <std_msgs/Empty.h>

#include <xbot2/xbot2.h>
#include <xbot2/ros/ros_support.h>
#include <xbot2/journal/journal.h>
#include <xbot2/hal/dev_button.h>

#include "button_event.hpp"


using std::string;

namespace XBot {

namespace Albero {

class GripperButton : public Button,
                      protected Journal
{
    public:

        typedef std::shared_ptr<GripperButton> Ptr;

        GripperButton();

        GripperButton(RosSupport::UniquePtr& ros,
                      uint64_t min_t,
                      uint64_t max_t,
                      string name,
                      string clickTopic="/click",
                      string doubleClickTopic="/double_click",
                      string longPressTopic="/long_press");

        ~GripperButton();

        void singleClick()     override;
        void doubleClick()     override;
        void singleClickLong() override;
        void doubleClickLong() override;

    private:

        string _name;
        XBot::PublisherPtr<std_msgs::Empty> _pub_click, _pub_doubleClick, _pub_longPress;

};

class GripperButtonsBoard : protected Journal
{
    public:

        typedef std::shared_ptr<GripperButtonsBoard> Ptr;

        GripperButtonsBoard(RosSupport::UniquePtr& ros,
                            uint64_t min_t,
                            uint64_t max_t,
                            Hal::ButtonsBoardBase::Ptr buttons_board);

        ~GripperButtonsBoard();

        void update(uint64_t t);
        void update(double t);

    private:

        std::map <std::string, Albero::GripperButton::Ptr> _buttons;

        uint64_t _min_t, _max_t;
        Hal::ButtonsBoardBase::Ptr _buttons_board;

};
}  // Albero namespace
}  // XBot namespace

#endif  // __BUTTON_HPP__
