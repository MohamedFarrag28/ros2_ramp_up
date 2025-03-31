#include "rclcpp/rclcpp.hpp"
#include "my_custom_interfaces/srv/add_three_ints.hpp"


class AddThreeIntsServer : public rclcpp::Node
{
public:
    AddThreeIntsServer() : Node("add_three_ints_server")
    {
        service_ = this->create_service<my_custom_interfaces::srv::AddThreeInts>(
            "add_three_ints",
            std::bind(&AddThreeIntsServer::handle_service, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "AddThreeInts Server is ready.");
    }

private:
    void handle_service(
        const std::shared_ptr<my_custom_interfaces::srv::AddThreeInts::Request> request,
        std::shared_ptr<my_custom_interfaces::srv::AddThreeInts::Response> response)
    {
        response->sum = request->a + request->b + request->c;
        RCLCPP_INFO(this->get_logger(), "Received: [%ld, %ld, %ld] -> Sending: [%ld]",
                    request->a, request->b, request->c, response->sum);
    }

    rclcpp::Service<my_custom_interfaces::srv::AddThreeInts>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddThreeIntsServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
