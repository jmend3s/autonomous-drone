
#ifndef __DRONE_TEENSY_EMULATOR_H__
#define __DRONE_TEENSY_EMULATOR_H__

#include <gz/sim/System.hh>
#include <gz/sim/Joint.hh>

#include <rclcpp/rclcpp.hpp>

#include <chrono>


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
        void Configure(gz::sim::Entity const& entity,
                       std::shared_ptr<sdf::Element const> const& sdf,
                       gz::sim::EntityComponentManager& ecm,
                       gz::sim::EventManager& eventMgr) override;
        void PreUpdate(gz::sim::UpdateInfo const& _info,
                        gz::sim::EntityComponentManager& _ecm) override;
        void PostUpdate(gz::sim::UpdateInfo const& _info,
                        gz::sim::EntityComponentManager const& _ecm) override;

    private:
        void extractFromSdf(std::shared_ptr<sdf::Element const> const& sdf);

        gz::sim::Entity _entity;

        gz::math::Vector3d _position;
        gz::math::Vector3d _velocity;
        gz::math::Vector3d _angularVelocity;
        gz::math::Quaternion<double> _orientation;

        rclcpp::Node::SharedPtr _node;

        double _controlPeriod;
        double _updateRate;

        double _damping;
        double _gravity;
        double _thrustCommand;

        std::map<std::string, double&> const _sdfElements = {
        { "damping" , _damping },
        { "gravity ", _gravity },
        { "thrust_command ", _thrustCommand },
        { "update_rate" , _updateRate }
        };
    };
}

#endif