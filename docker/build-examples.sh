#!/bin/bash

set -e

DIR=/home/user

cd $DIR

source .bashrc

cd build

cmake ../src/xbot2_examples \
-DCMAKE_BUILD_TYPE=RelWithDebInfo \
-DCMAKE_INSTALL_PREFIX=/home/user/install

make -j4 install
