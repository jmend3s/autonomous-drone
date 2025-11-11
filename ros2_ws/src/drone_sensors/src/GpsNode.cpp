
#include "GpsNode.h"


GpsNode::GpsNode()
    : Node("gps_node")
{
    _subscriber = create_subscription<sensor_msgs::msg::NavSatFix>("drone/gps", 10,
        [this](sensor_msgs::msg::NavSatFix::ConstSharedPtr message) { gpsCallback(message); });
    _publisher = create_publisher<sensor_msgs::msg::NavSatFix>("gps/fix", 10);
}

void GpsNode::gpsCallback(sensor_msgs::msg::NavSatFix::ConstSharedPtr message)
{
    auto publisherMessage = *message;
    publisherMessage.header.frame_id = "base_link";
    _publisher->publish(publisherMessage);
}
