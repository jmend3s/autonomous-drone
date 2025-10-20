FROM osrf/ros:jazzy-desktop-full

# Install necessary programs
RUN apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y \
      build-essential \
      gdb \
      ssh \
  && rm -rf /var/lib/apt/lists/*

# Install necessary ROS 2 control packages
RUN apt-get update \
  && apt-get install -y \
    ros-jazzy-gz-ros2-control \
    ros-jazzy-gz-ros2-control-demos \
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    ros-jazzy-ros-gz \
    ros-jazzy-moveit \
    ros-jazzy-joint-state-publisher \
    ros-jazzy-joint-state-publisher-gui \
    ros-jazzy-urdf-tutorial \
    ros-jazzy-rmw-cyclonedds-cpp \
  && rm -rf /var/lib/apt/lists/*

# Create a non-root user, ensuring no UID/GID conflicts
ARG USERNAME=jmendes
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG WORKDIR=drone_ws

RUN if getent passwd $USER_UID >/dev/null; then \
      userdel -r -f $(getent passwd $USER_UID | cut -d: -f1); \
    fi && \
    if getent group $USER_GID >/dev/null; then \
      groupdel $(getent group $USER_GID | cut -d: -f1); \
    fi && \
    groupadd --gid $USER_GID $USERNAME && \
    useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME && \
    mkdir -p /home/$USERNAME/.config && chown $USER_UID:$USER_GID /home/$USERNAME/.config

# Set up sudo
RUN apt-get update \
  && apt-get install -y sudo \
  && echo "$USERNAME ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
  && chmod 0440 /etc/sudoers.d/$USERNAME \
  && rm -rf /var/lib/apt/lists/*

# Copy the entrypoint script
COPY entrypoint.sh /entrypoint.sh

# Set up the working directory
WORKDIR /home/$USERNAME/$WORKDIR/

# Automatically source ROS and workspace in bashrc
RUN echo "source /opt/ros/jazzy/setup.bash" >> /home/$USERNAME/.bashrc \
  && echo "source /home/$USERNAME/$WORKDIR/install/setup.bash" >> /home/$USERNAME/.bashrc \
  && chown $USERNAME:$USERNAME /home/$USERNAME/.bashrc

# Set up entrypoint and default command
ENTRYPOINT ["/bin/bash", "/entrypoint.sh"]
CMD ["bash"]