cmake_minimum_required(VERSION 3.5)
project(hippo_control)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hippo_msgs REQUIRED)
find_package(hippo_common REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  include
)

set(lib_name attitude_control)
add_library(${lib_name} src/geometric_attitude_control.cpp)
target_include_directories(${lib_name}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(${lib_name} rclcpp Eigen3)
ament_export_targets(${lib_name}Target HAS_LIBRARY_TARGET)
ament_export_dependencies(rclcpp Eigen3)

install(
  DIRECTORY include/
  DESTINATION include
)

install(TARGETS ${lib_name}
  EXPORT ${lib_name}Target
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
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
