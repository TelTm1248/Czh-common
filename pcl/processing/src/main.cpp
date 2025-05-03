#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_cloud.h>
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;

    PointCloud::Ptr cloud(new PointCloud);
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("input.pcd", *cloud) == -1) {
        PCL_ERROR("Couldn't read file input.pcd\n");
        return (-1);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255); //为每个点添加随机颜色

    for (size_t i = 0; i < cloud->size(); ++i) {
        cloud->points[i].r = dis(gen);
        cloud->points[i].g = dis(gen);
        cloud->points[i].b = dis(gen);
    }
    
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));  //创建可视化对象
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(1.0);

    viewer->addPointCloud<PointT>(cloud, "colored_cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "colored_cloud");
    while (!viewer->wasStopped()) {
        viewer->spinOnce(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}