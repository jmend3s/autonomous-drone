
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='drone_sensors',
             executable='drone_sensors_node',
             output='screen')
    ])