// test_quaternion.cpp
#include "axis_angle.h"
#include "common_math.h"
#include "quaternion.h"
#include "vec3.h"
#include <catch2/catch_test_macros.hpp>

using namespace tdm;

TEST_CASE("Quaternion Constructors", "[Quaternion]")
{
    SECTION("w,x,y,z constructor")
    {
        Quaternion q(1, 2, 3, 4);
        REQUIRE(q.w() == 1.0f);
        REQUIRE(q.x() == 2.0f);
        REQUIRE(q.y() == 3.0f);
        REQUIRE(q.z() == 4.0f);
    }

    SECTION("w, Vec3 constructor")
    {
        Vec3 v(2, 3, 4);
        Quaternion q(1, v);
        REQUIRE(q.w() == 1.0f);
        REQUIRE(q.x() == 2.0f);
        REQUIRE(q.y() == 3.0f);
        REQUIRE(q.z() == 4.0f);
    }

    SECTION("AxisAngle constructor")
    {
        Vec3 axis(0, 0, 1);
        AxisAngle aa(axis, Degree(90.0f));
        Quaternion q(aa);
        // half‑angle = 45°, so w = cos45°, xyz = axis*sin45°
        float c = cos(Degree(45.0f));
        float s = sin(Degree(45.0f));
        REQUIRE(fEqualE6(q.w(), c));
        REQUIRE(fEqualE6(q.x(), 0.0f));
        REQUIRE(fEqualE6(q.y(), 0.0f));
        REQUIRE(fEqualE6(q.z(), s));
    }
}

TEST_CASE("Quaternion Arithmetic", "[Quaternion]")
{
    Quaternion a(1, 2, 3, 4);
    Quaternion b(5, 6, 7, 8);

    SECTION("Addition")
    {
        auto c = a + b;
        REQUIRE(c.w() == 6.0f);
        REQUIRE(c.x() == 8.0f);
        REQUIRE(c.y() == 10.0f);
        REQUIRE(c.z() == 12.0f);
        a += b;
        REQUIRE(a == c);
    }

    SECTION("Multiplication")
    {
        // Check identity * b == b
        Quaternion I = Quaternion::Identity;
        REQUIRE((I * b) == b);
        REQUIRE((b * I) == b);

        // Compare against known product
        Quaternion prod = a * b;
        Quaternion manual(1 * 5 - 2 * 6 - 3 * 7 - 4 * 8, 1 * 6 + 2 * 5 + 3 * 8 - 4 * 7, 1 * 7 + 3 * 5 + 4 * 6 - 2 * 8,
                          1 * 8 + 4 * 5 + 2 * 7 - 3 * 6);
        REQUIRE(prod == manual);

        // compound
        Quaternion c = a;
        c *= b;
        REQUIRE(c == prod);
    }

    SECTION("Scalar multiply/divide")
    {
        auto m = a * 2.0f;
        REQUIRE(m.w() == 2.0f);
        REQUIRE(m.x() == 4.0f);
        REQUIRE(m == 2.0f * a);

        auto d = a / 2.0f;
        REQUIRE(d.w() == 0.5f);
        REQUIRE(d.x() == 1.0f);
        REQUIRE(fEqualE6((d * 2.0f).y(), a.y()));
        a /= 2.0f;
        REQUIRE(fEqualE6(a.w(), 0.5f));
    }

    SECTION("Dot product") { REQUIRE(a.dot(b) == (1 * 5 + 2 * 6 + 3 * 7 + 4 * 8)); }
}

TEST_CASE("Quaternion Norm, Conjugate, Inverse", "[Quaternion]")
{
    Quaternion q(1, 2, 3, 4);
    float len = tdm::sqrt(1 + 4 + 9 + 16);
    REQUIRE(fEqualE6(q.length(), len));
    REQUIRE(fEqualE5(q.lengthSquared(), (len * len)));

    Quaternion qn = q.normalized();
    REQUIRE(fEqualE6(qn.length(), 1.0f));

    Quaternion qc = q.conjugate();
    REQUIRE(qc.w() == 1.0f);
    REQUIRE(qc.x() == -2.0f);
    REQUIRE(qc.y() == -3.0f);
    REQUIRE(qc.z() == -4.0f);

    Quaternion qni = qn.inverse();
    REQUIRE(qn * qni == Quaternion::Identity);
}

TEST_CASE("Quaternion Pow & SLERP", "[Quaternion]")
{
    // unit quaternion: 90deg around Z
    AxisAngle aaZ(Vec3(0, 0, 1), Degree(90.0f));
    Quaternion q(aaZ);

    SECTION("Pow: double angle")
    {
        Quaternion q2 = q.pow(2.0f);
        // should be 180deg around Z
        AxisAngle aa180(Vec3(0, 0, 1), Degree(180.0f));
        Quaternion expected(aa180);
        REQUIRE(q2 == expected);
    }

    SECTION("SLERP halfway")
    {
        Quaternion I = Quaternion::Identity;
        Quaternion mid = Quaternion::slerp(I, q, 0.5f);
        // halfway between 0° and 90° → 45°
        AxisAngle aa45(Vec3(0, 0, 1), Degree(45.0f));
        Quaternion exp45(aa45);
        REQUIRE(mid == exp45);
    }
}

TEST_CASE("Quaternion Axis & Angle Accessors", "[Quaternion]")
{
    AxisAngle aa(Vec3(1, 0, 0), Degree(60.0f));
    Quaternion q(aa);

    Radian alpha = q.alpha();
    Radian targetAlpha = Radian(60.0f * 0.5f * (PI / 180.0f)); // half‑angle in rad
    REQUIRE(fEqualE6(alpha.valueRadians(), targetAlpha.valueRadians()));

    Radian theta = q.theta();
    REQUIRE(fEqualE6(theta.valueRadians(), Radian(Degree(60.0f)).valueRadians()));

    Vec3 axis = q.axisN();
    REQUIRE(fEqualE6(axis.entries[0], 1.0f));
    REQUIRE(fEqualE6(axis.entries[1], 0.0f));
    REQUIRE(fEqualE6(axis.entries[2], 0.0f));
}
