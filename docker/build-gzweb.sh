#!/bin/bash

set -e

DIR=/home/user

source /usr/share/gazebo/setup.sh
cd $DIR/gzweb
npm run deploy

