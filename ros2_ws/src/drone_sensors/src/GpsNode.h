
#ifndef __GPS_NODE_H__
#define __GPS_NODE_H__

#include <rclcpp/node.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>


class GpsNode : public rclcpp::Node
{
public:
    GpsNode();

private:
    void gpsCallback(sensor_msgs::msg::NavSatFix::ConstSharedPtr message);

    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr _subscriber;
    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr _publisher;
};

#endif