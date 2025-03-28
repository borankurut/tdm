#pragma once

#include "axis_angle.h"

namespace tdm
{

class Quaternion
{
public:
    Quaternion() { /*empty*/ }

    Quaternion(float w, float x, float y, float z) : m_w(w), m_x(x), m_y(y), m_z(z) { /*empty*/ }

    Quaternion(float w, const Vec3& v) : m_w(w), m_x(v.entries[0]), m_y(v.entries[1]), m_z(v.entries[2]) { /*empty*/ }

    explicit Quaternion(AxisAngle axisAngle)
    {
        Radian halfTheta = axisAngle.angle() / 2.0f;

        float c = tdm::cos(halfTheta);
        float s = tdm::sin(halfTheta);
        Vec3 axis_mult_s = axisAngle.axis() * s;

        m_w = c;
        m_x = axis_mult_s.entries[0];
        m_y = axis_mult_s.entries[1];
        m_z = axis_mult_s.entries[2];
    }

    // +

    // -

    // *
    Quaternion operator*(const Quaternion& other)
    {

        return Quaternion(m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z,
                          m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y,
                          m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z,
                          m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x);
    }

    float dot(const Quaternion& other) { return m_w * other.m_w + m_x * other.m_x + m_y * other.m_y + m_z * other.m_z; }

    // /
    Quaternion operator/(float scalar) const
    {
        return Quaternion(m_w / scalar, m_x / scalar, m_y / scalar, m_z / scalar);
    }
    Quaternion& operator/=(float scalar)
    {
        this->m_w /= scalar;
        this->m_x /= scalar;
        this->m_y /= scalar;
        this->m_z /= scalar;

        return *this;
    }

    float length() { return tdm::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z); }
    float lengthSquared() { return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z; }
    Quaternion normalized() { return *this / length(); }

    Quaternion conjugate() { return Quaternion(m_w, -m_x, -m_y, -m_z); }
    Quaternion inverse() { return conjugate().normalized(); }

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
    {
        os << "[" << quaternion.m_w << ", (" << quaternion.m_x << ", " << quaternion.m_y << ", " << quaternion.m_z
           << ")]";
        return os;
    }

    float getW() const { return m_w; }
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getZ() const { return m_z; }

    static Quaternion Identity;

private:
    float m_w;
    float m_x;
    float m_y;
    float m_z;
};

} // namespace tdm
