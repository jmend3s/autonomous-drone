
#include "CommunicationNode.h"

CommunicationNode::CommunicationNode()
{
    int constexpr argc = 0;
    char** const argv = nullptr;
    rclcpp::init(argc, argv);

    _communicationNode = rclcpp::Node::make_shared("teensy_emulator_communications");
    _commandSubscription = _communicationNode->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel",
        10,
        [this](geometry_msgs::msg::Twist::SharedPtr const message)
        {
            std::scoped_lock lock(_commandMutex);
            _lastCommand = *message;
        });
}

geometry_msgs::msg::Twist CommunicationNode::read()
{
    rclcpp::spin_some(_communicationNode);
    std::scoped_lock lock(_commandMutex);
    return _lastCommand;
}
