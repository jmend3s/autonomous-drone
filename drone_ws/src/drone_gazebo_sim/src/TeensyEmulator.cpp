
#include "TeensyEmulator.h"

#include <gz/plugin/Register.hh>
#include <gz/sim/Util.hh>


void drone_gazebo_sim::TeensyEmulator::Configure(const gz::sim::Entity& _entity,
    const std::shared_ptr<const sdf::Element>& _sdf, gz::sim::EntityComponentManager& _ecm,
    gz::sim::EventManager& _eventMgr)
{
    gzmsg << "[TeensyEmulator] Configure() called" << std::endl;
    _modelEntity = _entity;

    if (_sdf->HasElement("gain"))
    {
        _myGain = _sdf->Get<double>("gain");
    }

    _myGain = 135.0;
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
    static int counter = 0;
    if ((counter++ % 1000) == 0)   // print roughly once per 1000 ticks
    {
        gzdbg << "[TeensyEmulator] Sim time: "
              << std::fixed << std::setprecision(2)
              << _info.simTime.count() / 1e9   // seconds
              << "s  Gain=" << _myGain << std::endl;
    }
}


GZ_ADD_PLUGIN(
    drone_gazebo_sim::TeensyEmulator,
    gz::sim::System,
    drone_gazebo_sim::TeensyEmulator::ISystemConfigure,
    drone_gazebo_sim::TeensyEmulator::ISystemPreUpdate,
    drone_gazebo_sim::TeensyEmulator::ISystemPostUpdate
)
GZ_ADD_PLUGIN_ALIAS(drone_gazebo_sim::TeensyEmulator, "TeensyEmulator")
