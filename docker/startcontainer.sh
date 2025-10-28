#!/bin/bash

# This script is made to open a new terminal with two tabs for a container
# It's made to work with the terminator terminal and uses the
# xdotool to manipulate terminal commands
# If one of these tools is not installed just comment the last part of the script and run
# After that you can access the container normally 

# sudo apt install terminator
# sudo apt install xdotool

set -e

CONTAINER_NAME="drone-jazzy-dev"
IMAGE_NAME="drone-jazzy-dev"
WORKSPACE_DIR="drone_ws"
WORKSPACE_PATH="$PWD/$WORKSPACE_DIR"
USER_NAME="jmendes"
USER_ID=$(id -u)
GROUP_ID=$(id -g)

export XDG_RUNTIME_DIR=/tmp/runtime-$USER_NAME
mkdir -p $XDG_RUNTIME_DIR
chmod 700 $XDG_RUNTIME_DIR

if [ "$(docker ps -q -f name=^/${CONTAINER_NAME}$)" ]; then
    echo "Container ${CONTAINER_NAME} is already running."
else
  docker run -itd --rm \
    --name $CONTAINER_NAME \
    --hostname $CONTAINER_NAME \
    --gpus all \
    --user ${USER_ID}:${GROUP_ID} \
    --network=host \
    --ipc=host \
    -e DISPLAY=$DISPLAY \
    -e QT_X11_NO_MITSHM=1 \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -v "$WORKSPACE_PATH":/home/$USER_NAME/$WORKSPACE_DIR \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -v ~/.Xauthority:/home/$USER_NAME/.Xauthority:rw \
    -v /dev/dri:/dev/dri \
    --env="NVIDIA_DRIVER_CAPABILITIES=all" \
    --env="NVIDIA_VISIBLE_DEVICES=all" \
    $IMAGE_NAME
fi

# Wait for the container to initialize
sleep 1

xdotool key ctrl+shift+e
sleep 0.1
xdotool type "docker exec -it $CONTAINER_NAME bash -c 'source /opt/ros/jazzy/setup.bash; [ -f /$WORKSPACE_DIR/install/setup.bash ] && source /$WORKSPACE_DIR/install/setup.bash; exec bash'"
xdotool key Return

xdotool key ctrl+shift+o
sleep 0.1
xdotool type "docker exec -it $CONTAINER_NAME bash -c 'source /opt/ros/jazzy/setup.bash; [ -f /$WORKSPACE_DIR/install/setup.bash ] && source /$WORKSPACE_DIR/install/setup.bash; exec bash'"
xdotool key Return