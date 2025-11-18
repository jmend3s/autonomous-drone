
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch_ros.actions import Node

import os

def generate_launch_description():

    pkg_path = get_package_share_directory('drone_state_estimation')
    ekf = os.path.join(pkg_path, 'config', 'ekf.yaml')

    return LaunchDescription([
        Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_local',
            parameters=[ekf],
            output='screen'
        )
    ])