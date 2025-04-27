#include "pch.h"

namespace tdm
{

const Quaternion Quaternion::Identity = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion Quaternion::slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
    // Compute the cosine of the angle between the quaternions
    float cosOmega = q0.dot(q1);

    // Ensure we take the shortest path by adjusting the sign of q1 if necessary
    Quaternion q1_corrected = q1;
    if (cosOmega < 0.0f)
    {
        q1_corrected = q1_corrected * -1.0f;
        cosOmega = -cosOmega;
    }

    float k0, k1;

    // Check if quaternions are very close to use linear interpolation
    if (cosOmega > (1 - EPSILON_6))
    {
        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        // Compute the angle and interpolation coefficients
        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
        Radian omega = atan2(sinOmega, cosOmega);
        float oneOverSinOmega = 1.0f / sinOmega;

        k0 = tdm::sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = tdm::sin(t * omega) * oneOverSinOmega;
    }

    // Interpolate and return the result
    return (q0 * k0) + (q1_corrected * k1);
}

} // namespace tdm
