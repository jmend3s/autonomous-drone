#!/usr/bin/env python3

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, AppendEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

import os


def generate_launch_description():

    pkg_name = 'drone_gazebo'
    pkg_share = get_package_share_directory(pkg_name)

    world = LaunchConfiguration('world')
    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_world_cmd = DeclareLaunchArgument(
        name='world',
        default_value=os.path.join(pkg_share, 'worlds', 'empty.world'),
        description='Path to simulated world'
    )

    declare_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Flag to enable use_sim_time for simulation'
    )

    pkg_description_name = 'drone_description'

    pkg_description_share = FindPackageShare(package=pkg_description_name).find(pkg_description_name)
    pkg_ros_gz_sim = FindPackageShare(package='ros_gz_sim').find('ros_gz_sim')

    xacro_file_path = os.path.join(pkg_description_share, 'urdf', 'robot', 'drone.urdf.xacro')

    drone_resource_parent = os.path.dirname(pkg_description_share)

    set_env_vars_resources = AppendEnvironmentVariable(
        'GZ_SIM_RESOURCE_PATH',
        drone_resource_parent
    )

    robot_description_content = Command(['xacro ', xacro_file_path])

    robot_description_params = {'robot_description': robot_description_content, 'use_sim_time': use_sim_time}

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description_params]
    )

    start_gazebo_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')
        ),
        launch_arguments=[('gz_args', [' -r -v 4 ', world])]
    )

    start_gazebo_ros_spawner_node = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'drone',
            '-allow_renaming', 'true',
            '-z', '0.1'
        ]
    )

    ros_gazebo_bridge_node = Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            arguments=[
                '/drone/imu@sensor_msgs/msg/Imu@gz.msgs.IMU',
                '/drone/gps@sensor_msgs/msg/NavSatFix@gz.msgs.NavSat',
            ],
            output='screen',
        )

    ld = LaunchDescription()

    ld.add_action(declare_world_cmd)
    ld.add_action(declare_sim_time_cmd)

    ld.add_action(set_env_vars_resources)
    ld.add_action(start_gazebo_cmd)
    ld.add_action(robot_state_publisher_node)
    ld.add_action(start_gazebo_ros_spawner_node)
    ld.add_action(ros_gazebo_bridge_node)

    return ld
