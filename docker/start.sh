#!/bin/bash

source ~/.bashrc

set_xbot2_config src/xbot2_examples/config/teleop_simple_example.yaml

roscore &

gazebo src/xbot2_examples/world/teleop_xbot2.world &

cd gzweb
npm start > /dev/null && fg
cd


