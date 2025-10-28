# Autonomous Drone #

![Docker](https://img.shields.io/badge/Docker-28.5.1-blue)
![OS](https://img.shields.io/ubuntu/v/ubuntu-wallpapers/noble?color=6A0DAD)
![ROS_2 Jazzy](https://img.shields.io/ros/v/jazzy/rclcpp)
![Gazebo Iron 8.9.0](https://img.shields.io/badge/Gazebo_Iron-8.9.0-lightgrey)
![PlatformIO Core 6.1.16](https://img.shields.io/badge/PlatformIO_Core-6.1.16-E37B0D?logo=platformio&logoColor=white)

### Goals <br>

 - Deeper dive into robotics related mathematics and physics
 - Sensors & sensor fusion
 - Simulations
 - Hardware emulation
 - Real hardware
 - Relation simulation - reality 
 - Aerial robotics
 - Path planning
 - SLAM navigation 
 - Computer vision

### Architecture

    *Comming soon*

### Tools <br>

 - **Hardware**
   - Quadcopter (F450)
   - Raspberry pi 5
   - Teensy 4.1
   - IMU (BNO086) 
   - BLDC's
 
   <br>
 
 - **Software**
   - Docker
     - ROS2 Jazzy
     - ROS controllers
     - Gazebo Iron
     - Gazebo plugins
   - PlatformIO

### What is done

 - Docker environment setup
 - ROS2 environment
 - URDF description
 - Display and Gazebo launch files
 - PlatformIO environment for firmware
 - Electronics testing platform built

### Next steps

 - *Gazebo simulation*
   - Low level microcontroller emulation plugin for Gazebo
   - ROS2 controllers for motors and sensors
 - *Hardware*
   - Electronics testing (motors, IMU, microcontroller)
   - Controller design and building
   - PCB's

### Building locally 

Clone the repository locally ```git clone git@github.com:jmend3s/autonomous-drone.git``` <br>
If using another IDE ignore the directory ```clion_scripts``` <br>
Build the docker image ```sudo docker -t drone-jazzy-dev autonomous-drone/docker/``` <br>
If using Terminator terminal the container can be used by running ```./autonomous-drone/docker/startcontainer.sh``` **refer to the documentation inside the script** <br>
Build and source workspace ```colcon build && . install/setup.bash``` or using the alias ```build``` (This alias also cd's to the workspace) <br>
Launch Rviz2 ```ros2 launch drone_description drone.display.launch.py``` <br>
Launch Gazebo ```ros2 launch drone_gazebo drone.gazebo.launch.py```
