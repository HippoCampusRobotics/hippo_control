cmake_minimum_required(VERSION 3.5)
project(hippo_control)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hippo_msgs REQUIRED)
find_package(hippo_common REQUIRED)

include_directories(
  include
)

add_executable(actuator_command_mixer src/actuator_command_mixer.cpp src/simple_mixer.cpp)

ament_target_dependencies(actuator_command_mixer rclcpp hippo_msgs hippo_common)

install (TARGETS actuator_command_mixer
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
