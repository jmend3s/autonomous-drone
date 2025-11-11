
#include "ImuNode.h"

ImuNode::ImuNode()
    : Node("imu_node")
{
    _subscriber = create_subscription<sensor_msgs::msg::Imu>("drone/imu", 1,
        [this](sensor_msgs::msg::Imu::SharedPtr const message) { imuCallback(message); });
    _publisher = create_publisher<sensor_msgs::msg::Imu>("imu/data", 1);
}

void ImuNode::imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr message)
{
    auto publisherMessage = *message;
    publisherMessage.header.frame_id = "base_link";
    _publisher->publish(publisherMessage);
}
