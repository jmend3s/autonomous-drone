
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue

import os


def generate_launch_description():

    pkg_name = 'drone_description'
    pkg_share = get_package_share_directory(pkg_name)

    rviz_cfg = LaunchConfiguration('rviz_cfg')
    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Flag to enable use_sim_time for simulation'
    )

    declare_rviz_cfg = DeclareLaunchArgument(
        name='rviz_cfg',
        default_value=os.path.join(pkg_share, 'rviz', 'rviz2.display.rviz'),
        description='Path to RViz2 configurations'
    )

    model_arg = DeclareLaunchArgument(
        name="model",
        default_value=os.path.join(get_package_share_directory("drone_description"), "urdf", "robot", "drone.urdf.xacro"),
        description="Absolute path to robot URDF file"
    )

    robot_description = ParameterValue(Command(["xacro ", LaunchConfiguration("model")]), value_type=str)
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[
            {"robot_description": robot_description},
            {'use_sim_time': use_sim_time}
        ]
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen",
        arguments=["-d", rviz_cfg],
        parameters=[{'use_sim_time': use_sim_time}]
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_sim_time_cmd)
    launch_description.add_action(declare_rviz_cfg)

    launch_description.add_action(model_arg)
    launch_description.add_action(robot_state_publisher)
    launch_description.add_action(rviz_node)

    return launch_description
