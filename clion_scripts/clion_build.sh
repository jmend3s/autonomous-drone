#!/bin/bash

# ========================================================================
# Source ROS Development Environment For Clion Script
# ========================================================================


source /opt/ros/jazzy/setup.bash
source /home/jmendes/ros2_ws/install/setup.bash

exec cmake "$@"