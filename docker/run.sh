#!/bin/bash

set -e

# get path to script and change working directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR/..

docker run -it \
 --env="DISPLAY" \
 --env="QT_X11_NO_MITSHM=1" \
 --device=/dev/dri:/dev/dri \
 --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
 --name xbot2examples \
 --publish 8080:8080 \
 -v $(pwd)/src:/home/user/src/xbot2_examples/src \
 -v $(pwd)/world:/home/user/src/xbot2_examples/world \
 -v $(pwd)/config:/home/user/src/xbot2_examples/config \
 -v $(pwd)/CMakeLists.txt:/home/user/src/xbot2_examples/CMakeLists.txt \
 arturolaurenzi/xbot2:examples bash
#
#-v $(pwd)/world:/home/user/src/xbot2_examples/world \
#-v $(pwd)/config:/home/user/src/xbot2_examples/config \ 
#-v $(pwd)/CMakeLists.txt:/home/user/src/xbot2_examples/CMakeLists.txt \



