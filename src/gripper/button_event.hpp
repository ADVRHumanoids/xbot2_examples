#ifndef __BUTTON_EVENT_H__
#define __BUTTON_EVENT_H__

#include <algorithm>
#include <boost/circular_buffer.hpp>
#include <memory>

namespace XBot {

namespace Albero {

/**
   * Extend boost::circular_buffer for bool.
   */

class CircularBuffer {

   private:

    boost::circular_buffer<bool> _buffer;

   public:

    typedef std::shared_ptr<CircularBuffer> Ptr;

    CircularBuffer(uint capacity) : _buffer(capacity) {}

    void pushBack(bool value) {
        _buffer.push_back(value);
    }

    bool isTrue() {
        return std::all_of(_buffer.begin(), _buffer.end(), [](bool value) { return value; });
    }

    bool isFalse() {
        return std::none_of(_buffer.begin(), _buffer.end(), [](bool value) { return value; });
    }
};

/**
 * fw declaration
*/

class Button;

/**
   * Create the state objects.
   */

class State {
   public:

    typedef std::shared_ptr<State> Ptr;

    virtual ~State();
    virtual void update(Button *context, bool pressed, uint64_t t) = 0;
    virtual void onTimer(Button *context) = 0;
};

/**
 * The Button defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Button.
 */
class Button {
    /**
   * @var State A reference to the current state of the Button.
   */
   private:

    uint _clicks;
    uint64_t _time, _transition_time, _timeout;
    State::Ptr _state, _pressed, _released;

   public:



    Button();
    Button(uint64_t min_t, uint64_t max_t);
    ~Button();

    /**
    * The Button allows changing the State object at runtime.
    */
    void transitionTo(State::Ptr& state);

    /**
    * The Button delegates part of its behavior to the current State object.
    */
    void update(bool pressed, uint64_t t);
    void onTimer(Button *context);

    CircularBuffer::Ptr presses;

    //transitions
    void setPressed();
    void setReleased();

    // outcomes
    virtual void singleClick() = 0;
    virtual void doubleClick() = 0;
    virtual void singleClickLong() = 0;
    virtual void doubleClickLong() = 0;

    // clicks
    void resetClicks();
    const uint getClicks();
    void addClick();

    // time
    const uint64_t getElapsedTime();
    const uint64_t getTimeout();
};

class Pressed : public State {
   public:
    void update(Button *context, bool pressed, uint64_t t) override;
    void onTimer(Button *context) override;
};

class Released : public State {
   public:
    void update(Button *context, bool pressed, uint64_t t) override;
    void onTimer(Button *context) override;
};
}
}

#endif // __BUTTON_EVENT_H__
