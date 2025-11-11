
#include "GpsNode.h"
#include "ImuNode.h"

#include <rclcpp/rclcpp.hpp>


int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto executeNodes = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();

    auto imuNode = std::make_shared<ImuNode>();
    auto gpsNode = std::make_shared<GpsNode>();

    executeNodes->add_node(imuNode);
    executeNodes->add_node(gpsNode);

    executeNodes->spin();
    rclcpp::shutdown();
    return 0;
}