
#ifndef __COMMUNICATION_NODE_H__
#define __COMMUNICATION_NODE_H__

#include <gz/math/Quaternion.hh>
#include <gz/math/Vector3.hh>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/msg/imu.hpp>



class CommunicationNode
{
public:
    CommunicationNode();

    geometry_msgs::msg::Twist read();
    void publish(gz::math::Vector3d const& position,
        gz::math::Quaterniond const& orientation,
        gz::math::Vector3d const& linearVelocity,
        gz::math::Vector3d const& angularVelocity) const;

    gz::math::Vector3d getGyro() const;
    gz::math::Quaterniond getOrientation() const;

private:
    void broadcast(gz::math::Vector3d const& position, gz::math::Quaterniond const& orientation) const;
    void onImuMessage(sensor_msgs::msg::Imu::SharedPtr const& message);

    rclcpp::Node::SharedPtr _node;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr _odometryPublisher;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _commandSubscription;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr _imuSubscription;

    gz::math::Vector3d _gyro;
    gz::math::Quaterniond _orientation;

    std::unique_ptr<tf2_ros::TransformBroadcaster> _tfBroadcaster;

    geometry_msgs::msg::Twist _lastCommand;

    std::mutex _commandMutex;
};

#endif