
#ifndef __ODOM_MONITOR_H__
#define __ODOM_MONITOR_H__

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>


class OdomMonitor : public rclcpp::Node
{
public:
    OdomMonitor();

private:
    void odomCallback(nav_msgs::msg::Odometry::SharedPtr message);

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr _odomSubscriber;

    bool _hasLast;

    double _lastX;
    double _lastY;
    double _lastZ;
};

#endif