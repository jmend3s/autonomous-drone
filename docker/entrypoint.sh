#!/bin/bash

# ========================================================================
# Autonomous-Drone Jazzy Development Container Entrypoint
# ========================================================================


set -e

WORKDIR="ros2_ws"
ROBOT_NAME="drone"
USER="jmendes"
USER_EMAIL="jmendes.3595@gmail.com"
USER_HOME="/home/$USER"
BASHRC_PATH="$USER_HOME/.bashrc"
WS_PATH="$USER_HOME/$WORKDIR"

{
  echo "alias build=\"cd $WS_PATH && colcon build && source $BASHRC_PATH\""
  echo "alias create-pkg=\"ros2 pkg create --license BSD-3-Clause --build-type ament_cmake --maintainer-email $USER_EMAIL --maintainer-name $USER\""
  echo "alias $ROBOT_NAME=\"$WS_PATH/src/${ROBOT_NAME}_bringup/scripts/${ROBOT_NAME}_bringup.sh\""

  echo "alias display=\"ros2 launch ${ROBOT_NAME}_description ${ROBOT_NAME}.display.launch.py\""
  echo "alias simulation=\"ros2 launch ${ROBOT_NAME}_gazebo ${ROBOT_NAME}.gazebo.launch.py\""

  echo "export GZ_SIM_RESOURCE_PATH=$WS_PATH/src/${ROBOT_NAME}_gazebo/models:$WS_PATH/src/${ROBOT_NAME}_description/meshes:$WS_PATH/src"
  echo "export GZ_SIM_SYSTEM_PLUGIN_PATH=$WS_PATH/install/${ROBOT_NAME}_gazebo_sim/lib/"
} >> "$BASHRC_PATH"

exec "$@"