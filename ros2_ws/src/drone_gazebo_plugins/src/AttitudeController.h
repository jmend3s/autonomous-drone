
#ifndef __ATTITUDE_CONTROLLER_H__
#define __ATTITUDE_CONTROLLER_H__

#include <gz/math/Vector3.hh>
#include <gz/math/Vector4.hh>


class AttitudeController
{
    struct PID
    {
        double kp, ki, kd;
        double integral = 0.0;
        double lastError = 0.0;

        double update(double const error, double const dt)
        {
            integral += error * dt;
            double const derivative = (error - lastError) / dt;
            lastError = error;

            return kp * error + ki * integral + kd * derivative;
        }

        void reset()
        {
            integral = 0.0;
            lastError = 0.0;
        }
    };

public:
    AttitudeController();

    gz::math::Vector4d update(
        gz::math::Vector3d const& measuredRates,
        gz::math::Vector3d const& targetRates,
        double dt);

    void setHoverThrottle(double throttle);

private:
    double clamp(double value);

    PID _rollRate;
    PID _pitchRate;
    PID _yawRate;

    double _hoverThrottle;
};

#endif
