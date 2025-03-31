#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/msg/num.hpp"

class NumSubscriber : public rclcpp::Node
{
public:
    NumSubscriber() : Node("num_subscriber")
    {
        subscription_ = this->create_subscription<my_custom_interfaces::msg::Num>(
            "num_topic", 10,
            std::bind(&NumSubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const my_custom_interfaces::msg::Num::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Received: '%ld'", msg->num);
    }

    rclcpp::Subscription<my_custom_interfaces::msg::Num>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NumSubscriber>());
    rclcpp::shutdown();
    return 0;
}
