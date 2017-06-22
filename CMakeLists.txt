cmake_minimum_required(VERSION 2.8.3)
project(my_pcl_tutorial)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_pcl_tutorial
#  CATKIN_DEPENDS pcl_conversions pcl_ros roscpp sensor_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/my_pcl_tutorial_node.cpp)
add_executable(example src/example.cpp)
add_executable(example_voxelgrid src/example_voxelgrid_pcl_types.cpp)
add_executable(example_planar src/example_planarsegmentation.cpp)
add_executable(cylinder_segmentation src/cylinder_segmentation.cpp)
add_executable(don_segmentation src/don_segmentation.cpp)
add_executable(cluster_extraction src/cluster_extraction.cpp)
add_executable(region_growing_segmentation src/region_growing_segmentation.cpp)
target_link_libraries(example ${catkin_LIBRARIES})
target_link_libraries(example_voxelgrid ${catkin_LIBRARIES})
target_link_libraries(example_planar ${catkin_LIBRARIES})
target_link_libraries(cylinder_segmentation ${catkin_LIBRARIES})
target_link_libraries(don_segmentation ${catkin_LIBRARIES})
target_link_libraries(cluster_extraction ${catkin_LIBRARIES})
target_link_libraries(region_growing_segmentation ${catkin_LIBRARIES})


