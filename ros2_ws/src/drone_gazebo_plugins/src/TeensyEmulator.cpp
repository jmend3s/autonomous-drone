
#include "TeensyEmulator.h"

#include <gz/plugin/Register.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Util.hh>


DroneTeensyEmulator::TeensyEmulator::TeensyEmulator()
    : _entity(gz::sim::kNullEntity)
    , _position(0, 0, 1.0)
    , _linearVelocity(0, 0, 0)
    , _angularVelocity(0, 0, 0)
    , _orientation(0, 0, 0)
    , _damping(0.0)
    , _gravity(0.0)
    , _thrustCommand(0.0)
    , _controlPeriod(1.0)
    , _updateRate(0.0)
{
}

DroneTeensyEmulator::TeensyEmulator::~TeensyEmulator()
{
    rclcpp::shutdown();
}

void DroneTeensyEmulator::TeensyEmulator::Configure(gz::sim::Entity const& entity,
    std::shared_ptr<sdf::Element const> const& sdf, gz::sim::EntityComponentManager& ecm,
    gz::sim::EventManager& eventMgr)
{
    extractValuesFromSdf(sdf);
    _entity = entity;
    _controlPeriod /= _updateRate;

    gzmsg << "[TeensyEmulator] Configuration done" << std::endl;
}

void DroneTeensyEmulator::TeensyEmulator::PreUpdate(const gz::sim::UpdateInfo& info,
    gz::sim::EntityComponentManager& ecm)
{
    if (!info.paused)
    {
        auto command = _communicationNode.read();

        _linearVelocity = { command.linear.x, command.linear.y, command.linear.z };
        _angularVelocity = { command.angular.x, command.angular.y, command.angular.z };

        if (auto const dt = std::chrono::duration<double>(info.dt).count();
            dt > 0.0)
        {
            _position += _linearVelocity * dt;

            if (auto const angle = _angularVelocity.Length() * dt;
                angle > 1e-6)
            {
                auto const axis = _angularVelocity.Normalized();
                gz::math::Quaternion const q_delta(axis, angle);
                _orientation *= q_delta;
                _orientation.Normalize();
            }

            gz::sim::Model model(_entity);
            model.SetWorldPoseCmd(ecm, { _position, _orientation });
        }
    }
}

void DroneTeensyEmulator::TeensyEmulator::PostUpdate(const gz::sim::UpdateInfo& info,
    const gz::sim::EntityComponentManager& ecm)
{
    _communicationNode.publish(_position, _orientation, _linearVelocity, _angularVelocity);
}

void DroneTeensyEmulator::TeensyEmulator::extractValuesFromSdf(std::shared_ptr<sdf::Element const> const& sdf)
{
    std::map<std::string, double&> sdfElements = {
        { "damping" , _damping },
        { "gravity", _gravity },
        { "thrust_command", _thrustCommand },
        { "update_rate" , _updateRate }
    };

    for (auto& [sdfElement, member] : sdfElements)
    {
        member = sdf->HasElement(sdfElement) ? sdf->Get<double>(sdfElement) : 0.0;
    }
}

GZ_ADD_PLUGIN(
    DroneTeensyEmulator::TeensyEmulator,
    gz::sim::System,
    DroneTeensyEmulator::TeensyEmulator::ISystemConfigure,
    DroneTeensyEmulator::TeensyEmulator::ISystemPreUpdate,
    DroneTeensyEmulator::TeensyEmulator::ISystemPostUpdate
)
GZ_ADD_PLUGIN_ALIAS(DroneTeensyEmulator::TeensyEmulator, "TeensyEmulator")
