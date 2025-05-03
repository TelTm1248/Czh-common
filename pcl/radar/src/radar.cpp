#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <point_cloud_file.pcd>" << std::endl;
        return -1;
    }

    // 创建点云对象
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 加载点云文件
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) == -1) {
        PCL_ERROR("Couldn't read file %s\n", argv[1]);
        return -1;
    }

    // 创建可视化对象
    pcl::visualization::PCLVisualizer viewer("Point Cloud Viewer");

    // 添加点云到可视化窗口
    viewer.addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    viewer.setBackgroundColor(0, 0, 0); // 设置背景为黑色
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");

    // 添加坐标系
    viewer.addCoordinateSystem(1.0);

    // 主循环
    while (!viewer.wasStopped()) {
        viewer.spinOnce(100);
    }
    
    return 0;
}