// Include necessary ROS 2 headers
#include "rclcpp/rclcpp.hpp"   
#include "std_msgs/msg/string.hpp" 

// Define a subscriber node class that inherits from rclcpp::Node
class MinimalSubscriber : public rclcpp::Node {
public:
    // Constructor for the subscriber node
    MinimalSubscriber() : Node("minimal_subscriber") {
        // Create a subscription to listen to "topic"
        // The queue size of 10 ensures messages are received even if processing is slightly delayed
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "topic",  // Name of the topic to subscribe to
            10,  // Queue size
            std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1)  // Callback function
        );
    }

private:
    // Callback function to process received messages
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) {
        // Print the received message using the ROS 2 logging system
        RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
    }

    // Declare a subscription object that will receive messages from the "topic"
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

// Main function to initialize and run the ROS 2 node
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);  // Initialize the ROS 2 system
    rclcpp::spin(std::make_shared<MinimalSubscriber>());  // Start the node and keep it running
    rclcpp::shutdown();  // Cleanup before exiting
    return 0;
}
