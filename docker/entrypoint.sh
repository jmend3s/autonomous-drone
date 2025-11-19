#!/bin/bash

# ========================================================================
# Autonomous-Drone Jazzy Development Container Entrypoint
# ========================================================================


set -e

WORKDIR="ros2_ws"
ROBOT_NAME="drone"
USER="jmendes"

{
  echo "alias build=\"cd /home/$USER/$WORKDIR && colcon build && source ~/.bashrc\""
  echo "alias create-pkg=\"ros2 pkg create --license BSD-3-Clause --build-type ament_cmake --maintainer-email jmendes.3595@gmail.com --maintainer-name jmendes\""

  echo "alias $ROBOT_NAME=\"ros2 launch drone_bringup drone.bringup.launch.py\""
  echo "alias display=\"ros2 launch drone_description drone.display.launch.py\""
  echo "alias simulation=\"ros2 launch drone_gazebo drone.gazebo.launch.py\""

  echo "export GZ_SIM_RESOURCE_PATH=/home/$USER/$WORKDIR/src/drone_gazebo/models:/home/$USER/$WORKDIR/src/drone_description/meshes:/home/$USER/$WORKDIR/src"
  echo "export GZ_SIM_SYSTEM_PLUGIN_PATH=/home/$USER/$WORKDIR/install/drone_gazebo_sim/lib/"
} >> /home/$USER/.bashrc
exec "$@"