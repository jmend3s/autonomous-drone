#ifndef __DRONE_TEENSY_EMULATOR_H__
#define __DRONE_TEENSY_EMULATOR_H__

#include <gz/sim/System.hh>


namespace drone_gazebo_sim
{
    class TeensyEmulator
        : public gz::sim::System
        , public gz::sim::ISystemConfigure
        , public gz::sim::ISystemPreUpdate
        , public gz::sim::ISystemPostUpdate
    {
    public:
        void Configure(const gz::sim::Entity& _entity,
                        const std::shared_ptr<const sdf::Element>& _sdf,
                        gz::sim::EntityComponentManager& _ecm,
                        gz::sim::EventManager& _eventMgr) override;
        void PreUpdate(const gz::sim::UpdateInfo& _info,
                        gz::sim::EntityComponentManager& _ecm) override;
        void PostUpdate(const gz::sim::UpdateInfo& _info,
                        const gz::sim::EntityComponentManager& _ecm) override;
    private:
        gz::sim::Entity _modelEntity;
        double _myGain{1.0};
    };
}

#endif