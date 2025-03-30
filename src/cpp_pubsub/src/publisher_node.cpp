// Include necessary ROS 2 headers
#include "rclcpp/rclcpp.hpp"   
#include "std_msgs/msg/string.hpp"  

// Define a class that inherits from rclcpp::Nodev ----> {making it a ROS 2 node} 
class MinimalPublisher : public rclcpp::Node {
public:
    // Constructor for the publisher node
    MinimalPublisher() : Node("minimal_publisher"), count_(0) {
        // Create a publisher for std_msgs::msg::String messages on the "topic" topic
        // The queue size of 10 sets the maximum number of messages to buffer before dropping or blocking new ones.
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        
        // Create a timer that triggers the publish_message function every 500 milliseconds
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),                      // Interval: 500ms
            std::bind(&MinimalPublisher::publish_message, this)  // Bind the function with the object
        );
    }

private:
    // Function to publish messages
    void publish_message() {
        auto message = std_msgs::msg::String();                             // Create a String message
        message.data = "Hello, ROS 2! Count: " + std::to_string(count_++);  // Set the message content

        // Print message to console (ROS 2 logging system)
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());

        publisher_->publish(message);  // Publish the message to the topic
    }

    // Declare a publisher object that will publish messages to the "topic"
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    // Declare a timer object that will call publish_message() at regular intervals
    rclcpp::TimerBase::SharedPtr timer_;

    // Counter to track the number of messages published
    size_t count_;
};

// Main function to initialize and run the ROS 2 node
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);  // Initialize the ROS 2 system
    rclcpp::spin(std::make_shared<MinimalPublisher>());  // Start the node and keep it running
    rclcpp::shutdown();  // Cleanup before exiting
    return 0;
}

