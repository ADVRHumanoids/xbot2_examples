#!/bin/bash

set -e

nvidia-docker run --rm -it \
 --device=/dev/dri:/dev/dri \
 --privileged \
 --env "DOCKER=1" \
 --env="DISPLAY=$DISPLAY" \
 --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
 --volume="$HOME/.ssh:/home/user/.ssh:ro" \
 --env="XAUTHORITY=$XAUTH" \
 --volume="$XAUTH:$XAUTH" \
 --name xbot2examples \
 --publish 8080:8080 \
 --publish 8888:8888 \
 -v $(pwd)/src:/home/user/src/xbot2_examples/src \
 -v $(pwd)/world:/home/user/src/xbot2_examples/world \
 -v $(pwd)/config:/home/user/src/xbot2_examples/config \
 -v $(pwd)/CMakeLists.txt:/home/user/src/xbot2_examples/CMakeLists.txt \
 arturolaurenzi/xbot2:examples bash

