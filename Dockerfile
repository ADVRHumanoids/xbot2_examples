FROM ros:noetic-ros-base-focal
ENV rosdistro noetic

# install all dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \ 
sudo file libyaml-cpp-dev build-essential cmake cmake-curses-gui git wget vim \
libmatio-dev \
ros-${rosdistro}-robot ros-${rosdistro}-interactive-markers ros-${rosdistro}-tf2-eigen ros-${rosdistro}-rviz \ 
gazebo9 libgazebo9-dev \ 
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

# download binaries for hhcm software, including xbot2
RUN mkdir deb
COPY docker/deb deb

# install binaries
COPY docker/setup-xbot2.sh .
RUN ./setup-xbot2.sh
RUN rm setup-xbot2.sh
RUN rm -rf deb

# set ownership to user for the whole home folder
RUN chown -R user .

# install qt5 charts and graphics drivers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \ 
libqt5charts5-dev libgl1-mesa-glx libgl1-mesa-dri

# change user, copy start script (launches gazebo and gzweb)
USER user
COPY --chown=user:user docker/start.sh .

COPY --chown=user:user docker/build-examples.sh .


