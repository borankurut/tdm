#pragma once

#include "axis_angle.h"
#include "common_math.h"

namespace tdm
{

class ExponentialMap
{
public:
    ExponentialMap(const AxisAngle& axisAngle) : e(axisAngle.angle().valueRadians() * axisAngle.axis()) { /*empty*/ }

    friend std::ostream& operator<<(std::ostream& os, const ExponentialMap& exponentialMap)
    {
        os << exponentialMap.e;
        return os;
    }

    Vec3 getValue() const { return e; }

private:
    Vec3 e;
};

} // namespace tdm
