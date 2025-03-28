#pragma once

#include "common_math.h"
#include "vec3.h"

namespace tdm
{

class Polar3
{
public:
    Polar3(float radius, Radian heading, Radian pitch) : m_radius(radius), m_heading(heading), m_pitch(pitch)
    {
        makeCanonical();
    }

    Polar3(const Vec3& cartesian) { *this = toPolar(cartesian); }

    Vec3 toCartesian() const
    {
        float x = m_radius * cos(m_pitch) * sin(m_heading);
        float y = -m_radius * sin(m_pitch);
        float z = m_radius * cos(m_pitch) * cos(m_heading);

        return Vec3(x, y, z);
    }

    static Polar3 toPolar(const Vec3& cartesian)
    {
        float x = cartesian.x();
        float y = cartesian.y();
        float z = cartesian.z();

        float r = sqrt(x * x + y * y + z * z);

        if (r < EPSILON_6)
            return Polar3(0.0f, Radian(0.0f), Radian(0.0f));

        Radian h = atan2(x, z);
        Radian p = arcsin(-y / r);
        return Polar3(r, h, p);
    }

    friend std::ostream& operator<<(std::ostream& os, const Polar3& polar)
    {
        os << "[Radius: " << polar.m_radius << ", Head: " << polar.m_heading << ", Pitch: " << polar.m_pitch << "]";
        return os;
    }

    float r() const { return m_radius; }
    Radian h() const { return m_heading; }
    Radian p() const { return m_pitch; }

private:
    float m_radius;
    Radian m_heading;
    Radian m_pitch;

    void makeCanonical();
};

} // namespace tdm
