#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "approximate");
    ros::NodeHandle nh;

    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::io::loadPCDFile("laser.pcd", laser);

    pcl::ApproximateVoxelGrid<pcl::PointXYZI> voxel;
    voxel.setInputCloud(laser.makeShared());
    voxel.setLeafSize(0.05, 0.05, 0.05);
    voxel.filter(laser);

    pcl::io::savePCDFile("approximate.pcd", laser);
    
    return 0;
}

