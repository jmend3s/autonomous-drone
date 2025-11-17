from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    sensors_node = Node(package='drone_sensors',
        executable='drone_sensors_node',
        output='screen'
    )

    launch_description = LaunchDescription()

    launch_description.add_action(sensors_node)

    return launch_description
