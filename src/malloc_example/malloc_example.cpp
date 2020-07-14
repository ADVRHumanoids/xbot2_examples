#include "malloc_example.h"


bool MallocExample::on_initialize()
{
    return true;
}

void MallocExample::starting()
{
    start_completed();
}

void MallocExample::run()
{
    _A.setRandom(10, 40);  // this will trigger malloc() once

    _B.setRandom(40, 10);  // this will trigger malloc() once

    _C = _A * _B;  // this will trigger malloc() at each loop

    //    _C.noalias() = _A * _B;  // this will trigger malloc() once
}

XBOT2_REGISTER_PLUGIN(MallocExample, malloc_example)
