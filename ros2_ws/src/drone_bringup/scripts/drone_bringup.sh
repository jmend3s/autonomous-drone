#!/bin/bash

# ========================================================================
# Simulation Bringup Script
# ========================================================================

RVIZ_CONFIG="bringup.display.rviz"
RVIZ_CONFIG_PATH="/home/jmendes/ros2_ws/install/drone_description/share/drone_description/rviz/${RVIZ_CONFIG}"

WORLD="empty.world"
WORLD_PATH="/home/jmendes/ros2_ws/install/drone_gazebo/share/drone_gazebo/worlds/${WORLD}"

ros2 launch drone_bringup drone.bringup.launch.py \
    use_rviz:=true \
    rviz_cfg:=${RVIZ_CONFIG_PATH} \
    use_gazebo:=true \
    use_bridge:=true \
    world:=${WORLD_PATH} \
    use_sensors_node:=true \
    use_state_estimation:=true \
    use_ekf_local:=true \
    use_navsat_transform:=true \
    use_ekf_global:=true \
    use_sim_time:=true \
