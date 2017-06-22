#!/usr/bin/env bash

bash -c "source /home/ubuntu/.bashrc &&
source /home/ubuntu/catkin_ws/devel/setup.bash &&
roslaunch realsense_camera r200_nodelet_rgbd.launch && 
rosrun my_pcl_tutorial region_growing_segmentation input:=/camera/depth/points"
