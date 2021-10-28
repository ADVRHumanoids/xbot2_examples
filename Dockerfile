FROM nvidia/opengl:1.0-glvnd-runtime-ubuntu20.04 as nvidia
FROM ros:noetic-ros-base-focal

COPY --from=nvidia /usr/local /usr/local
COPY --from=nvidia /etc/ld.so.conf.d/nvidia.conf /etc/ld.so.conf.d/nvidia.conf
ENV NVIDIA_VISIBLE_DEVICES=all NVIDIA_DRIVER_CAPABILITIES=all

ENV rosdistro noetic

# install all dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \ 
sudo file libyaml-cpp-dev build-essential cmake cmake-curses-gui git wget vim \
libmatio-dev \
ros-${rosdistro}-robot ros-${rosdistro}-interactive-markers ros-${rosdistro}-tf2-eigen ros-${rosdistro}-rviz \ 
gazebo11 libgazebo11-dev \ 
libjansson-dev nodejs npm libboost-dev imagemagick libtinyxml-dev mercurial \
qt5-default qttools5-dev qtquickcontrols2-5-dev qtdeclarative5-dev 

# create a regular user
RUN useradd -ms /bin/bash user
RUN adduser user sudo
RUN echo 'user:user' | chpasswd

WORKDIR /home/user

# clone gzweb and copy meshes so that they're visible to it
RUN git clone https://github.com/osrf/gzweb.git
COPY models/database/ gzweb/http/client/assets/

# copy the build script, which will compile gzweb and xbot2_examples
COPY docker/build-gzweb.sh .
RUN ./build-gzweb.sh
RUN rm build-gzweb.sh

# install qt5 charts and graphics drivers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \ 
libqt5charts5-dev libgl1-mesa-glx libgl1-mesa-dri python3-pip

# install xbot
RUN sh -c 'echo "deb http://xbot.cloud/xbot2/ubuntu/$(lsb_release -sc) /" > /etc/apt/sources.list.d/xbot-latest.list'
RUN wget -q -O - http://xbot.cloud/xbot2/ubuntu/KEY.gpg | apt-key add -
RUN apt-get update && apt install -y xbot2_desktop_full

# install python modules for backtrace pretty printer
RUN pip3 install parse ansicolors notebook

# set ownership to user for the whole home folder
RUN chown -R user .

# change user, copy start script (launches gazebo and gzweb)
USER user
COPY --chown=user:user docker/start.sh .
COPY --chown=user:user docker/build-examples.sh .
RUN bash -c "echo source /opt/ros/noetic/setup.bash >> /home/user/.bashrc"
RUN bash -c "echo source /opt/xbot/setup.sh >> /home/user/.bashrc"
RUN bash -c "echo export GAZEBO_MODEL_PATH=/home/user/gzweb/http/client/assets >> /home/user/.bashrc"
RUN bash -c "echo export LD_LIBRARY_PATH=$\LD_LIBRARY_PATH:/home/user/install/lib >> /home/user/.bashrc"
RUN bash -c "echo alias notebook_docker=\'jupyter notebook --no-browser --ip=0.0.0.0\' >> /home/user/.bashrc"