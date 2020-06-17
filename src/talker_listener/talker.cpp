#include "talker.h"

bool Talker::on_initialize()
{
    /* Advertise int topic */
    _small_pub = advertise<int>("output_small");


    /* Advertise Eigen::MatrixXd topic */
    // first, define a matrix of the right size to
    // pre-allocate buffers without incurring in
    // runtime mallocs
    Eigen::MatrixXd big_matrix_prealloc(1000, 1000);

    // advertise topic with optional argument
    _big_pub = advertise("output_big", big_matrix_prealloc);

    // success if we could advertise both topics
    return _small_pub && _big_pub;
}


void Talker::starting()
{
    _iter = 0;
    start_completed();
}

void Talker::run()
{
    ++_iter;

    // publish the integer
    _small_pub->publish(_iter);

    // to publish the big matrix in a zero-copy fashion,
    //first we loan a pre-allocated message from the pool
    auto big_msg_ptr = _big_pub->loanMessage();

    // this is a copy of the 'big_matrix_prealloc' provided
    // to the 'advertise' call, so it has the right size
    // of 1000x1000

    // pool could be empty, so we must check the
    // return value
    if(big_msg_ptr)
    {
        // print address (we will check that the subscriber
        // receives the same object and not a copy)
        jhigh().jinfo("publishing a big matrix = {} @{} \n",
                      _iter, static_cast<void*>(&(big_msg_ptr->msg()))
                      );

        // just modify an element
        big_msg_ptr->msg()(999, 999) = _iter;

        // publish
        // note: std::move makes it explicit that
        // big_msg_ptr will be invalidated after
        // publish returns
        _big_pub->publishLoaned(std::move(big_msg_ptr));

        // here big_msg_ptr is empty
    }
}

XBOT2_REGISTER_PLUGIN(Talker, talker)
