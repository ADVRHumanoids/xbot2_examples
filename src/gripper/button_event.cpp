#include "button_event.hpp"

#define DEFAULT_MIN_TIME 100
#define DEFAULT_MAX_TIME 500

namespace XBot{

namespace Albero {

State::~State()
{
    /**/
}

Button::Button()
    : _clicks(0)
    , _time(0)
    , _transition_time(0)
    , _timeout(DEFAULT_MAX_TIME)
{

    presses.reset(new CircularBuffer(DEFAULT_MIN_TIME));

    _pressed.reset(new Pressed);
    _released.reset(new Released);

    transitionTo(_released);
}

Button::Button(uint64_t min_t, uint64_t max_t)
    : _clicks(0)
    , _time(0)
    , _transition_time(0)
    , _timeout(max_t)
{

    presses.reset(new CircularBuffer(min_t));

    _pressed.reset(new Pressed);
    _released.reset(new Released);

    transitionTo(_released);
}

Button::~Button()
{
    /**/
}

void Button::addClick()
{
    _clicks++;
}

const uint Button::getClicks()
{
    return _clicks;
}

void Button::resetClicks()
{
    _clicks = 0;
}

const uint64_t Button::getElapsedTime()
{
    return _time - _transition_time;
}

const uint64_t Button::getTimeout()
{
    return _timeout;
}

void Button::transitionTo(State::Ptr& state)
{
    _state = state;
}

void Button::update(bool pressed, uint64_t t)
{
    _time = t;
    _state->update(this, pressed, _time);

    if (getElapsedTime() > _timeout) {
        onTimer(this);
    }
}

void Button::onTimer(Button *context)
{
    _state->onTimer(this);
}

void Button::setPressed()
{
    _transition_time = _time;
    transitionTo(_pressed);
}

void Button::setReleased()
{
    transitionTo(_released);
}

/**************************/

void Pressed::update(Button *context, bool pressed, uint64_t t)
{
    context->presses->pushBack(pressed);

    if (context->presses->isFalse())
    {
        if (context->getElapsedTime() < context->getTimeout()) {
            context->addClick();
        }
        context->setReleased();
    }
}

void Pressed::onTimer(Button *context)
{
    if (context->getClicks() == 0) {
        context->singleClickLong();
    }

    else if (context->getClicks() == 1) {
        context->doubleClickLong();
    }

    context->resetClicks();
}

void Released::update(Button *context, bool pressed, uint64_t t)
{
    context->presses->pushBack(pressed);

    if (context->presses->isTrue()) {
        context->setPressed();
    }
}

void Released::onTimer(Button *context)
{
    if (context->getClicks() == 1) {
        context->singleClick();
    }

    else if (context->getClicks() == 2) {
        context->doubleClick();
    }

    context->resetClicks();
}
}
}

#undef DEFAULT_MIN_TIME
#undef DEFAULT_MAX_TIME
