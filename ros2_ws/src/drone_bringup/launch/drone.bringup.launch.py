#!/usr/bin/env python3

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

import os


def generate_launch_description():

    pkg_rviz_name = 'drone_description'
    pkg_gazebo_name = 'drone_gazebo'

    pkg_rviz_share = get_package_share_directory(pkg_rviz_name)
    pkg_gazebo_share = get_package_share_directory(pkg_gazebo_name)

    use_gazebo = LaunchConfiguration('use_gazebo')
    use_rviz = LaunchConfiguration('use_rviz')
    use_sim_time = LaunchConfiguration('use_sim_time')
    world = LaunchConfiguration('world')
    rviz_cfg = LaunchConfiguration('rviz_cfg')

    declare_gazebo_cmd = DeclareLaunchArgument(
        name='use_gazebo',
        default_value='true',
        description='Flag to enable Gazebo simulation'
    )

    declare_rviz_cmd = DeclareLaunchArgument(
        name='use_rviz',
        default_value='true',
        description='Flag to enable RViz2 visualization'
    )

    declare_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Flag to enable use_sim_time for simulation'
    )

    declare_world_cmd = DeclareLaunchArgument(
        name='world',
        default_value=os.path.join(pkg_gazebo_share, 'worlds', 'empty.world'),
        description='Path to simulated world'
    )

    declare_rviz_cfg_cmd = DeclareLaunchArgument(
        name='rviz_cfg',
        default_value=os.path.join(pkg_rviz_share, 'rviz', 'bringup.display.rviz'),
        description='Path to RViz2 configurations'
    )

    gazebo_launch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_share, 'launch', 'drone.gazebo.launch.py')
        ),
        launch_arguments={
            'world': world,
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(use_gazebo)
    )

    rviz_launch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_rviz_share, 'launch', 'drone.display.launch.py')
        ),
        launch_arguments={
            'rviz_config': rviz_cfg,
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(use_rviz)
    )

    ld = LaunchDescription()

    ld.add_action(declare_gazebo_cmd)
    ld.add_action(declare_rviz_cmd)
    ld.add_action(declare_sim_time_cmd)
    ld.add_action(declare_world_cmd)
    ld.add_action(declare_rviz_cfg_cmd)

    ld.add_action(gazebo_launch_cmd)
    ld.add_action(rviz_launch_cmd)

    return ld
