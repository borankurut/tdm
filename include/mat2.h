#pragma once

#include "common_math.h"
#include "vec2.h"
#include <iostream>

namespace tdm
{

class Mat2
{
public:
    Mat2() { /*empty*/ }

    explicit Mat2(const float arr[4]) { memcpy(m, arr, 4 * sizeof(float)); }

    Mat2(float m_1, float m_2, float m_3, float m_4) : m{m_1, m_2, m_3, m_4} { /*empty*/ }

    Mat2& operator=(const Mat2& other)
    {
        memcpy(m, other.m, 4 * sizeof(float));
        return *this;
    }

    // +
    const Mat2& operator+() const { return *this; }
    Mat2 operator+(const Mat2& other) const
    {
        return Mat2(m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3]);
    }
    Mat2& operator+=(const Mat2& other) { return (*this = *this + other); }

    // -
    Mat2 operator-() const { return Mat2(-m[0], -m[1], -m[2], -m[3]); }
    Mat2 operator-(const Mat2& other) const
    {
        return Mat2(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3]);
    }
    Mat2& operator-=(const Mat2& other) { return (*this = *this - other); }

    // *
    Mat2 operator*(float scalar) const { return {m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar}; }

    friend Mat2 operator*(float scalar, const Mat2& mat) { return mat * scalar; }

    Mat2 operator*(const Mat2& other) const
    {
        return Mat2(m[0] * other.m[0] + m[1] * other.m[2], m[0] * other.m[1] + m[1] * other.m[3],
                    m[2] * other.m[0] + m[3] * other.m[2], m[2] * other.m[1] + m[3] * other.m[3]);
    }

    friend Vec2 operator*(const Vec2& vec, const Mat2& mat)
    {
        return Vec2(vec.entries[0] * mat.m[0] + vec.entries[1] * mat.m[2],
                    vec.entries[0] * mat.m[1] + vec.entries[1] * mat.m[3]);
    }

    Mat2& operator*=(const Mat2& other) { return (*this = *this * other); }

    Mat2& operator*=(float scalar) { return (*this = *this * scalar); }

    // /
    Mat2 operator/(float scalar) const { return {m[0] / scalar, m[1] / scalar, m[2] / scalar, m[3] / scalar}; }

    friend Mat2 operator/(float scalar, const Mat2& mat) { return mat / scalar; }

    Mat2& operator/=(float scalar) { return (*this = *this / scalar); }

    // comparators
    bool operator==(const Mat2& other) const
    {
        return tdm::abs(m[0] - other.m[0]) < EPSILON_6 && tdm::abs(m[1] - other.m[1]) < EPSILON_6 &&
               tdm::abs(m[2] - other.m[2]) < EPSILON_6 && tdm::abs(m[3] - other.m[3]) < EPSILON_6;
    }
    bool operator!=(const Mat2& other) const { return !(*this == other); }

    // indexing
    float& operator[](int ix)
    {
        assert(ix >= 0 && ix < 4);
        return m[ix];
    }
    const float& operator[](int ix) const
    {
        assert(ix >= 0 && ix < 4);
        return m[ix];
    }

    // output stream
    friend std::ostream& operator<<(std::ostream& os, const Mat2& mat)
    {
        os << "[" << mat.m[0] << ", " << mat.m[1] << "; " << mat.m[2] << ", " << mat.m[3] << "]";
        return os;
    }

    // matrix operations
    Mat2 transpose() const { return Mat2(m[0], m[2], m[1], m[3]); }

    float determinant() const { return m[0] * m[3] - m[1] * m[2]; }

    Mat2 inverse() const
    {
        float det = determinant();
        if (tdm::abs(det - 0.0f) < EPSILON_6)
        {
            return Mat2::Zero;
        }
        else
        {
            float invDet = 1.0f / det;
            return Mat2(m[3] * invDet, -m[1] * invDet, -m[2] * invDet, m[0] * invDet);
        }
    }

    // gettters
    Vec2 getRow(int ixRow) const
    {
        assert(ixRow < 2);
        int i = 2 * ixRow;
        return Vec2(m[i], m[i + 1]);
    }

    Vec2 getColumn(int ixColumn) const
    {
        assert(ixColumn < 2);
        return Vec2(m[ixColumn], m[ixColumn + 2]);
    }

    // setters
    void setRow(int ixRow, const Vec2& vec)
    {
        assert(ixRow < 2);
        int i = 2 * ixRow;
        m[i] = vec.x();
        m[i + 1] = vec.y();
    }

    void setColumn(int ixColumn, const Vec2& vec)
    {
        assert(ixColumn < 2);
        m[ixColumn] = vec.x();
        m[ixColumn + 2] = vec.y();
    }

    // special matrices
    static Mat2 Zero;
    static Mat2 Identity;

private:
    float m[4];
    /*
     *	m[0], m[1]
     *	m[2], m[3]
     */
};

} // namespace tdm
