#pragma once

#include "common_math.h"
#include "vec2.h"
#include <iostream>

namespace tdm
{
class Vec4;

class Vec3
{
public:
    float entries[3];

    explicit Vec3(const float arr[3]) { memcpy(entries, arr, 3 * sizeof(float)); }

    Vec3(float x, float y, float z) : entries{x, y, z} { /*empty*/ }

    Vec3() : entries{0.0f, 0.0f, 0.0f} { /*empty*/ }

    Vec3& operator=(const Vec2& other)
    {
        memcpy(entries, other.entries, 3 * sizeof(float));
        return *this;
    }

    // +
    const Vec3& operator+() const { return *this; }
    Vec3 operator+(const Vec3& other) const
    {
        return Vec3{entries[0] + other.entries[0], entries[1] + other.entries[1], entries[2] + other.entries[2]};
    }

    Vec3& operator+=(const Vec3& other)
    {
        entries[0] += other.entries[0];
        entries[1] += other.entries[1];
        entries[2] += other.entries[2];
        return *this;
    }

    // -
    Vec3 operator-(const Vec3& other) const
    {
        return Vec3{entries[0] - other.entries[0], entries[1] - other.entries[1], entries[2] - other.entries[2]};
    }

    Vec3 operator-() const { return Vec3{-entries[0], -entries[1], -entries[2]}; }

    Vec3& operator-=(const Vec3& other)
    {
        entries[0] -= other.entries[0];
        entries[1] -= other.entries[1];
        entries[2] -= other.entries[2];
        return *this;
    }

    // *
    friend Vec3 operator*(float scalar, const Vec3& vec) { return vec * scalar; }

    Vec3 operator*(const Vec3& other) const
    {
        return Vec3{entries[0] * other.entries[0], entries[1] * other.entries[1], entries[2] * other.entries[2]};
    }

    Vec3 operator*(float scalar) const { return Vec3{entries[0] * scalar, entries[1] * scalar, entries[2] * scalar}; }

    Vec3& operator*=(float scalar)
    {
        entries[0] *= scalar;
        entries[1] *= scalar;
        entries[2] *= scalar;
        return *this;
    }

    // /
    friend Vec3 operator/(float scalar, const Vec3& vec) { return vec / scalar; }

    Vec3 operator/(const Vec3& other) const
    {
        assert(other.entries[0] != 0.0f && other.entries[1] != 0.0f);
        return Vec3{entries[0] / other.entries[0], entries[1] / other.entries[1], entries[2] / other.entries[2]};
    }

    Vec3 operator/(float scalar) const
    {
        assert(scalar != 0.0f);
        return Vec3{entries[0] / scalar, entries[1] / scalar, entries[2] / scalar};
    }

    Vec3& operator/=(float scalar)
    {
        assert(scalar != 0.0f);
        entries[0] /= scalar;
        entries[1] /= scalar;
        entries[2] /= scalar;
        return *this;
    }

    // comparators
    bool operator==(const Vec3& other) const
    {

        return fEqualE6(entries[0], other.entries[0]) && fEqualE6(entries[1], other.entries[1]) &&
               fEqualE6(entries[2], other.entries[2]);
    }

    bool operator!=(const Vec3& other) const { return !(*this == other); }

    // vector functions
    float dot(const Vec3& other) const
    {
        return entries[0] * other.entries[0] + entries[1] * other.entries[1] + entries[2] * other.entries[2];
    }

    Vec3 cross(const Vec3& other) const
    {
        return Vec3{entries[1] * other.entries[2] - entries[2] * other.entries[1],
                    entries[2] * other.entries[0] - entries[0] * other.entries[2],
                    entries[0] * other.entries[1] - entries[1] * other.entries[0]};
    }

    float length() const
    {
        return tdm::sqrt(entries[0] * entries[0] + entries[1] * entries[1] + entries[2] * entries[2]);
    }

    float lengthSquared() const
    {
        return (entries[0] * entries[0] + entries[1] * entries[1] + entries[2] * entries[2]);
    }

    bool isUnit() const { return fEqualE5(lengthSquared(), 1.0f); }

    Vec3 normalized() const
    {
        float len = length();

        if (fEqualE6(len, 0.0f))
            return *this;

        return (*this / len);
    }

    Vec3& reverse()
    {
        swap(entries[0], entries[2]);
        return *this;
    }

    // getters
    float x() const { return entries[0]; }
    float y() const { return entries[1]; }
    float z() const { return entries[2]; }

    // setters
    Vec3& setX(float x)
    {
        entries[0] = x;
        return *this;
    }
    Vec3& setY(float y)
    {
        entries[1] = y;
        return *this;
    }
    Vec3& setZ(float z)
    {
        entries[2] = z;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec)
    {
        os << "(" << vec.entries[0] << ", " << vec.entries[1] << ", " << vec.entries[2] << ")";
        return os;
    }

    static const Vec3 Zero;

    static const Vec3 Right;
    static const Vec3 Left;
    static const Vec3 Up;
    static const Vec3 Down;
    static const Vec3 Forward;
    static const Vec3 Backward;
};

} // namespace tdm
