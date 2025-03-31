#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/msg/num.hpp" 

class NumPublisher : public rclcpp::Node
{
public:
    NumPublisher() : Node("num_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<my_custom_interfaces::msg::Num>("num_topic", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&NumPublisher::publish_message, this));
    }

private:
    void publish_message()
    {
        auto message = my_custom_interfaces::msg::Num();
        message.num = count_++;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", message.num);
        publisher_->publish(message);
    }

    rclcpp::Publisher<my_custom_interfaces::msg::Num>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NumPublisher>());
    rclcpp::shutdown();
    return 0;
}
