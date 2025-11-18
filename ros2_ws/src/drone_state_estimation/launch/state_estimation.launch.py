
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

import os


def generate_launch_description():

    pkg_path = get_package_share_directory('drone_state_estimation')
    ekf_path = os.path.join(pkg_path, 'config', 'ekf.yaml')

    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Flag to enable use_sim_time for simulation'
    )

    efk_local_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_local',
        output='screen',
        parameters=[ekf_path, {'use_sim_time': use_sim_time}],
        remappings=[ ('/odometry/filtered', '/odometry/filtered') ]
    )

    navsat_transform_node = Node(
        package='robot_localization',
        executable='navsat_transform_node',
        name='navsat_transform',
        output='screen',
        parameters=[ekf_path, {'use_sim_time': use_sim_time}],
        remappings=[
            ('/imu', '/imu/data'),
            ('/gps/fix', '/gps/fix'),
            ('/odometry/filtered', '/odometry/filtered'),
            ('odometry/gps', 'odometry/gps_navsat')
        ]
    )

    efk_global_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_global',
        output='screen',
        parameters=[ekf_path, {'use_sim_time': use_sim_time}],
        remappings=[ ('/odometry/filtered', '/odometry/filtered/global') ]
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_sim_time_cmd)
    launch_description.add_action(efk_local_node)
    launch_description.add_action(navsat_transform_node)
    launch_description.add_action(efk_global_node)

    return launch_description
