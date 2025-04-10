cmake_minimum_required(VERSION 3.8)
project(cpp_service_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_custom_interfaces REQUIRED)


add_executable(service_node src/service_node.cpp)
ament_target_dependencies(service_node rclcpp example_interfaces)

add_executable(client_node src/client_node.cpp)
ament_target_dependencies(client_node rclcpp example_interfaces)

add_executable(add_three_ints_server src/add_three_ints_server.cpp)
ament_target_dependencies(add_three_ints_server rclcpp my_custom_interfaces)

add_executable(add_three_ints_client src/add_three_ints_client.cpp)
ament_target_dependencies(add_three_ints_client rclcpp my_custom_interfaces)


install(TARGETS
  service_node
  client_node
  add_three_ints_server
  add_three_ints_client
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
