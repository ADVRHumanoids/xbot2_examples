#!/bin/bash

set -e

DIR=/home/user

source /usr/share/gazebo/setup.sh
cd $DIR/gzweb
npm run deploy

cd $DIR/deb 
echo "user" | sudo ./install.sh
cd $DIR
rm -rf deb

source /opt/ros/noetic/setup.sh
source /opt/xbot/setup.sh

cd $DIR
mkdir $DIR/build
mkdir $DIR/install

echo "source /opt/ros/noetic/setup.bash" >> $DIR/.bashrc
echo "source /opt/xbot/setup.sh" >> $DIR/.bashrc
echo "export GAZEBO_MODEL_PATH=$DIR/gzweb/http/client/assets" >> $DIR/.bashrc
echo "export XBOT_CONFIG=$DIR/.xbot2/active_config" >> $DIR/.bashrc
echo "export XBOT_ROOT=$DIR/src/xbot2_examples" >> $DIR/.bashrc
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DIR/install/lib" >> $DIR/.bashrc

cd $DIR
mkdir .xbot2


