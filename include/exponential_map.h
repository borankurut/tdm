#pragma once

#include "axis_angle.h"
#include "common_math.h"

namespace tdm
{

class ExponentialMap
{
public:
    ExponentialMap(const AxisAngle& axisAngle) : m_e(axisAngle.angle().valueRadians() * axisAngle.axis()) { /*empty*/ }

    friend std::ostream& operator<<(std::ostream& os, const ExponentialMap& exponentialMap)
    {
        os << exponentialMap.m_e;
        return os;
    }

    Vec3 getE() const { return m_e; }

    Vec3 getAxis() const { return m_e.normalized(); }

    Radian getAngle() const { return Radian(m_e.length()); }

private:
    Vec3 m_e;
};

} // namespace tdm
