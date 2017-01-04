cmake_minimum_required(VERSION 2.8.0)
project(transform_to_tf)

add_definitions(-std=c++11)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS})


cs_add_library(transform_to_tf
  src/library/transform_to_tf.cpp
)

cs_add_executable(transform_to_tf_node
  src/transform_to_tf_node.cpp
)

target_link_libraries(transform_to_tf_node transform_to_tf ${catkin_LIBRARIES})

cs_install()
cs_export()
