#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"  // Service message type


class MinimalClient : public rclcpp::Node
{
public:
    MinimalClient() : Node("minimal_client")
    {
        client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

        // Wait for the service to be available
         while (!client_->wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_WARN(this->get_logger(), "Waiting for service to become available...");
        }
        RCLCPP_INFO(this->get_logger(), "Client is ready to send requests.");
    }

    // Function to send a request
    void send_request(int64_t a, int64_t b)
    {
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        // Call the service asynchronously
        auto result_future = client_->async_send_request(request);
        
        // Wait for the response
        if (rclcpp::spin_until_future_complete(this->shared_from_this(), result_future) ==
            rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "Result: %ld", result_future.get()->sum);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service.");
        }
    }

private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
};

// Main function
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    if (argc != 3)  // Expecting two integer arguments
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Usage: client_node <int_a> <int_b>");
        return 1;
    }

    int64_t a = std::atoll(argv[1]);  // Convert input to integers
    int64_t b = std::atoll(argv[2]);

    auto client_node = std::make_shared<MinimalClient>();


    if (!rclcpp::ok()) // Check if interrupted before sending request
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "ROS was interrupted before sending request.");
        rclcpp::shutdown();
        return 1;
    }
    
    // Send a request with sample values
    client_node->send_request(a, b);

    rclcpp::shutdown();
    return 0;
}
