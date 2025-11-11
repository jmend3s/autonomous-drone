# ========================================================================
# ROS 2 JAZZY DEVELOPMENT ENVIRONMENT
# ========================================================================

FROM osrf/ros:jazzy-desktop-full

RUN apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y \
    build-essential \
    gdb \
    ssh \
    wget \
    lsb-release \
    gnupg \
  && rm -rf /var/lib/apt/lists/*

RUN apt-get update \
  && apt-get install -y \
    ros-jazzy-joint-state-publisher \
    ros-jazzy-joint-state-publisher-gui \
    ros-jazzy-moveit \
    ros-jazzy-ros-gz \
    ros-jazzy-ros-gz-sim \
    ros-jazzy-gz-ros2-control \
    ros-jazzy-gz-ros2-control-demos \
    ros-jazzy-robot-localization \
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    ros-jazzy-rmw-cyclonedds-cpp \
    ros-jazzy-urdf-tutorial \
  && rm -rf /var/lib/apt/lists/*

ARG USERNAME=jmendes
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG WORKDIR=ros2_ws

RUN if getent passwd $USER_UID >/dev/null; then \
      userdel -r -f $(getent passwd $USER_UID | cut -d: -f1); \
    fi && \
    if getent group $USER_GID >/dev/null; then \
      groupdel $(getent group $USER_GID | cut -d: -f1); \
    fi && \
    groupadd --gid $USER_GID $USERNAME && \
    useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME && \
    mkdir -p /home/$USERNAME/.config && chown $USER_UID:$USER_GID /home/$USERNAME/.config

RUN apt-get update \
  && apt-get install -y sudo \
  && echo "$USERNAME ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
  && chmod 0440 /etc/sudoers.d/$USERNAME \
  && rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/jazzy/setup.bash" >> /home/$USERNAME/.bashrc \
  && echo "source /home/$USERNAME/$WORKDIR/install/setup.bash" >> /home/$USERNAME/.bashrc \
  && chown $USERNAME:$USERNAME /home/$USERNAME/.bashrc

COPY entrypoint.sh /entrypoint.sh
USER $USERNAME
WORKDIR /home/$USERNAME/$WORKDIR/
ENTRYPOINT ["/bin/bash", "/entrypoint.sh"]
CMD ["bash"]