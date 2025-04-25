#pragma once

#include "euler.h"
#include "orientation_matrix.h"
#include "quaternion.h"

namespace tdm
{

inline Quaternion eulerToQuaternion(const Euler& euler)
{
    Radian hd2 = euler.head() / 2.0f;
    Radian pd2 = euler.pitch() / 2.0f;
    Radian bd2 = euler.bank() / 2.0f;

    float chd2 = cos(hd2), shd2 = sin(hd2), // cs head / 2
        cpd2 = cos(pd2), spd2 = sin(pd2),   // cs pitch / 2
        cbd2 = cos(bd2), sbd2 = sin(bd2);   // cs bank / 2

    return Quaternion(chd2 * cpd2 * cbd2 + shd2 * spd2 * sbd2,  // w
                      chd2 * spd2 * cbd2 + shd2 * cpd2 * sbd2,  // x
                      shd2 * cpd2 * cbd2 - chd2 * spd2 * sbd2,  // y
                      chd2 * cpd2 * sbd2 - shd2 * spd2 * cbd2); // z
}

inline Euler quaternionToEuler(const Quaternion& quaternion)
{
    // Input quaternion
    float w = quaternion.w(), x = quaternion.x(), y = quaternion.y(), z = quaternion.z();

    // Output Euler angles (radians)
    Radian h, p, b;

    // Extract sin(pitch)
    float sp = -2.0f * (y * z - w * x);

    // Check for Gimbal lock with slight tolerance for numerical imprecision
    if (fabs(sp) > 0.9999f)
    {
        // Looking straight up or down
        p = HALF_PI * sp; // pi/2

        // Compute heading, slam bank to zero
        h = atan2(-x * z + w * y, 0.5f - y * y - z * z);
        b = 0.0f;
    }
    else
    {
        // Compute angles
        p = asin(sp);
        h = atan2(x * z + w * y, 0.5f - x * x - y * y);
        b = atan2(x * y + w * z, 0.5f - x * x - z * z);
    }

    return Euler(h, p, b);
}

} // namespace tdm
