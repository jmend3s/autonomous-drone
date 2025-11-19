
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

import os


def generate_launch_description():

    pkg_rviz_name = 'drone_description'
    pkg_gazebo_name = 'drone_gazebo'
    pkg_sensors_name = 'drone_sensors'
    pkg_state_estimation_name = 'drone_state_estimation'

    pkg_rviz_share = get_package_share_directory(pkg_rviz_name)
    pkg_gazebo_share = get_package_share_directory(pkg_gazebo_name)
    pkg_sensors_share = get_package_share_directory(pkg_sensors_name)
    pkg_state_estimation_share = get_package_share_directory(pkg_state_estimation_name)

    pkg_rviz_launch = PythonLaunchDescriptionSource(os.path.join(pkg_rviz_share, 'launch', 'drone.display.launch.py'))
    pkg_gazebo_launch = PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_share, 'launch', 'drone.gazebo.launch.py'))
    pkg_sensors_launch = PythonLaunchDescriptionSource(os.path.join(pkg_sensors_share, 'launch', 'sensors.launch.py'))
    pkg_state_estimation_launch = PythonLaunchDescriptionSource(os.path.join(pkg_state_estimation_share, 'launch', 'state_estimation.launch.py'))

    use_rviz = LaunchConfiguration('use_rviz')
    rviz_cfg = LaunchConfiguration('rviz_cfg')

    use_gazebo = LaunchConfiguration('use_gazebo')
    use_bridge = LaunchConfiguration('use_bridge')
    world = LaunchConfiguration('world')

    use_sensors_node = LaunchConfiguration('use_sensors_node')

    use_state_estimation = LaunchConfiguration('use_state_estimation')
    use_ekf_local = LaunchConfiguration('use_ekf_local')
    use_navsat_transform = LaunchConfiguration('use_navsat_transform')
    use_ekf_global = LaunchConfiguration('use_ekf_global')

    use_sim_time = LaunchConfiguration('use_sim_time')

    declare_use_rviz = DeclareLaunchArgument(
        name='use_rviz',
        default_value='true',
        description='Flag to enable RViz2 visualization'
    )

    declare_use_rviz_cfg = DeclareLaunchArgument(
        name='rviz_cfg',
        default_value = os.path.join(pkg_rviz_share, 'rviz', 'bringup.display.rviz'),
        description='Path to RViz2 configurations'
    )

    declare_use_gazebo = DeclareLaunchArgument(
        name='use_gazebo',
        default_value='true',
        description='Flag to enable Gazebo simulation'
    )

    declare_use_bridge = DeclareLaunchArgument(
        name='use_bridge',
        default_value='true',
        description='Flag to enable clock bridge for simulation'
    )

    declare_use_world = DeclareLaunchArgument(
        name='world',
        default_value=os.path.join(pkg_gazebo_share, 'worlds', 'empty.world'),
        description='Path to simulated world'
    )

    declare_use_sensors_node = DeclareLaunchArgument(
        name='use_sensors_node',
        default_value='true',
        description='Flag to enable drone_sensors simulation'
    )

    declare_use_state_estimation = DeclareLaunchArgument(
        name='use_state_estimation',
        default_value='true',
        description = 'Flag to enable state_estimation node'
    )

    declare_use_ekf_local = DeclareLaunchArgument(
        name='use_ekf_local',
        default_value='true',
        description = 'Flag to enable local EKF'
    )

    declare_use_navsat_transform = DeclareLaunchArgument(
        name='use_navsat_transform',
        default_value='true',
        description = 'Flag to enable local NavSat transform'
    )

    declare_use_ekf_global = DeclareLaunchArgument(
        name='use_ekf_global',
        default_value='true',
        description = 'Flag to enable global EKF'
    )

    declare_use_sim_time = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Flag to enable use_sim_time for simulation'
    )

    rviz_launch = IncludeLaunchDescription(pkg_rviz_launch,
        launch_arguments={
            'rviz_config': rviz_cfg,
            'use_sim_time': use_sim_time
        }.items(),
        condition = IfCondition(use_rviz)
    )

    gazebo_launch = IncludeLaunchDescription(pkg_gazebo_launch,
        launch_arguments={
            'world': world,
            'use_bridge': use_bridge,
            'use_sim_time': use_sim_time
        }.items(),
        condition = IfCondition(use_gazebo)
    )

    sensors_launch = IncludeLaunchDescription(pkg_sensors_launch,
        launch_arguments={
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(use_sensors_node)
    )

    state_estimation_launch = IncludeLaunchDescription(pkg_state_estimation_launch,
        launch_arguments={
            'use_ekf_local': use_ekf_local,
            'use_navsat_transform': use_navsat_transform,
            'use_ekf_global': use_ekf_global,
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(use_state_estimation)
    )

    launch_description = LaunchDescription()

    launch_description.add_action(declare_use_rviz)
    launch_description.add_action(declare_use_rviz_cfg)

    launch_description.add_action(declare_use_gazebo)
    launch_description.add_action(declare_use_bridge)
    launch_description.add_action(declare_use_world)

    launch_description.add_action(declare_use_sensors_node)

    launch_description.add_action(declare_use_state_estimation)
    launch_description.add_action(declare_use_ekf_local)
    launch_description.add_action(declare_use_navsat_transform)
    launch_description.add_action(declare_use_ekf_global)

    launch_description.add_action(declare_use_sim_time)

    launch_description.add_action(rviz_launch)
    launch_description.add_action(gazebo_launch)
    launch_description.add_action(sensors_launch)
    launch_description.add_action(state_estimation_launch)

    return launch_description
