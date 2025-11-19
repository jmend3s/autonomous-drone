#!/bin/bash

# ========================================================================
# Autonomous-Drone ROS 2 Jazzy Development Docker Image Build Script
# ========================================================================


set -e

IMAGE_NAME="drone-jazzy-dev"
DOCKER_DIR="docker"

docker build -t $IMAGE_NAME \
  --build-arg USER_UID=$(id -u) \
  --build-arg USER_GID=$(id -g) \
  $DOCKER_DIR/
