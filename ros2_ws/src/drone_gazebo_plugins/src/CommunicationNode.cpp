
#include "CommunicationNode.h"


CommunicationNode::CommunicationNode()
{
    int constexpr argc = 0;
    char** const argv = nullptr;
    rclcpp::init(argc, argv);

    _node = rclcpp::Node::make_shared("teensy_emulator_communications");
    _odometryPublisher = _node->create_publisher<nav_msgs::msg::Odometry>("/drone/odometry", 10);
    _commandSubscription = _node->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel",
        10,
        [this](geometry_msgs::msg::Twist::SharedPtr const message)
        {
            std::scoped_lock lock(_commandMutex);
            _lastCommand = *message;
        });

    _tfBroadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(_node);
}

geometry_msgs::msg::Twist CommunicationNode::read()
{
    rclcpp::spin_some(_node);
    std::scoped_lock lock(_commandMutex);
    return _lastCommand;
}

void CommunicationNode::publish(gz::math::Vector3d const& position,
    gz::math::Quaterniond const& orientation,
    gz::math::Vector3d const& linearVelocity,
    gz::math::Vector3d const& angularVelocity) const
{
    nav_msgs::msg::Odometry odometryMessage;

    odometryMessage.header.stamp = _node->get_clock()->now();
    odometryMessage.header.frame_id = "odom";
    odometryMessage.child_frame_id = "base_link";

    odometryMessage.pose.pose.position.x = position.X();
    odometryMessage.pose.pose.position.y = position.Y();
    odometryMessage.pose.pose.position.z = position.Z();
    odometryMessage.pose.pose.orientation.x = orientation.X();
    odometryMessage.pose.pose.orientation.y = orientation.Y();
    odometryMessage.pose.pose.orientation.z = orientation.Z();
    odometryMessage.pose.pose.orientation.w = orientation.W();

    odometryMessage.twist.twist.linear.x = linearVelocity.X();
    odometryMessage.twist.twist.linear.y = linearVelocity.Y();
    odometryMessage.twist.twist.linear.z = linearVelocity.Z();
    odometryMessage.twist.twist.angular.x = angularVelocity.X();
    odometryMessage.twist.twist.angular.y = angularVelocity.Y();
    odometryMessage.twist.twist.angular.z = angularVelocity.Z();

    broadcast(position, orientation);
    _odometryPublisher->publish(odometryMessage);
}

void CommunicationNode::broadcast(gz::math::Vector3d const& position, gz::math::Quaterniond const& orientation) const
{
    geometry_msgs::msg::TransformStamped transformStamped;
    transformStamped.header.stamp = _node->get_clock()->now();
    transformStamped.header.frame_id = "odom";
    transformStamped.child_frame_id = "base_footprint";

    transformStamped.transform.translation.x = position.X();
    transformStamped.transform.translation.y = position.Y();
    transformStamped.transform.translation.z = position.Z();
    transformStamped.transform.rotation.x = orientation.X();
    transformStamped.transform.rotation.y = orientation.Y();
    transformStamped.transform.rotation.z = orientation.Z();
    transformStamped.transform.rotation.w = orientation.W();

    _tfBroadcaster->sendTransform(transformStamped);
}
