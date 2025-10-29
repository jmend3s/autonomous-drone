#ifndef __DRONE_TEENSY_EMULATOR_H__
#define __DRONE_TEENSY_EMULATOR_H__

#include <gz/sim/System.hh>
#include <gz/sim/Joint.hh>

#include <rclcpp/rclcpp.hpp>


namespace DroneTeensyEmulator
{
    class TeensyEmulator
        : public gz::sim::System
        , public gz::sim::ISystemConfigure
        , public gz::sim::ISystemPreUpdate
        , public gz::sim::ISystemPostUpdate
    {
    public:

        void Configure(gz::sim::Entity const& entity,
                        std::shared_ptr<sdf::Element const> const& sdf,
                        gz::sim::EntityComponentManager& ecm,
                        gz::sim::EventManager& eventMgr) override;
        void PreUpdate(gz::sim::UpdateInfo const& _info,
                        gz::sim::EntityComponentManager& _ecm) override;
        void PostUpdate(gz::sim::UpdateInfo const& _info,
                        gz::sim::EntityComponentManager const& _ecm) override;
    private:
        gz::sim::Entity _entity{gz::sim::kNullEntity};
        std::array<gz::sim::Joint, 6> _motorJoints;

        rclcpp::Node::SharedPtr _node;

        gz::math::Vector3d _position;
        gz::math::Vector3d _velocity;
        gz::math::Vector3d _angularVelocity;
        gz::math::Quaternion<double> _orientation;
        double _thrustCommand;

        double _controllPeriod;
        double _updateRate;
        double _lastSimTime;

        double _myGain{1.0};
    };
}

#endif