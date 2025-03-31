#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"  // Service message type

class MinimalService : public rclcpp::Node
{
public:
    MinimalService() : Node("minimal_service")
    {
        // Creating the service that listens for "add_two_ints" requests
        service_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints",
            std::bind(&MinimalService::handle_service, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "Service is ready to add two integers.");
    }

private:
    // Callback function for handling client requests
    void handle_service(
        const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        response->sum = request->a + request->b; // Process request
        RCLCPP_INFO(this->get_logger(), "Received request: %ld + %ld", request->a, request->b);
        RCLCPP_INFO(this->get_logger(), "Sending response: %ld", response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_;
};

// Main function
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalService>());
    rclcpp::shutdown();
    return 0;
}
