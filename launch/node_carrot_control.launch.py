from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


def declare_launch_args(launch_description: LaunchDescription):
    action = DeclareLaunchArgument('vehicle_name')
    launch_description.add_action(action)
    action = DeclareLaunchArgument('use_sim_time')
    launch_description.add_action(action)
    action = DeclareLaunchArgument(
        'carrot_control_config',
        description='Path to the carrot control YAML file')
    launch_description.add_action(action)


def add_carrot_control_node(launch_description: LaunchDescription):
    action = Node(package='hippo_control',
                  executable='carrot_control_node',
                  parameters=[
                      {
                          'use_sim_time': LaunchConfiguration('use_sim_time'),
                          'vehicle_name': LaunchConfiguration('vehicle_name')
                      },
                      LaunchConfiguration('carrot_control_config'),
                  ])
    launch_description.add_action(action)


def generate_launch_description():
    launch_description = LaunchDescription()
    declare_launch_args(launch_description=launch_description)
    add_carrot_control_node(launch_description=launch_description)

    return launch_description
