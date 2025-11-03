cmake_minimum_required(VERSION 3.8)
project(drone_gazebo_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
#find_package(gz-math8 REQUIRED)
find_package(gz-msgs10 REQUIRED)
find_package(gz-plugin2 REQUIRED COMPONENTS register)
find_package(gz-transport13 REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(${GZ-SIM_INCLUDE_DIRS})

add_library(TeensyEmulator SHARED
  src/TeensyEmulator.cpp
  src/CommunicationNode.cpp
)

set_property(TARGET TeensyEmulator PROPERTY CXX_STANDARD 17)
target_include_directories(TeensyEmulator PRIVATE
  ${GZ-SIM_INCLUDE_DIRS}
)

find_package(gz-plugin2 REQUIRED COMPONENTS register)

ament_target_dependencies(TeensyEmulator
  rclcpp
  std_msgs
  nav_msgs
  geometry_msgs
  tf2_ros
  gz-sim8
  gz-msgs10
  gz-plugin2
  gz-transport13
)

install(TARGETS TeensyEmulator
  DESTINATION lib
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
