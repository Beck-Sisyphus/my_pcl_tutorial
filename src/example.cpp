#include <ros/ros.h>
// PCL specific includes
#include <pcl/filters/voxel_grid.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

ros::Publisher pub;

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
	// Convert to ROS data type
	sensor_msgs::PointCloud2 output;
	
	// Do data processing here...
	output = *input;

	// Publish the data.
	pub.publish(output);
}

int main (int argc, char** argv)
{
	// Intialize ROS
	ros::init(argc, argv, "my_pcl_tutorial");
	ros::NodeHandle nh;
	
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe("input", 1, cloud_cb);
	
	// Create a ROS publisher for the ouput point cloud
	pub = nh.advertise<sensor_msgs::PointCloud2>("output", 1);

	// Spin
	ros::spin();
}
