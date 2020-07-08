FROM ros:noetic-ros-base-focal
ENV rosdistro noetic

# install all dependencies
RUN apt-get update && apt-get install -y \ 
sudo file libyaml-cpp-dev build-essential cmake cmake-curses-gui git wget vim \
libmatio-dev ros-${rosdistro}-robot ros-${rosdistro}-interactive-markers ros-${rosdistro}-tf2-eigen \ 
gazebo9 libgazebo9-dev \ 
libjansson-dev nodejs npm libboost-dev imagemagick libtinyxml-dev mercurial

# create a regular user
RUN useradd -ms /bin/bash user
RUN adduser user sudo
RUN echo 'user:user' | chpasswd

WORKDIR /home/user

# clone gzweb and copy meshes so that they're visible to it
RUN git clone https://github.com/osrf/gzweb.git
COPY models/database/ gzweb/http/client/assets/

# download binaries for hhcm software, including xbot2
RUN mkdir deb
COPY docker/deb deb

# copy the build script, which will compile gzweb and xbot2_examples
COPY docker/build.sh .
RUN ./build.sh
RUN rm build.sh

# set ownership to user for the whole home folder
RUN chown -R user .

# change user, copy start script (launches gazebo and gzweb)
USER user
COPY --chown=user:user docker/start.sh .


