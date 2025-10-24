
#include "TeensyEmulator.h"

#include <gz/plugin/Register.hh>
#include <gz/sim/Util.hh>


void drone_gazebo_sim::TeensyEmulator::Configure(const gz::sim::Entity& _entity,
    const std::shared_ptr<const sdf::Element>& _sdf, gz::sim::EntityComponentManager& _ecm)
{
    _modelEntity = _entity;

    if (_sdf->HasElement("gain"))
    {
        _myGain = _sdf->Get<double>("gain");
    }
    gzmsg << "MyCustomController configured for entity: " <<
        gz::sim::scopedName(_entity, _ecm) <<
        " with gain: " << _myGain << std::endl;
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
