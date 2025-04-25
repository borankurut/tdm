#pragma once

#include "common_math.h"
#include "vec2.h"
#include "vec3.h"
#include <iostream>

namespace tdm
{

class Vec4
{
public:
    float entries[4];

    explicit Vec4(const float arr[4]) { memcpy(entries, arr, 4 * sizeof(float)); }

    // w = 1 for homogeneous coordinates
    Vec4(float x, float y, float z, float w = 1.0f) : entries{x, y, z, w} { /*empty*/ }

    Vec4() : entries{0.0f, 0.0f, 0.0f, 1.0f} { /*empty*/ }

    Vec4(Vec3 vec, float w = 1.0f) : entries{vec.entries[0], vec.entries[1], vec.entries[2], w} { /*empty*/ }

    Vec4& operator=(const Vec2& other)
    {
        memcpy(entries, other.entries, 4 * sizeof(float));
        return *this;
    }

    // +
    const Vec4& operator+() const { return *this; }

    Vec4 operator+(const Vec4& other) const
    {
        return Vec4{entries[0] + other.entries[0], entries[1] + other.entries[1], entries[2] + other.entries[2],
                    entries[3] + other.entries[3]};
    }

    Vec4& operator+=(const Vec4& other)
    {
        entries[0] += other.entries[0];
        entries[1] += other.entries[1];
        entries[2] += other.entries[2];
        entries[3] += other.entries[3];
        return *this;
    }

    // -
    Vec4 operator-(const Vec4& other) const
    {
        return Vec4{entries[0] - other.entries[0], entries[1] - other.entries[1], entries[2] - other.entries[2],
                    entries[3] - other.entries[3]};
    }

    Vec4 operator-() const { return Vec4{-entries[0], -entries[1], -entries[2], -entries[3]}; }

    Vec4& operator-=(const Vec4& other)
    {
        entries[0] -= other.entries[0];
        entries[1] -= other.entries[1];
        entries[2] -= other.entries[2];
        entries[3] -= other.entries[3];
        return *this;
    }

    // *
    Vec4 operator*(const Vec4& other) const
    {
        return Vec4{entries[0] * other.entries[0], entries[1] * other.entries[1], entries[2] * other.entries[2],
                    entries[3] * other.entries[3]};
    }

    Vec4 operator*(float scalar) const
    {
        return Vec4{entries[0] * scalar, entries[1] * scalar, entries[2] * scalar, entries[3] * scalar};
    }

    Vec4& operator*=(float scalar)
    {
        entries[0] *= scalar;
        entries[1] *= scalar;
        entries[2] *= scalar;
        entries[3] *= scalar;
        return *this;
    }

    friend Vec4 operator*(float scalar, const Vec4& vec) { return vec * scalar; }

    // /
    Vec4 operator/(const Vec4& other) const
    {
        assert(other.entries[0] != 0.0f && other.entries[1] != 0.0f && other.entries[2] != 0.0f &&
               other.entries[3] != 0.0f);
        return Vec4{entries[0] / other.entries[0], entries[1] / other.entries[1], entries[2] / other.entries[2],
                    entries[3] / other.entries[3]};
    }

    Vec4 operator/(float scalar) const
    {
        assert(scalar != 0.0f);
        return Vec4{entries[0] / scalar, entries[1] / scalar, entries[2] / scalar, entries[3] / scalar};
    }

    Vec4& operator/=(float scalar)
    {
        assert(scalar != 0.0f);
        entries[0] /= scalar;
        entries[1] /= scalar;
        entries[2] /= scalar;
        entries[3] /= scalar;
        return *this;
    }

    friend Vec4 operator/(float scalar, const Vec4& vec) { return vec / scalar; }

    // comparators
    bool operator==(const Vec4& other) const
    {
        return fEqualE6(entries[0], other.entries[0]) && fEqualE6(entries[1], other.entries[1]) &&
               fEqualE6(entries[2], other.entries[2]) && fEqualE6(entries[3], other.entries[3]);
    }

    bool operator!=(const Vec4& other) const { return !(*this == other); }

    // vector functions
    float dot(const Vec4& other) const
    {
        return entries[0] * other.entries[0] + entries[1] * other.entries[1] + entries[2] * other.entries[2] +
               entries[3] * other.entries[3];
    }

    float length() const
    {
        return tdm::sqrt(entries[0] * entries[0] + entries[1] * entries[1] + entries[2] * entries[2] +
                         entries[3] * entries[3]);
    }

    float lengthSquared() const
    {
        return (entries[0] * entries[0] + entries[1] * entries[1] + entries[2] * entries[2] + entries[3] * entries[3]);
    }

    bool isUnit() const { return fEqualE5(lengthSquared(), 1.0f); }

    Vec4 normalized() const
    {
        float len = length();

        if (fEqualE6(len, 0.0f))
            return *this;

        return (*this) / len;
    }

    Vec4& reverse()
    {
        swap(entries[0], entries[3]);
        swap(entries[1], entries[2]);
        return *this;
    }

    Vec4 toCartesian() const
    {
        if (entries[3] != 0)
        {
            return (*this / entries[3]);
        }
        return *this;
    }

    // gettters
    float x() const { return entries[0]; }
    float y() const { return entries[1]; }
    float z() const { return entries[2]; }
    float w() const { return entries[3]; }

    // setters
    Vec4& setX(float x)
    {
        entries[0] = x;
        return *this;
    }
    Vec4& setY(float y)
    {
        entries[1] = y;
        return *this;
    }
    Vec4& setZ(float z)
    {
        entries[2] = z;
        return *this;
    }
    Vec4& setW(float w)
    {
        entries[3] = w;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec4& vec)
    {
        os << "(" << vec.entries[0] << ", " << vec.entries[1] << ", " << vec.entries[2] << ", " << vec.entries[3]
           << ")";
        return os;
    }

    static const Vec4 Zero;

    static const Vec4 Right;
    static const Vec4 Left;
    static const Vec4 Up;
    static const Vec4 Down;
    static const Vec4 Forward;
    static const Vec4 Backward;
};

} // namespace tdm
