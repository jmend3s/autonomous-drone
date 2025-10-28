
#include "TeensyEmulator.h"

#include <gz/sim/Model.hh>
#include <gz/plugin/Register.hh>
#include <gz/sim/Util.hh>


void drone_gazebo_sim::TeensyEmulator::Configure(gz::sim::Entity const& entity,
    std::shared_ptr<sdf::Element const> const& sdf, gz::sim::EntityComponentManager& ecm,
    gz::sim::EventManager& eventMgr)
{
    gzmsg << "[TeensyEmulator] Configure() called" << std::endl;

    _entity = entity;

    gz::sim::Model const model(_entity);
    auto const jointEntities =  model.Joints(ecm);

    for (auto const& joint_entity : jointEntities)
    {
        _motorJoints.emplace_back(joint_entity);
    }

    if (sdf->HasElement("update_rate"))
    {
        _updateRate = sdf->Get<double>("update_rate");
    }

    _controllPeriod = 1.0 / _updateRate;
    _lastSimTime = 0.0;

    rclcpp::init(0, nullptr);
    _node = rclcpp::Node::make_shared("teensy_emulator");

    gzmsg << "[TeensyEmulator] Configure() done" << std::endl;
}

void drone_gazebo_sim::TeensyEmulator::PreUpdate(const gz::sim::UpdateInfo& _info,
    gz::sim::EntityComponentManager& _ecm)
{
}

void drone_gazebo_sim::TeensyEmulator::PostUpdate(const gz::sim::UpdateInfo& _info,
    const gz::sim::EntityComponentManager& _ecm)
{
}


GZ_ADD_PLUGIN(
    drone_gazebo_sim::TeensyEmulator,
    gz::sim::System,
    drone_gazebo_sim::TeensyEmulator::ISystemConfigure,
    drone_gazebo_sim::TeensyEmulator::ISystemPreUpdate,
    drone_gazebo_sim::TeensyEmulator::ISystemPostUpdate
)
GZ_ADD_PLUGIN_ALIAS(drone_gazebo_sim::TeensyEmulator, "TeensyEmulator")
