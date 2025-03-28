#pragma once

#include "common_math.h"
#include "vec2.h"

namespace tdm
{

class Polar2
{
public:
    Polar2(float radius, Radian heading) : m_radius(radius), m_heading(heading) { makeCanonical(); }

    Polar2(const Vec2& cartesian) { *this = toPolar(cartesian); }

    Vec2 toCartesian() const
    {
        float x = m_radius * cos(m_heading);
        float y = m_radius * sin(m_heading);

        return Vec2(x, y);
    }

    static Polar2 toPolar(const Vec2& cartesian)
    {
        float x = cartesian.x();
        float y = cartesian.y();
        float r = sqrt(x * x + y * y);

        if (r < EPSILON_6)
            return Polar2(0.0f, Radian(0.0f));

        Radian h = atan2(y, x);
        return Polar2(r, h);
    }

    friend std::ostream& operator<<(std::ostream& os, const Polar2& polar)
    {
        os << "[Radius: " << polar.m_radius << ", Head: " << polar.m_heading << "]";
        return os;
    }

    float r() const { return m_radius; }
    Radian h() const { return m_heading; }

private:
    float m_radius;
    Radian m_heading;

    void makeCanonical();
};

} // namespace tdm
