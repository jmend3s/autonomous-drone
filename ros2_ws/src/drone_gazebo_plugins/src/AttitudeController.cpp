
#include "AttitudeController.h"


AttitudeController::AttitudeController()
    : _rollRate({ 0.08, 0.001, 0.002 })
    , _pitchRate({ 0.08, 0.001, 0.002 })
    , _yawRate({ 0.05, 0.001, 0.001 })
    , _hoverThrottle(0.5)
{
}

gz::math::Vector4d AttitudeController::update(
    gz::math::Vector3d const& measuredRates,
    gz::math::Vector3d const& targetRates,
    double const dt)
{
    double const rollError = targetRates.X() - measuredRates.X();
    double const pitchError = targetRates.Y() - measuredRates.Y();
    double const yawError = targetRates.Z() - measuredRates.Z();

    double const rollCommand = _rollRate.update(rollError, dt);
    double const pitchCommand = _pitchRate.update(pitchError, dt);
    double const yawCommand = _yawRate.update(yawError, dt);

    double motorA = _hoverThrottle + rollCommand - pitchCommand + yawCommand;
    double motorB = _hoverThrottle - rollCommand - pitchCommand - yawCommand;
    double motorC = _hoverThrottle - rollCommand + pitchCommand + yawCommand;
    double motorD = _hoverThrottle + rollCommand + pitchCommand - yawCommand;

    motorA = clamp(motorA);
    motorB = clamp(motorB);
    motorC = clamp(motorC);
    motorD = clamp(motorD);

    return { motorA, motorB, motorC, motorD };
}

void AttitudeController::setHoverThrottle(double const throttle)
{
    _hoverThrottle = throttle;
}

double AttitudeController::clamp(double const value) const
{
    return std::clamp(value, 0.0, 1.0);
}
