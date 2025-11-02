cmake_minimum_required(VERSION 3.22.1)
project(drone)

add_subdirectory(ros2_ws/src/drone_description)
add_subdirectory(ros2_ws/src/drone_gazebo)
add_subdirectory(ros2_ws/src/drone_gazebo_plugins)
