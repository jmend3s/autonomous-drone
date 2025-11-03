
#ifndef __TEENSY_EMULATOR_H__
#define __TEENSY_EMULATOR_H__

#include "CommunicationNode.h"

#include <gz/sim/System.hh>
#include <gz/sim/Joint.hh>

#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>


namespace DroneTeensyEmulator
{
    class TeensyEmulator final
        : public gz::sim::System
        , public gz::sim::ISystemConfigure
        , public gz::sim::ISystemPreUpdate
        , public gz::sim::ISystemPostUpdate
    {
    public:
        TeensyEmulator();
        ~TeensyEmulator() override;

        void Configure(gz::sim::Entity const& entity, std::shared_ptr<sdf::Element const> const& sdf,
            gz::sim::EntityComponentManager& ecm, gz::sim::EventManager& eventMgr) override;
        void PreUpdate(gz::sim::UpdateInfo const& info, gz::sim::EntityComponentManager& ecm) override;
        void PostUpdate(gz::sim::UpdateInfo const& info, gz::sim::EntityComponentManager const& ecm) override;

    private:
        void extractValuesFromSdf(std::shared_ptr<sdf::Element const> const& sdf);

        gz::sim::Entity _entity;
        CommunicationNode _communicationNode;

        gz::math::Vector3d _position;
        gz::math::Vector3d _linearVelocity;
        gz::math::Vector3d _angularVelocity;
        gz::math::Quaternion<double> _orientation;

        double _damping;
        double _gravity;
        double _thrustCommand;

        double _controlPeriod;
        double _updateRate;
    };
}

#endif