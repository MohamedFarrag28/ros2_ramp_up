#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

class AddressBookSubscriber : public rclcpp::Node
{
public:
    AddressBookSubscriber() : Node("address_book_subscriber")
    {
        subscription_ = this->create_subscription<more_interfaces::msg::AddressBook>(
            "address_book", 10, std::bind(&AddressBookSubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const more_interfaces::msg::AddressBook::SharedPtr msg) const
    {
        std::string phone_type;
        switch (msg->phone_type)
        {
        case more_interfaces::msg::AddressBook::PHONE_TYPE_HOME:
            phone_type = "Home";
            break;
        case more_interfaces::msg::AddressBook::PHONE_TYPE_WORK:
            phone_type = "Work";
            break;
        case more_interfaces::msg::AddressBook::PHONE_TYPE_MOBILE:
            phone_type = "Mobile";
            break;
        default:
            phone_type = "Unknown";
            break;
        }

        RCLCPP_INFO(this->get_logger(), "Received: %s %s, Phone: %s, Type: %s",
                    msg->first_name.c_str(), msg->last_name.c_str(),
                    msg->phone_number.c_str(), phone_type.c_str());
    }

    rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddressBookSubscriber>());
    rclcpp::shutdown();
    return 0;
}
