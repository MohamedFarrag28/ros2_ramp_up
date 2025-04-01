// Include necessary ROS 2 headers
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// Define a class that inherits from rclcpp::Node → {making it a ROS 2 node}
class MinimalPublisher : public rclcpp::Node {
public:
    // Constructor for the publisher node
    MinimalPublisher() : Node("minimal_publisher"), count_(0) {
        // Declare ROS 2 parameters with default values
        this->declare_parameter<std::string>("message_content", "Hello, ROS 2!");
        this->declare_parameter<int>("publish_rate", 500); // Default: 500ms

        // Retrieve the initial parameter values
        message_content_ = this->get_parameter("message_content").as_string();
        publish_rate_ = this->get_parameter("publish_rate").as_int();

        // Create a publisher for std_msgs::msg::String messages on the "topic" topic
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);

        // Create a timer that triggers the publish_message function at the given rate
        create_timer();

        // Set up a parameter callback to handle changes dynamically
        param_callback_handle_ = this->add_on_set_parameters_callback(
            std::bind(&MinimalPublisher::parameters_callback, this, std::placeholders::_1)
        );
    }

private:
    // Function to publish messages
    void publish_message() {
        auto message = std_msgs::msg::String();
        message.data = message_content_ + " Count: " + std::to_string(count_++);

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    // Function to create or update the timer
    void create_timer() {
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(publish_rate_),
            std::bind(&MinimalPublisher::publish_message, this)
        );
    }

    // Parameter callback function → called when parameters change
    rcl_interfaces::msg::SetParametersResult parameters_callback(
        const std::vector<rclcpp::Parameter>& parameters) 
    {
        rcl_interfaces::msg::SetParametersResult result;
        result.successful = true;

        for (const auto& param : parameters) {
            if (param.get_name() == "message_content") {
                message_content_ = param.as_string();
                RCLCPP_INFO(this->get_logger(), "Updated message_content: %s", message_content_.c_str());
            } 
            else if (param.get_name() == "publish_rate") {
                int new_rate = param.as_int();
                if (new_rate > 0) {
                    publish_rate_ = new_rate;
                    RCLCPP_INFO(this->get_logger(), "Updated publish_rate: %d ms", publish_rate_);
                    create_timer(); // Restart timer with new rate
                } else {
                    result.successful = false;
                    result.reason = "publish_rate must be greater than 0";
                }
            }
        }
        return result;
    }

    // Declare a publisher object that will publish messages to the "topic"
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    // Declare a timer object that will call publish_message() at regular intervals
    rclcpp::TimerBase::SharedPtr timer_;

    // Parameter callback handle
    OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;

    // Counter for tracking the number of messages published
    size_t count_;

    // Parameters (stored as class variables)
    std::string message_content_;
    int publish_rate_;
};

// Main function to initialize and run the ROS 2 node
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}
