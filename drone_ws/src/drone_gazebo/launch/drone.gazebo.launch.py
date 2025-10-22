import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import AppendEnvironmentVariable
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    pkg_name_description = 'drone_description'

    pkg_share_description = FindPackageShare(package=pkg_name_description).find(pkg_name_description)
    pkg_ros_gz_sim = FindPackageShare(package='ros_gz_sim').find('ros_gz_sim')

    xacro_file_path = os.path.join(pkg_share_description, 'urdf', 'drone.urdf.xacro')

    drone_resource_parent = os.path.dirname(pkg_share_description)

    set_env_vars_resources = AppendEnvironmentVariable(
        'GZ_SIM_RESOURCE_PATH',
        drone_resource_parent
    )

    robot_description_content = Command(['xacro ', xacro_file_path])

    robot_description_params = {'robot_description': robot_description_content, 'use_sim_time': True}

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
        # '-r' means start paused; 'empty.sdf' is the standard world
        launch_arguments=[('gz_args', ' -r empty.sdf')]
    )

    start_gazebo_ros_spawner_cmd = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=[
            '-topic', 'robot_description',  # Read URDF from /robot_description topic
            '-name', 'my_drone',
            '-allow_renaming', 'true',
            # Spawn slightly above the ground plane
            '-z', '0.1'
        ]
    )

    return LaunchDescription([
        set_env_vars_resources,
        start_gazebo_cmd,
        robot_state_publisher_node,
        start_gazebo_ros_spawner_cmd
    ])
