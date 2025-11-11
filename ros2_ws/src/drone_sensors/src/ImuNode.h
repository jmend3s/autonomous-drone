
#ifndef __IMU_NODE_H__
#define __IMU_NODE_H__

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>


class ImuNode : public rclcpp::Node
{
public:
    ImuNode();

private:
    void imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr message);

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr _subscriber;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr _publisher;
};

#endif