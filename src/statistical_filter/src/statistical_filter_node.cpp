#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "statistical");
    ros::NodeHandle nh;

    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::io::loadPCDFile("laser.pcd", laser);

    pcl::StatisticalOutlierRemoval<pcl::PointXYZI> statistical;
    statistical.setInputCloud(laser.makeShared());
    statistical.setMeanK(20);
    statistical.setStddevMulThresh(1);
    //statistical.setNegative(true);
    statistical.filter(laser);

    pcl::io::savePCDFile("statistical.pcd", laser);
    return 0;
}

