
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():

    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_use_sim_time = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
    )

    sensors_node = Node(
        package='drone_sensors',
        executable='drone_sensors_node',
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_use_sim_time)
    launch_description.add_action(sensors_node)

    return launch_description
