#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$SCRIPT_DIR/models/database

gazebo --verbose $SCRIPT_DIR/world/teleop_xbot2.world
