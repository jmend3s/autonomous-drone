#!/bin/bash
set -e

WORKDIR="drone_ws"
ROBOT_NAME="drone"
USER="jmendes"

echo "alias build=\"cd /home/$USER/$WORKDIR && colcon build && source ~/.bashrc\"" >> /home/$USER/.bashrc
echo "alias $ROBOT_NAME=\"bash ~/$WORKDIR/src/drone_bringup/scripts/drone_gazebo.sh\"" >> /home/$USER/.bashrc

echo "export GZ_SIM_RESOURCE_PATH=/home/$USER/$WORKDIR/src/drone_gazebo/models" >> /home/$USER/.bashrc

exec "$@"