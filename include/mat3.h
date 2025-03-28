#pragma once

#include "common_math.h"
#include "vec3.h"
#include <iostream>

namespace tdm
{

class Mat3
{
public:
    Mat3() { /*empty*/ }

    explicit Mat3(const float arr[9]) { memcpy(m, arr, 9 * sizeof(float)); }

    Mat3(float m_1, float m_2, float m_3, float m_4, float m_5, float m_6, float m_7, float m_8, float m_9)
        : m{m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8, m_9}
    { /*empty*/
    }

    Mat3& operator=(const Mat3& other)
    {
        memcpy(m, other.m, 9 * sizeof(float));
        return *this;
    }

    // +
    const Mat3& operator+() const { return *this; }
    Mat3 operator+(const Mat3& other) const
    {
        return Mat3(m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3], m[4] + other.m[4],
                    m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7], m[8] + other.m[8]);
    }
    Mat3& operator+=(const Mat3& other) { return (*this = *this + other); }

    // -
    Mat3 operator-() const { return Mat3(-m[0], -m[1], -m[2], -m[3], -m[4], -m[5], -m[6], -m[7], -m[8]); }
    Mat3 operator-(const Mat3& other) const
    {
        return Mat3(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3], m[4] - other.m[4],
                    m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7], m[8] - other.m[8]);
    }
    Mat3& operator-=(const Mat3& other) { return (*this = *this - other); }

    // *
    Mat3 operator*(float scalar) const;
    friend Mat3 operator*(float scalar, const Mat3& mat) { return mat * scalar; }
    Mat3 operator*(const Mat3& other) const;
    friend Vec3 operator*(const Vec3& vec, const Mat3& mat);

    Mat3& operator*=(const Mat3& other) { return (*this = *this * other); }
    Mat3& operator*=(float scalar) { return (*this = *this * scalar); }

    // /
    Mat3 operator/(float scalar) const;
    friend Mat3 operator/(float scalar, const Mat3& mat) { return mat / scalar; }
    Mat3& operator/=(float scalar) { return (*this = *this / scalar); }

    // comparators
    bool operator==(const Mat3& other) const;
    bool operator!=(const Mat3& other) const { return !(*this == other); }

    // indexing
    float& operator[](int ix)
    {
        assert(ix >= 0 && ix < 9);
        return m[ix];
    }
    const float& operator[](int ix) const
    {
        assert(ix >= 0 && ix < 9);
        return m[ix];
    }

    // output stream
    friend std::ostream& operator<<(std::ostream& os, const Mat3& mat)
    {
        os << "[" << mat.m[0] << ", " << mat.m[1] << ", " << mat.m[2] << "; " << mat.m[3] << ", " << mat.m[4] << ", "
           << mat.m[5] << "; " << mat.m[6] << ", " << mat.m[7] << ", " << mat.m[8] << "]";
        return os;
    }

    // matrix operations
    Mat3 transpose() const { return Mat3(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]); }

    float determinant() const
    {
        return m[0] * (m[4] * m[8] - m[5] * m[7]) + m[1] * (m[5] * m[6] - m[3] * m[8]) +
               m[2] * (m[3] * m[7] - m[4] * m[6]);
    }

    Mat3 inverse() const;

    // getters
    Vec3 getRow(int ixRow) const
    {
        assert(ixRow < 3);
        int i = 3 * ixRow;
        return Vec3(m[i], m[i + 1], m[i + 2]);
    }

    Vec3 getColumn(int ixColumn) const
    {
        assert(ixColumn < 3);
        return Vec3(m[ixColumn], m[ixColumn + 3], m[ixColumn + 6]);
    }

    void setRow(int ixRow, const Vec3& vec)
    {
        assert(ixRow < 3);
        int i = 3 * ixRow;
        m[i] = vec.entries[0];
        m[i + 1] = vec.entries[1];
        m[i + 2] = vec.entries[2];
    }

    // setters
    void setColumn(int ixColumn, const Vec3& vec)
    {
        assert(ixColumn < 3);
        m[ixColumn] = vec.entries[0];
        m[ixColumn + 3] = vec.entries[1];
        m[ixColumn + 6] = vec.entries[2];
    }

    // 3D operations
    void orthogonalize()
    {
        Vec3 r0 = getRow(0);
        Vec3 r1 = getRow(1);

        r1 = r1 - (r1.dot(r0) / r0.dot(r0)) * r0;

        Vec3 r0n = r0.normalized();
        Vec3 r1n = r1.normalized();

        setRow(0, r0n);
        setRow(1, r1n);
        setRow(2, r0n.cross(r1n));
    }

    bool isOrthogonal() const;

    static Mat3 rotMatCardinalX(const Radian& r)
    {
        float s = sin(r);
        float c = cos(r);

        return Mat3(1.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f, -s, c);
    }

    static Mat3 rotMatCardinalY(const Radian& r)
    {
        float s = sin(r);
        float c = cos(r);

        return Mat3(c, 0.0f, -s, 0.0f, 1.0f, 0.0f, s, 0.0f, c);
    }

    static Mat3 rotMatCardinalZ(const Radian& r)
    {
        float s = sin(r);
        float c = cos(r);

        return Mat3(c, s, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat3 scaleCardinal(float k_x, float k_y, float k_z)
    {
        return Mat3(k_x, 0.0f, 0.0f, 0.0f, k_y, 0.0f, 0.0f, 0.0f, k_z);
    }

    static Mat3 scaleArbitrary(const Vec3& vec, float k)
    {
        float x = vec.entries[0];
        float y = vec.entries[1];
        float z = vec.entries[2];

        return Mat3(1 + (k - 1) * x * x, (k - 1) * x * y, (k - 1) * x * z, (k - 1) * x * y, 1 + (k - 1) * y * y,
                    (k - 1) * y * z, (k - 1) * x * z, (k - 1) * y * z, 1 + (k - 1) * z * z);
    }

    static Mat3 reflection(const Vec3& vec) { return scaleArbitrary(vec, -1.0f); }

    // special matrices
    static Mat3 Zero;
    static Mat3 Identity;

private:
    float m[9];
    /*
     *	m[0], m[1], m[2]
     *	m[3], m[4], m[5]
     *	m[6], m[7], m[8]
     */
};

} // namespace tdm
