#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class Tracker : public rclcpp::Node {
public:
    Tracker() : Node("tracker") {
        subscription_ = create_subscription<std_msgs::msg::Float64MultiArray>(
            "tracker_params", 10, std::bind(&Tracker::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) const {
        if (msg->data.size() == 6) {
            RCLCPP_INFO(get_logger(), "Received parameters:");
            RCLCPP_INFO(get_logger(), "ekf.xyz: %.3f", msg->data[0]);
            RCLCPP_INFO(get_logger(), "ekf.yaw: %.3f", msg->data[1]);
            RCLCPP_INFO(get_logger(), "ekf.r: %.3f", msg->data[2]);
            RCLCPP_INFO(get_logger(), "vx: %d", static_cast<int>(msg->data[3]));
            RCLCPP_INFO(get_logger(), "vy: %d", static_cast<int>(msg->data[4]));
            RCLCPP_INFO(get_logger(), "vz: %d", static_cast<int>(msg->data[5]));
        } else {
            RCLCPP_ERROR(get_logger(), "Invalid parameter count received: %zu", msg->data.size());
        }
    }

    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Tracker>());
    rclcpp::shutdown();
    return 0;
}