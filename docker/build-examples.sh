#!/bin/bash

set -e


mkdir build
cd build

cmake ../src/xbot2_examples \
-DCMAKE_BUILD_TYPE=RelWithDebInfo \
-DCMAKE_INSTALL_PREFIX=/home/user/install

make -j4 install
