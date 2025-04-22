#pragma once

#include "common_math.h"
#include <iostream>

namespace tdm
{
class Vec3;
class Vec4;

class Vec2
{
public:
    float entries[2];

    explicit Vec2(const float arr[2]) { memcpy(entries, arr, 2 * sizeof(float)); }

    Vec2(float x, float y) : entries{x, y} { /*empty*/ }

    Vec2() : entries{0.0f, 0.0f} { /*empty*/ }

    Vec2& operator=(const Vec2& other)
    {
        memcpy(entries, other.entries, 2 * sizeof(float));
        return *this;
    }

    // +
    const Vec2& operator+() const { return *this; }

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2{entries[0] + other.entries[0], entries[1] + other.entries[1]};
    }

    Vec2& operator+=(const Vec2& other)
    {
        entries[0] += other.entries[0];
        entries[1] += other.entries[1];
        return *this;
    }

    // -
    Vec2 operator-(const Vec2& other) const
    {
        return Vec2{entries[0] - other.entries[0], entries[1] - other.entries[1]};
    }

    Vec2 operator-() const { return Vec2{-entries[0], -entries[1]}; }

    Vec2& operator-=(const Vec2& other)
    {
        entries[0] -= other.entries[0];
        entries[1] -= other.entries[1];
        return *this;
    }

    // *
    Vec2 operator*(const Vec2& other) const
    {
        return Vec2{entries[0] * other.entries[0], entries[1] * other.entries[1]};
    }

    Vec2 operator*(float scalar) const { return Vec2{entries[0] * scalar, entries[1] * scalar}; }

    Vec2& operator*=(float scalar)
    {
        entries[0] *= scalar;
        entries[1] *= scalar;
        return *this;
    }

    friend Vec2 operator*(float scalar, const Vec2& vec) { return vec * scalar; }

    // /
    Vec2 operator/(const Vec2& other) const
    {
        assert(other.entries[0] != 0.0f && other.entries[1] != 0.0f);
        return Vec2{entries[0] / other.entries[0], entries[1] / other.entries[1]};
    }

    Vec2 operator/(float scalar) const
    {
        assert(scalar != 0.0f);
        return Vec2{entries[0] / scalar, entries[1] / scalar};
    }

    Vec2& operator/=(float scalar)
    {
        assert(scalar != 0.0f);
        entries[0] /= scalar;
        entries[1] /= scalar;
        return *this;
    }

    friend Vec2 operator/(float scalar, const Vec2& vec) { return vec / scalar; }

    // comparators
    bool operator==(const Vec2& other) const
    {
        return fEqualE6(entries[0], other.entries[0]) && fEqualE6(entries[1], other.entries[1]);
    }

    bool operator!=(const Vec2& other) const { return !(*this == other); }

    // vector functions
    float dot(const Vec2& other) const { return entries[0] * other.entries[0] + entries[1] * other.entries[1]; }

    float cross(const Vec2& other) const { return (entries[0] * other.entries[1]) - (entries[1] * other.entries[0]); }

    float length() const { return tdm::sqrt(entries[0] * entries[0] + entries[1] * entries[1]); }

    float lengthSquared() const { return (entries[0] * entries[0] + entries[1] * entries[1]); }

    bool isUnit() const { return fEqualE5(lengthSquared(), 1.0f); }

    Vec2 normalized() const
    {
        float len = length();

        if (fEqualE6(len, 0.0f))
            return *this;

        return (*this / len);
    }

    Vec2& reverse()
    {
        swap(entries[0], entries[1]);
        return *this;
    }

    // getters
    float x() const { return entries[0]; }
    float y() const { return entries[1]; }

    // setters
    Vec2& setX(float x)
    {
        entries[0] = x;
        return *this;
    }
    Vec2& setY(float y)
    {
        entries[1] = y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
    {
        os << "(" << vec.entries[0] << ", " << vec.entries[1] << ")";
        return os;
    }

    static Vec2 Zero;
    static Vec2 Right;
    static Vec2 Left;
    static Vec2 Up;
    static Vec2 Down;
};

} // namespace tdm
