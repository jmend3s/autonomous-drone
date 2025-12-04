
#include "PIDPositionController.h"

PIDPositionController::PIDPositionController()
    : Node("PID_position_control_node")
    , _targetX(0), _targetY(0), _targetZ(1)
    , _kp { 1.5, 1.5, 3.0 }, _kd { 0.2, 0.2, 0.5 }, _ki { 0.0, 0.0, 0.0 }
    , _velocityCommandX(0), _velocityCommandY(0), _velocityCommandZ(0)
    , _integralX(0), _integralY(0), _integralZ(0)
    , _dt(0.01)
{
    _odometrySubscriber = create_subscription<nav_msgs::msg::Odometry>("/drone/odom", 10,
        [this](nav_msgs::msg::Odometry::SharedPtr msg) { odometryCallback(msg); });

    _targetSubscriber = create_subscription<geometry_msgs::msg::PoseStamped>("/target_pose", 10,
        [this](geometry_msgs::msg::PoseStamped::SharedPtr msg)
        {
            _targetX = msg->pose.position.x;
            _targetY = msg->pose.position.y;
            _targetZ = msg->pose.position.z;

            RCLCPP_INFO(get_logger(), "Target set to: [%.2f, %.2f, %.2f]", _targetX, _targetY, _targetZ);
        });

    _commandPublisher = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
}

void PIDPositionController::odometryCallback(nav_msgs::msg::Odometry::SharedPtr const msg)
{
    double const x = msg->pose.pose.position.x;
    double const y = msg->pose.pose.position.y;
    double const z = msg->pose.pose.position.z;

    double const errorX = _targetX - x;
    double const errorY = _targetY - y;
    double const errorZ = _targetZ - z;

    _integralX += errorX * _dt;
    _integralY += errorY * _dt;
    _integralZ += errorZ * _dt;

    double const derivativeX = -msg->twist.twist.linear.x;
    double const derivativeY = -msg->twist.twist.linear.y;
    double const derivativeZ = -msg->twist.twist.linear.z;

    _velocityCommandX = _kp[0] * errorX + _kd[0] * derivativeX + _ki[0] * _integralX;
    _velocityCommandY = _kp[1] * errorY + _kd[1] * derivativeY + _ki[1] * _integralY;
    _velocityCommandZ = _kp[2] * errorZ + _kd[2] * derivativeZ + _ki[2] * _integralZ;

    _velocityCommandX = std::clamp(_velocityCommandX, -2.0, 2.0);
    _velocityCommandY = std::clamp(_velocityCommandY, -2.0, 2.0);
    _velocityCommandZ = std::clamp(_velocityCommandZ, -1.0, 1.0);

    geometry_msgs::msg::Twist command;
    command.linear.x = _velocityCommandX;
    command.linear.y = _velocityCommandY;
    command.linear.z = _velocityCommandZ;

    _commandPublisher->publish(command);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PIDPositionController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}