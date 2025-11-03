
#ifndef __COMMUNICATION_NODE_H__
#define __COMMUNICATION_NODE_H__

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>


class CommunicationNode
{
public:
    CommunicationNode();
    geometry_msgs::msg::Twist read();

private:
    rclcpp::Node::SharedPtr _communicationNode;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _commandSubscription;

    geometry_msgs::msg::Twist _lastCommand;

    std::mutex _commandMutex;
};

#endif