
#ifndef __PID_POSITION_CONTROLLER_H__
#define __PID_POSITION_CONTROLLER_H__

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>


class PIDPositionController : public rclcpp::Node
{
public:
    PIDPositionController();

private:
    void odometryCallback(nav_msgs::msg::Odometry::SharedPtr msg);

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr _odometrySubscriber;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr _targetSubscriber;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr _commandPublisher;

    double _targetX;
    double _targetY;
    double _targetZ;

    double _kp[3];
    double _kd[3];
    double _ki[3];

    double _velocityCommandX;
    double _velocityCommandY;
    double _velocityCommandZ;

    double _integralX;
    double _integralY;
    double _integralZ;

    double _dt;
};

#endif