
#include "OdomMonitor.h"


OdomMonitor::OdomMonitor()
    : Node("odom_monitor")
    , _hasLast(false)
    , _lastX(0.0)
    , _lastY(0.0)
    , _lastZ(0.0)
{
    _odomSubscriber = create_subscription<nav_msgs::msg::Odometry>("/drone/odom", 10,
        [this](nav_msgs::msg::Odometry::SharedPtr const message) { odomCallback(message); });
}

void OdomMonitor::odomCallback(nav_msgs::msg::Odometry::SharedPtr message)
{
    double const x = message->pose.pose.position.x;
    double const y = message->pose.pose.position.y;
    double const z = message->pose.pose.position.z;

    if (std::isfinite(x) || std::isfinite(y) || std::isfinite(z))
    {
        if (std::abs(x) > 1000.0 || std::abs(y) > 1000.0 || std::abs(z) > 1000.0)
        {
            RCLCPP_ERROR(this->get_logger(), "ABSURD odom: [x=%.3f, y=%.3f, z=%.3f]",
                x, y, z);
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Odom: [%.2f, %.2f, %.2f]", x, y, z);
        }

        if (_hasLast)
        {
            double const dx = x - _lastX;
            double const dy = y - _lastY;
            double const dz = z - _lastZ;

            double const distance = std::sqrt(dx*dx + dy*dy + dz*dz);

            if (distance > 5.0) // moved > 5 m in one step? probably wrong
            {
                RCLCPP_WARN(this->get_logger(), "BIG JUMP in odom: Δ[%.2f, %.2f, %.2f] (distance=%.2f)",
                    dx, dy, dz, distance);
            }
        }

        _hasLast = true;
        _lastX = x;
        _lastY = y;
        _lastZ = z;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "NON-FINITE odom: [x=%.3f, y=%.3f, z=%.3f]", x, y, z);
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<OdomMonitor>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}