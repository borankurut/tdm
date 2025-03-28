#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <utility>

namespace tdm
{

constexpr float EPSILON_7 = 1e-7f;
constexpr float EPSILON_6 = 1e-6f;
constexpr float EPSILON_5 = 1e-5f;
constexpr float EPSILON_4 = 1e-4f;
constexpr float EPSILON_3 = 1e-3f;

constexpr float PI = 3.14159265359f;
constexpr float HALF_PI = PI / 2.0f;
constexpr float TWO_PI = 2.0f * PI;
constexpr float POS_INF = std::numeric_limits<float>::infinity();
constexpr float NEG_INF = -std::numeric_limits<float>::infinity();

constexpr float fDegToRad = PI / 180.0f;
constexpr float fRadToDeg = 180.0f / PI;

class Degree;

class Radian
{
public:
    explicit Radian(float value = 0.0f) : m_value(value) { /*empty*/ }
    Radian(const Degree& degree);
    Radian& operator=(const float f)
    {
        m_value = f;
        return *this;
    }
    Radian& operator=(const Radian& radian)
    {
        m_value = radian.m_value;
        return *this;
    }
    Radian& operator=(const Degree& degree);

    float valueRadians() const { return m_value; }
    float valueDegrees() const { return m_value * fRadToDeg; }

    // +
    const Radian& operator+() const { return *this; }
    Radian operator+(const Radian& radian) const { return Radian(m_value + radian.m_value); }
    Radian operator+(const Degree& degree) const;
    Radian& operator+=(const Radian& radian)
    {
        m_value += radian.m_value;
        return *this;
    }
    Radian& operator+=(const Degree& degree);

    // -
    Radian operator-() const { return Radian(-m_value); }
    Radian operator-(const Radian& radian) const { return Radian(m_value - radian.m_value); }
    Radian operator-(const Degree& degree) const;
    Radian& operator-=(const Radian& radian)
    {
        m_value -= radian.m_value;
        return *this;
    }
    Radian& operator-=(const Degree& degree);

    // *
    Radian operator*(float f) const { return Radian(m_value * f); }
    Radian operator*(const Radian& radian) const { return Radian(m_value * radian.m_value); }
    Radian operator*(const Degree& degree) const;
    Radian& operator*=(float f)
    {
        m_value *= f;
        return *this;
    }
    Radian& operator*=(const Radian& radian)
    {
        m_value *= radian.m_value;
        return *this;
    }
    Radian& operator*=(const Degree& degree);

    // /
    Radian operator/(float f) const { return Radian(m_value / f); }
    Radian operator/(const Radian& radian) const { return Radian(m_value / radian.m_value); }
    Radian operator/(const Degree& degree) const;
    Radian& operator/=(float f)
    {
        m_value /= f;
        return *this;
    }
    Radian& operator/=(const Radian& radian)
    {
        m_value *= radian.m_value;
        return *this;
    }
    Radian& operator/=(const Degree& degree);

    // comparators
    bool operator<(const Radian& radian) const { return m_value < radian.m_value; }
    bool operator<=(const Radian& radian) const { return m_value <= radian.m_value; }
    bool operator==(const Radian& radian) const { return m_value == radian.m_value; }
    bool operator!=(const Radian& radian) const { return m_value != radian.m_value; }
    bool operator>=(const Radian& radian) const { return m_value >= radian.m_value; }
    bool operator>(const Radian& radian) const { return m_value > radian.m_value; }

    friend std::ostream& operator<<(std::ostream& os, const Radian& radian)
    {
        os << "Radian:" << radian.valueRadians();
        return os;
    }

private:
    float m_value;
};

class Degree
{
public:
    explicit Degree(float value = 0.0f) : m_value(value) { /*empty*/ }
    Degree(const Radian& radian);
    Degree& operator=(const float f)
    {
        m_value = f;
        return *this;
    }
    Degree& operator=(const Degree& degree)
    {
        m_value = degree.m_value;
        return *this;
    }
    Degree& operator=(const Radian& radian);

    float valueRadians() const { return m_value * fDegToRad; }
    float valueDegrees() const { return m_value; }

    // +
    const Degree& operator+() const { return *this; }
    Degree operator+(const Degree& degree) const { return Degree(m_value + degree.m_value); }
    Degree operator+(const Radian& radian) const;
    Degree& operator+=(const Degree& degree)
    {
        m_value += degree.m_value;
        return *this;
    }
    Degree& operator+=(const Radian& radian);

    // -
    Degree operator-() const { return Degree(-m_value); }
    Degree operator-(const Degree& degree) const { return Degree(m_value - degree.m_value); }
    Degree operator-(const Radian& radian) const;
    Degree& operator-=(const Degree& degree)
    {
        m_value -= degree.m_value;
        return *this;
    }
    Degree& operator-=(const Radian& radian);

    // *
    Degree operator*(float f) const { return Degree(m_value * f); }
    Degree& operator*=(float f)
    {
        m_value *= f;
        return *this;
    }

    // /
    Degree operator/(float f) const { return Degree(m_value / f); }
    Degree& operator/=(float f)
    {
        m_value /= f;
        return *this;
    }

    // comparators
    bool operator<(const Degree& degree) const { return m_value < degree.m_value; }
    bool operator<=(const Degree& degree) const { return m_value <= degree.m_value; }
    bool operator==(const Degree& degree) const { return m_value == degree.m_value; }
    bool operator!=(const Degree& degree) const { return m_value != degree.m_value; }
    bool operator>=(const Degree& degree) const { return m_value >= degree.m_value; }
    bool operator>(const Degree& degree) const { return m_value > degree.m_value; }

    friend std::ostream& operator<<(std::ostream& os, const Degree& degree)
    {
        os << "Degree:" << degree.valueDegrees();
        return os;
    }

private:
    float m_value;
};

// radian functions
inline Radian::Radian(const Degree& degree) : m_value(degree.valueRadians()) { /*empty*/ }

inline Radian& Radian::operator=(const Degree& degree)
{
    m_value = degree.valueRadians();
    return *this;
}

inline Radian Radian::operator+(const Degree& degree) const { return Radian(m_value + degree.valueRadians()); }
inline Radian& Radian::operator+=(const Degree& degree)
{
    m_value += degree.valueRadians();
    return *this;
}

inline Radian Radian::operator-(const Degree& degree) const { return Radian(m_value - degree.valueRadians()); }
inline Radian& Radian::operator-=(const Degree& degree)
{
    m_value -= degree.valueRadians();
    return *this;
}

inline Radian Radian::operator*(const Degree& degree) const { return Radian(m_value * degree.valueRadians()); }
inline Radian& Radian::operator*=(const Degree& degree)
{
    m_value *= degree.valueRadians();
    return *this;
}

inline Radian Radian::operator/(const Degree& degree) const { return Radian(m_value / degree.valueRadians()); }
inline Radian& Radian::operator/=(const Degree& degree)
{
    m_value /= degree.valueRadians();
    return *this;
}

// degree functions
inline Degree::Degree(const Radian& radian) : m_value(radian.valueDegrees()) { /*empty*/ }

inline Degree& Degree::operator=(const Radian& radian)
{
    m_value = radian.valueDegrees();
    return *this;
}

inline Degree Degree::operator+(const Radian& radian) const { return Degree(m_value + radian.valueDegrees()); }
inline Degree& Degree::operator+=(const Radian& radian)
{
    m_value += radian.valueDegrees();
    return *this;
}

inline Degree Degree::operator-(const Radian& radian) const { return Degree(m_value - radian.valueDegrees()); }
inline Degree& Degree::operator-=(const Radian& radian)
{
    m_value -= radian.valueDegrees();
    return *this;
}

inline void swap(float& a, float& b) { std::swap(a, b); }

inline float floor(float x) { return std::floor(x); }

inline float ceil(float x) { return std::ceil(x); }

inline float sqrt(float n) { return std::sqrt(n); }

inline float abs(float n) { return std::fabs(n); }

inline float abs(Radian radian) { return abs(radian.valueRadians()); }

inline float sin(Radian r) { return std::sin(r.valueRadians()); }

inline Radian arcsin(float x) { return Radian(std::asin(x)); }

inline float cos(Radian r) { return std::cos(r.valueRadians()); }

inline Radian arccos(float x) { return Radian(std::acos(x)); }

inline float tan(Radian r) { return std::tan(r.valueRadians()); }

inline Radian atan(float x) { return Radian(std::atan(x)); }

inline Radian atan2(float y, float x)
{
    if (x == 0 && y == 0)
        return Radian(0.0f);
    else
        return Radian(std::atan2(y, x));
}

inline float wrapPi(float theta)
{
    theta = theta - TWO_PI * tdm::floor((theta + PI) / TWO_PI);
    return theta;
}

inline Radian wrapPi(Radian theta) { return Radian(wrapPi(theta.valueRadians())); }

} // namespace tdm
