/*
 * Beck Pang, 20170620
 * Regional growing segmentation
 * http://pointclouds.org/documentation/tutorials/region_growing_segmentation.php
 */
#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <string>

#include <cstddef>
#include <iostream>
#include <cassert>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

using namespace std;
ros::Publisher pub;

void cloud_cb (const pcl::PCLPointCloud2ConstPtr& cloud_input)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_XYZ (new pcl::PointCloud <pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_XYZ_passthrough (new pcl::PointCloud <pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_XYZ_filtered (new pcl::PointCloud <pcl::PointXYZ>);

    pcl::fromPCLPointCloud2 (*cloud_input, *cloud_XYZ);

    std::cerr << "PointCloud before voxel grid filtering: " << cloud_XYZ->width * cloud_XYZ->height
              << " data points (" << pcl::getFieldsList(*cloud_XYZ) << ").\n";

    // Passthrough filter for the distance
//    pcl::IndicesPtr indices (new std::vector<int>);
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud_XYZ);
//    pass.setInputCloud(cloud_XYZ);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.5, 1.0);
    pass.filter(*cloud_XYZ_passthrough);

    // Create the voxel grid filtering object
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud(cloud_XYZ_passthrough);
    sor.setLeafSize(0.005f, 0.005f, 0.005f);
    sor.filter(*cloud_XYZ_filtered);

    std::cerr << "PointCloud after voxel grid filtering: " << cloud_XYZ_filtered->width * cloud_XYZ_filtered->height
              << " data points (" << pcl::getFieldsList(*cloud_XYZ_filtered) << ").\n";

    pcl::RegionGrowing<pcl::PointXYZ, pcl::Normal> reg;

    if (cloud_XYZ_filtered->points.size() != 0)
    {
        // Normal estimation
        pcl::search::Search<pcl::PointXYZ>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZ> > (new pcl::search::KdTree<pcl::PointXYZ>);
        pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
        pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normal_estimator;
        normal_estimator.setSearchMethod(tree);
        normal_estimator.setInputCloud(cloud_XYZ_filtered);
    //    normal_estimator.setInputCloud(cloud_XYZ);
        normal_estimator.setKSearch(50);
        normal_estimator.compute(*normals);


        // Region growing

        reg.setMinClusterSize(100);
        reg.setMaxClusterSize(1000000);
        reg.setSearchMethod(tree);
        reg.setNumberOfNeighbours(30);
        // reg.setIndices(indices);
        reg.setInputCloud(cloud_XYZ_filtered);
    //    reg.setInputCloud(cloud_XYZ);
        reg.setInputNormals(normals);
        reg.setSmoothnessThreshold(10.0 / 180.0 * M_PI);
        reg.setCurvatureThreshold(1.0);

        std::vector<pcl::PointIndices> clusters;
        reg.extract(clusters);

        cout << "Number of clusters is equal to " << clusters.size() << endl;
        cout << "First cluster has " << clusters[0].indices.size() << " points." << endl;
    }


    // Publish the colored cloud
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();
    sensor_msgs::PointCloud2 outcloud;

    // if (colored_cloud != nullptr)
    if (colored_cloud != NULL)
    {
        pcl::toROSMsg(*colored_cloud, outcloud);
    }
    else
    {
        // std::cout << "No colored cloud detected" << std::endl;
    }
    outcloud.header.frame_id = "/camera_depth_frame";
    outcloud.header.stamp = ros::Time::now();
    pub.publish(outcloud);
}

int main (int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "region_grower");
    ros::NodeHandle nh;

    // Create a ROS subscriber for the input point cloud
    ros::Subscriber sub = nh.subscribe("input", 1, cloud_cb);

    // Create a ROS publisher for the output point cloud
    pub = nh.advertise<pcl::PCLPointCloud2>("region_growing", 1);

    // Spin
    ros::spin();
}
