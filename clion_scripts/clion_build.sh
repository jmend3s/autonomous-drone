#!/bin/bash

source /opt/ros/jazzy/setup.bash
source /home/jmendes/drone_ws/install/setup.bash

exec cmake "$@"