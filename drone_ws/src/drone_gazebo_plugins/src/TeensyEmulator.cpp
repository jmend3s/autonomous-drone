
#include "TeensyEmulator.h"

#include <gz/sim/Model.hh>
#include <gz/plugin/Register.hh>
#include <gz/sim/Util.hh>


DroneTeensyEmulator::TeensyEmulator::TeensyEmulator()
    : _position(0, 0, 1.0)
    , _velocity(0, 0, 0)
    , _angularVelocity(0, 0, 0)
    , _orientation(0, 0, 0)
{
}

void DroneTeensyEmulator::TeensyEmulator::Configure(gz::sim::Entity const& entity,
    std::shared_ptr<sdf::Element const> const& sdf, gz::sim::EntityComponentManager& ecm,
    gz::sim::EventManager& eventMgr)
{
    extractFromSdf(sdf);
    _controlPeriod = 1.0 / _updateRate;
    _entity = entity;

    rclcpp::init(0, nullptr);
    _node = rclcpp::Node::make_shared("teensy_emulator");

    gzmsg << "[TeensyEmulator] Configure() done" << std::endl;
}

void DroneTeensyEmulator::TeensyEmulator::PreUpdate(const gz::sim::UpdateInfo& _info,
    gz::sim::EntityComponentManager& _ecm)
{
}

void DroneTeensyEmulator::TeensyEmulator::PostUpdate(const gz::sim::UpdateInfo& _info,
    const gz::sim::EntityComponentManager& _ecm)
{
}

void DroneTeensyEmulator::TeensyEmulator::extractFromSdf(std::shared_ptr<sdf::Element const> const& sdf)
{
    for (auto const& [sdfElement, localValue] : _sdfElements)
    {
        localValue = sdf->HasElement(sdfElement) ?
            sdf->Get<double>(sdfElement) : 0.0;
        _updateRate = sdf->Get<double>("update_rate");
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
