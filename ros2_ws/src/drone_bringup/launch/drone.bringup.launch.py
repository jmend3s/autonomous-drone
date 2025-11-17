#!/usr/bin/env python3

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import SetParameter, Node

import os


def generate_launch_description():

    pkg_rviz_name = 'drone_description'
    pkg_gazebo_name = 'drone_gazebo'
    pkg_sensors_name = 'drone_sensors'

    pkg_rviz_share = get_package_share_directory(pkg_rviz_name)
    pkg_gazebo_share = get_package_share_directory(pkg_gazebo_name)
    pkg_sensors_share = get_package_share_directory(pkg_sensors_name)

    use_rviz = LaunchConfiguration('use_rviz')
    rviz_cfg = LaunchConfiguration('rviz_cfg')
    use_gazebo = LaunchConfiguration('use_gazebo')
    use_sensors_node = LaunchConfiguration('use_sensors_node')
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_clock_bridge = LaunchConfiguration('use_clock_bridge')
    world = LaunchConfiguration('world')

    declare_rviz_cmd = DeclareLaunchArgument(
        name = 'use_rviz',
        default_value = 'true',
        description = 'Flag to enable RViz2 visualization'
    )

    declare_rviz_cfg_cmd = DeclareLaunchArgument(
        name = 'rviz_cfg',
        default_value = os.path.join(pkg_rviz_share, 'rviz', 'bringup.display.rviz'),
        description = 'Path to RViz2 configurations'
    )

    declare_gazebo_cmd = DeclareLaunchArgument(
        name = 'use_gazebo',
        default_value = 'true',
        description = 'Flag to enable Gazebo simulation'
    )

    declare_sensors_node_cmd = DeclareLaunchArgument(
        name = 'use_sensors_node',
        default_value = 'true',
        description = 'Flag to enable drone_sensors simulation'
    )

    declare_sim_time_cmd = DeclareLaunchArgument(
        name = 'use_sim_time',
        default_value = 'true',
        description = 'Flag to enable use_sim_time for simulation'
    )

    declare_clock_bridge_cmd = DeclareLaunchArgument(
        name = 'use_clock_bridge',
        default_value = 'true',
        description = 'Flag to enable clock bridge for simulation'
    )

    declare_world_cmd = DeclareLaunchArgument(
        name = 'world',
        default_value=os.path.join(pkg_gazebo_share, 'worlds', 'empty.world'),
        description = 'Path to simulated world'
    )

    set_sim_time_param = SetParameter('use_sim_time', use_sim_time)

    rviz_launch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_rviz_share, 'launch', 'drone.display.launch.py')
        ),
        launch_arguments= {
            'rviz_config': rviz_cfg,
            'use_sim_time': use_sim_time
        }.items(),
        condition = IfCondition(use_rviz)
    )

    gazebo_launch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_share, 'launch', 'drone.gazebo.launch.py')
        ),
        launch_arguments= {
            'world': world,
            'use_sim_time': use_sim_time
        }.items(),
        condition = IfCondition(use_gazebo)
    )

    sensors_launch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_sensors_share, 'launch', 'sensors.launch.py')
        ),
        launch_arguments= {
            'world': world,
            'use_sim_time': use_sim_time
        }.items(),
        condition = IfCondition(use_sensors_node)
    )

    clock_bridge_node = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[ '/clock@rosgraph_msgs/msg/Clock@gz.msgs.Clock' ],
        output='screen',
    )

    clock_bridge_delayed_cmd = TimerAction(
        period=3.0,
        actions=[clock_bridge_node]
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_rviz_cmd)
    launch_description.add_action(declare_rviz_cfg_cmd)
    launch_description.add_action(declare_gazebo_cmd)
    launch_description.add_action(declare_sensors_node_cmd)
    launch_description.add_action(declare_sim_time_cmd)
    launch_description.add_action(declare_clock_bridge_cmd)
    launch_description.add_action(declare_world_cmd)

    launch_description.add_action(set_sim_time_param)

    launch_description.add_action(rviz_launch_cmd)
    launch_description.add_action(gazebo_launch_cmd)
    launch_description.add_action(sensors_launch_cmd)
    launch_description.add_action(clock_bridge_delayed_cmd)

    return launch_description
