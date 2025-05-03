#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

class Founder : public rclcpp::Node {
public:
    Founder() : Node("founder") {
        // 声明参数
        declare_parameters();
        
        // 获取并打印参数
        print_parameters();
        
        // 创建发布者和定时器
        publisher_ = create_publisher<std_msgs::msg::Float64MultiArray>("tracker_params", 10);
        timer_ = create_wall_timer(1000ms, std::bind(&Founder::timer_callback, this));
    }

private:
    void declare_parameters() {
        this->declare_parameter("ekf.xyz", 0.0);
        this->declare_parameter("ekf.yaw", 0.0);
        this->declare_parameter("ekf.r", 0.0);
        this->declare_parameter("vx", 0);
        this->declare_parameter("vy", 0);
        this->declare_parameter("vz", 0);
    }

    void print_parameters() {
        RCLCPP_INFO(get_logger(), "Loaded parameters:");
        RCLCPP_INFO(get_logger(), "ekf.xyz: %.3f", get_parameter("ekf.xyz").as_double());
        RCLCPP_INFO(get_logger(), "ekf.yaw: %.3f", get_parameter("ekf.yaw").as_double());
        RCLCPP_INFO(get_logger(), "ekf.r: %.3f", get_parameter("ekf.r").as_double());
        RCLCPP_INFO(get_logger(), "vx: %d", get_parameter("vx").as_int());
        RCLCPP_INFO(get_logger(), "vy: %d", get_parameter("vy").as_int());
        RCLCPP_INFO(get_logger(), "vz: %d", get_parameter("vz").as_int());
    }

    void timer_callback() {
        auto msg = std_msgs::msg::Float64MultiArray();
        msg.data = {
            get_parameter("ekf.xyz").as_double(),
            get_parameter("ekf.yaw").as_double(),
            get_parameter("ekf.r").as_double(),
            static_cast<double>(get_parameter("vx").as_int()),
            static_cast<double>(get_parameter("vy").as_int()),
            static_cast<double>(get_parameter("vz").as_int())
        };
        
        publisher_->publish(msg);
        RCLCPP_INFO(get_logger(), "Published parameters to tracker");
    }

    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Founder>());
    rclcpp::shutdown();
    return 0;
}