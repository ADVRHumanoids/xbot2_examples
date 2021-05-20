#ifndef ALBERO_CARTESIO_RT_H
#define ALBERO_CARTESIO_RT_H

#include "cartesio_rt.h"

namespace XBot {

class AlberoCartesioRt : public CartesioRt
{

public:
    
    using CartesioRt::CartesioRt;

    bool on_initialize() override;
    void starting() override;
    void run() override;
    
    // void stopping() override;
    // void on_abort() override;
    // void on_close() override;

private:

    /* data members */

    Eigen::VectorXd _k, _d;

    /* methods */
    
    void updateModel();
};


}

#endif // CARTESIO_RT_H
