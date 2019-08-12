#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/conditional_removal.h>
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "conditional");
    ros::NodeHandle nh;

    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::io::loadPCDFile("laser.pcd", laser);
    
    return 0;
}

