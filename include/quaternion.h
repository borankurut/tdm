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
    Quaternion operator+(const Quaternion& other) const
    {
        return Quaternion(m_w + other.m_w, m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
    }

    Quaternion& operator+=(const Quaternion& other)
    {
        m_w += other.m_w;
        m_x += other.m_x;
        m_y += other.m_y;
        m_z += other.m_z;
        return *this;
    }

    // -

    // *
    Quaternion operator*(const Quaternion& other) const
    {

        return Quaternion(m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z,
                          m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y,
                          m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z,
                          m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x);
    }
    Quaternion& operator*=(const Quaternion& other)
    {

        float w = m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z;
        float x = m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y;
        float y = m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z;
        float z = m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x;
        m_w = w;
        m_x = x;
        m_y = y;
        m_z = z;
        return *this;
    }

    Quaternion operator*(float scalar) const
    {
        return Quaternion(m_w * scalar, m_x * scalar, m_y * scalar, m_z * scalar);
    }

    Quaternion& operator*=(float scalar)
    {
        m_w *= scalar;
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        return *this;
    }
    friend Quaternion operator*(float scalar, const Quaternion& quaternion)
    {
        return Quaternion(quaternion.m_w * scalar, quaternion.m_x * scalar, quaternion.m_y * scalar,
                          quaternion.m_z * scalar);
    }

    // comparators
    bool operator==(const Quaternion& other) const
    {
        return (fEqualE6(m_w, other.m_w) && fEqualE6(m_x, other.m_x) && fEqualE6(m_y, other.m_y) &&
                fEqualE6(m_z, other.m_z))

               ||

               (fEqualE6(-m_w, other.m_w) && fEqualE6(-m_x, other.m_x) && fEqualE6(-m_y, other.m_y) &&
                fEqualE6(-m_z, other.m_z));
    }
    bool operator!=(const Quaternion& other) const { return !(*this == other); }

    float dot(const Quaternion& other) const
    {
        return m_w * other.m_w + m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
    }

    // /
    Quaternion operator/(float scalar) const
    {
        assert(!fEqualE6(scalar, 0.0f));
        return Quaternion(m_w / scalar, m_x / scalar, m_y / scalar, m_z / scalar);
    }
    Quaternion& operator/=(float scalar)
    {
        assert(!fEqualE6(scalar, 0.0f));
        this->m_w /= scalar;
        this->m_x /= scalar;
        this->m_y /= scalar;
        this->m_z /= scalar;

        return *this;
    }

    float length() const { return tdm::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z); }
    float lengthSquared() const { return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z; }
    Quaternion normalized() const { return *this / length(); }

    // use conjugate instead inverse for orientation.
    Quaternion conjugate() const { return Quaternion(m_w, -m_x, -m_y, -m_z); }
    Quaternion inverse() const { return conjugate().normalized(); }

    Quaternion displacementFrom(const Quaternion& other) const { return other * this->conjugate(); }

    Quaternion pow(float exponent) const
    {
        // Assume unit quaternion
        if (abs(m_w) > (1 - EPSILON_6))
            return *this; // identity or near-zero rotation

        Radian alpha = arccos(m_w); // half angle
        Radian newAlpha = alpha * exponent;

        float sinAlpha = sin(Radian(alpha));
        float mult = sin(Radian(newAlpha)) / sinAlpha;

        return Quaternion(cos(newAlpha), Vec3(m_x, m_y, m_z) * mult);
    }

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
    {
        os << "[" << quaternion.m_w << ", (" << quaternion.m_x << ", " << quaternion.m_y << ", " << quaternion.m_z
           << ")]";
        return os;
    }
    static Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t);

    float getW() const { return m_w; }
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getZ() const { return m_z; }

    Radian getAlpha() const
    {
        float cosA = m_w;
        float sinA = Vec3(m_x, m_y, m_z).length();
        return atan2(sinA, cosA);
    }
    Radian getTheta() const { return 2.0f * getAlpha(); }

    Vec3 getAxisN() const { return Vec3(m_x, m_y, m_z).normalized(); }

    static Quaternion Identity;

private:
    float m_w;
    float m_x;
    float m_y;
    float m_z;
};

} // namespace tdm
