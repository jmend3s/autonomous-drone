# Autonomous Drone #

![Docker](https://img.shields.io/badge/Docker-28.5.1-blue)
![OS](https://img.shields.io/ubuntu/v/ubuntu-wallpapers/noble?color=6A0DAD)
![ROS_2 Jazzy](https://img.shields.io/ros/v/jazzy/rclcpp)
![Gazebo Iron 8.9.0](https://img.shields.io/badge/Gazebo_Iron-8.9.0-lightgrey)
![CLion Version](https://img.shields.io/badge/CLion-2025.2.4-007ACC)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

This repository contains the ROS 2 simulation, description, and development environment for the Autonomous Drone project. <br>
An IoT-enabled autonomous drone platform for surveillance, search and rescue missions. Integrating ROS2, Gazebo simulation and onboard flight control

---
### Project Objectives

This project aims to develop a modular and autonomous drone platform with the following goals:
- **Full simulation to hardware workflow** — seamless transition from Gazebo testing to real hardware.
- **Modular ROS 2 → firmware architecture** — separation between high-level nodes and low-level control loops.
- **Real time sensor fusion and control** — integrate IMU, GPS and camera data.
- **Autonomous navigation and vision integration** — waypoint following, obstacle avoidance and SLAM.
- **Extensible design for research** — a flexible base for robotics experiments.

---
 ### System Overview

```
+------------------+             +-------------------+
|  Raspberry Pi 5  |  <------->  |  Teensy 4.1 MCU   |
|  ROS2 Nodes      |             |  Flight Controller|
+------------------+             +-------------------+
        |                               |
        v                               v
   +----------+                   +------------+
   | Gazebo   |                   | ESC / IMU  |
   | Simulator|                   | Interfaces |
   +----------+                   +------------+ 
```

---
### Project Structure

```
clion_scripts/                # Clion realated scripts for ROS 2 integration
docker/                       # Dockerfile and helper scripts
docs/                         # Diagrams and documentation
flight-controller/            # Teensy firmware (submodule)
printables/                   # 3D models
ros2_ws/
├── src/
│ ├── drone_description/      # URDF and meshes
│ ├── drone_gazebo/           # Simulation plugins and worlds
│ └── drone_gazebo_plugins/   # Custom Gazebo plugins
```

---
### Quick Start 

 - Clone the repository ```git clone git@github.com:jmend3s/autonomous-drone.git``` <br>
 - Go to project root ```cd autonomous-drone/```
 - Build the docker image ```./docker/build.sh``` <br>
 - Start container ```./docker/run.sh``` **refer to the documentation on the script to use without Terminator and xdotool** <br>
 - **Inside the container** build and source workspace ```colcon build && . install/setup.bash``` or use the alias ```build``` (which also moves to the workspace root) <br>
 - Launch RViz2 ```ros2 launch drone_description drone.display.launch.py``` <br>
 - Launch Gazebo ```ros2 launch drone_gazebo drone.gazebo.launch.py``` <br>
**Be sure to run all the Docker scripts on the project's root**

---
### Teensy Flight Control

The [Teensy Flight Controller](https://github.com/jmend3s/flight-controller)
submodule handles low-level motor control, sensor reading, and hardware communication.
It interfaces with the ROS 2 companion computer through serial and can also be emulated
inside Gazebo using a custom plugin (in development).

---
### Current Status

- [x] Docker development environment setup
- [x] ROS 2 Jazzy workspace created
- [x] Drone URDF and Gazebo world defined
- [ ] Gazebo plugin for Teensy flight controller emulation
- [ ] ROS 2 controller for BLDC motors
- [ ] Integration of IMU data in simulation

---
### Hardware <br>

- Frame: F450 quadcopter  
- Companion computer: Raspberry Pi 5  
- Flight controller: [Teensy Flight Controller](https://github.com/jmend3s/flight-controller)  
- Motors: A2212 1400 KV BLDC × 4  
- ESCs: 40 A × 4
- Propellers: 8045 × 4
- Battery: LiPo 3S 5200 mAh  
