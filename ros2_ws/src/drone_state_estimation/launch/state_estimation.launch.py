
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

import os


def generate_launch_description():

    pkg_name = 'drone_state_estimation'
    pkg_share_directory = get_package_share_directory(pkg_name)
    ekf_local_path = os.path.join(pkg_share_directory, 'config', 'ekf_local.yaml')
    ekf_global_path = os.path.join(pkg_share_directory, 'config', 'ekf_global.yaml')
    navsat_transform_path = os.path.join(pkg_share_directory, 'config', 'navsat_transform.yaml')

    use_ekf_local = LaunchConfiguration('use_ekf_local')
    use_navsat_transform = LaunchConfiguration('use_navsat_transform')
    use_ekf_global = LaunchConfiguration('use_ekf_global')
    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_use_ekf_local = DeclareLaunchArgument(
        name='use_ekf_local',
        default_value='true'
    )

    declare_use_navsat_transform = DeclareLaunchArgument(
        name='use_navsat_transform',
        default_value='true'
    )

    declare_use_ekf_global = DeclareLaunchArgument(
        name='use_ekf_global',
        default_value='true'
    )

    declare_use_sim_time = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
    )

    efk_local_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_local',
        output='screen',
        parameters=[
            ekf_local_path,
            {'use_sim_time': use_sim_time}
        ],
        remappings=[ ('/odometry/filtered', '/odometry/filtered') ],
        condition=IfCondition(use_ekf_local)
    )

    navsat_transform_node = Node(
        package='robot_localization',
        executable='navsat_transform_node',
        name='navsat_transform',
        output='screen',
        parameters=[
            navsat_transform_path,
            {'use_sim_time': use_sim_time}
        ],
        remappings=[
            ('/imu', '/imu/data'),
            ('/gps/fix', '/gps/fix'),
            ('/odometry/filtered', '/odometry/filtered'),
            ('/odometry/gps', '/odometry/gps_navsat')
        ],
        condition = IfCondition(use_navsat_transform)
    )

    efk_global_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_global',
        output='screen',
        parameters=[
            ekf_global_path,
            {'use_sim_time': use_sim_time}
        ],
        remappings=[('/odometry/filtered', '/odometry/filtered/global')],
        condition = IfCondition(use_ekf_global)
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_use_ekf_local)
    launch_description.add_action(declare_use_navsat_transform)
    launch_description.add_action(declare_use_ekf_global)
    launch_description.add_action(declare_use_sim_time)

    launch_description.add_action(efk_local_node)
    launch_description.add_action(navsat_transform_node)
    launch_description.add_action(efk_global_node)

    return launch_description
