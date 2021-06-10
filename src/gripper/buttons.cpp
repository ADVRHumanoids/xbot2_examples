#include "buttons.hpp"

#define SEC_TO_MSEC 1000

namespace XBot {

namespace Albero {

GripperButton::GripperButton()
    : Button()
    , Journal("")
{
    /**/
}

GripperButton::GripperButton(RosSupport::UniquePtr& ros,
                             uint64_t min_t,
                             uint64_t max_t,
                             string name,
                             string clickTopic,
                             string doubleClickTopic,
                             string longPressTopic)

    : Button(min_t, max_t)
    , Journal(name)
    , _name(name)
{

    int queue_size = 1;

    std_msgs::Empty click_preallock, doubleClick_preallock, longPress_prealloc;

    _pub_click = ros->advertise <std_msgs::Empty> (name + clickTopic, queue_size, click_preallock);
    _pub_doubleClick = ros->advertise <std_msgs::Empty> (name + doubleClickTopic, queue_size, doubleClick_preallock);
    _pub_longPress  = ros->advertise <std_msgs::Empty> (name + longPressTopic, queue_size, longPress_prealloc);

}

GripperButton::~GripperButton()
{
    /**/
}

void GripperButton::singleClick()
{
    auto msg = _pub_click->loanMessage();

    if(msg)
    {
        _pub_click->publishLoaned(std::move(msg));
    }
    else
    {
        jwarn("could not publish single click message \n");
    }

}

void GripperButton::doubleClick()
{
    auto msg = _pub_doubleClick->loanMessage();

    if(msg)
    {
        _pub_doubleClick->publishLoaned(std::move(msg));
    }
    else
    {
        jwarn("could not publish double click message \n");
    }

}


void GripperButton::singleClickLong()
{
    auto msg = _pub_longPress->loanMessage();

    if (msg)
    {
        _pub_longPress->publishLoaned(std::move(msg));
    }
    else
    {
        jwarn("could not publish long click message \n");
    }

}

void GripperButton::doubleClickLong()
{
    // XBot::Logger::success() << "double long press!" << XBot::Logger::endl();
}

GripperButtonsBoard::GripperButtonsBoard(RosSupport::UniquePtr& ros,
                                         uint64_t min_t,
                                         uint64_t max_t,
                                         Hal::ButtonsBoardBase::Ptr buttons_board)
    : Journal(buttons_board->get_name())
    , _min_t(min_t)
    , _max_t(max_t)
    , _buttons_board(buttons_board)
{
    for (const std::string& button_name : _buttons_board->getButtonsNames())
    {
        _buttons[button_name] = std::make_shared<Albero::GripperButton> (ros, min_t, max_t, buttons_board->get_name() + "/" + button_name);
    }
}

GripperButtonsBoard::~GripperButtonsBoard()
{
    /**/
}

void GripperButtonsBoard::update(uint64_t time)
{
    for (const auto& button : _buttons)
    {
        bool pressed = _buttons_board->isPressed(button.first);
        button.second->update(pressed, time);
    }
}

void GripperButtonsBoard::update(double time)
{
    uint64_t int_time = time * SEC_TO_MSEC;
    update(int_time);
}

}  // namespace Albero
}  // namespace XBot

#undef SEC_TO_MSEC
