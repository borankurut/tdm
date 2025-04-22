#pragma once
#include "common_math.h"
#include "vec3.h"
#include <iostream>

namespace tdm
{

class AxisAngle
{
public:
    AxisAngle(const Vec3& axis, const Radian& angle)
    {
        m_axis = axis.normalized();
        m_angle = wrapPi(angle);
    }

    friend std::ostream& operator<<(std::ostream& os, const AxisAngle& axisAngle)
    {
        os << "[Axis: " << axisAngle.m_axis << ", Angle: " << axisAngle.m_angle << "]";
        return os;
    }

    const Vec3& axis() const { return m_axis; }
    const Radian& angle() const { return m_angle; }

private:
    Vec3 m_axis;
    Radian m_angle;
};

} // namespace tdm
