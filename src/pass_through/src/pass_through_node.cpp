#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/passthrough.h>
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pass_through");
    pcl::PointCloud<pcl::PointXYZI> laser;
    pcl::io::loadPCDFile("laser.pcd", laser);

    pcl::PassThrough<pcl::PointXYZI> pass_through;
    pass_through.setInputCloud(laser.makeShared());
    pass_through.setFilterFieldName("z");
    pass_through.setFilterLimits(-2.5, -1.0);   //按照z轴大小过滤
    pass_through.setFilterLimitsNegative(true); //true保存outer false保存inter
    pass_through.filter(laser);

    double max_z = -10.0;
    std::cout << max_z << std::endl;
    for(int i = 0; i < laser.points.size(); i ++)
    {
        pcl::PointXYZI point = laser.points[i];
        if(max_z < point.z)
        {
            max_z = point.z;
        }
    }

    std::cout << max_z << std::endl;
    pcl::io::savePCDFile("pass_through.pcd", laser);
    return 0;
}

