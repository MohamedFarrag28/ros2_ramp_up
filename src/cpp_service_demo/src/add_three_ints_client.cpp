#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/srv/add_three_ints.hpp"

class AddThreeIntsClient : public rclcpp::Node
{
public:
    AddThreeIntsClient() : Node("add_three_ints_client")
    {
        client_ = this->create_client<my_custom_interfaces::srv::AddThreeInts>("add_three_ints");

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
    void send_request(int64_t a, int64_t b, int64_t c)
    {
        auto request = std::make_shared<my_custom_interfaces::srv::AddThreeInts::Request>();
        request->a = a;
        request->b = b;
        request->c = c;

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
    rclcpp::Client<my_custom_interfaces::srv::AddThreeInts>::SharedPtr client_;
};

// Main function
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    if (argc != 4)  // Expecting three integer arguments
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Usage: add_three_ints_client <int_a> <int_b> <int_c>");
        return 1;
    }

    int64_t a = std::atoll(argv[1]);  // Convert input to integers
    int64_t b = std::atoll(argv[2]);
    int64_t c = std::atoll(argv[3]);

    auto client_node = std::make_shared<AddThreeIntsClient>();

    if (!rclcpp::ok()) // Check if interrupted before sending request
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "ROS was interrupted before sending request.");
        rclcpp::shutdown();
        return 1;
    }

    // Send the request
    client_node->send_request(a, b, c);

    rclcpp::shutdown();
    return 0;
}
