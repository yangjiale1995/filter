#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>

ros::Publisher pub;

void callback(const sensor_msgs::PointCloud2::ConstPtr &msg)
{
    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::fromROSMsg(*msg, laser);
    std::cout << "laser " << laser.points.size() << std::endl; 

    pcl::VoxelGrid<pcl::PointXYZI> voxel;
    voxel.setInputCloud(laser.makeShared());
    voxel.setLeafSize(0.1, 0.1, 0.1);
    voxel.filter(laser);

    std::cout << "voxel " << laser.points.size() << std::endl;

    sensor_msgs::PointCloud2 newMsg;
    pcl::toROSMsg(laser, newMsg);
    newMsg.header = msg->header;
    pub.publish(newMsg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "voxel_grid");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points_200", 10, callback);
    pub = nh.advertise<sensor_msgs::PointCloud2>("yang", 10);

    ros::spin();

    /*
    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::io::loadPCDFile("laser.pcd", laser);

    pcl::VoxelGrid<pcl::PointXYZI> voxel;
    voxel.setInputCloud(laser.makeShared());
    voxel.setLeafSize(0.1, 0.1, 0.1);
    //voxel.setFilterLimitsNegative(false);
    voxel.filter(laser);

    pcl::io::savePCDFile("voxel_grid.pcd", laser);
    */
    return 0;
}

