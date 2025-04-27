// test_vectors.cpp

#include "pch.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

const Vec2 v2a(1.0f, 2.0f);
const Vec2 v2b(3.0f, 4.0f);
const Vec3 v3a(1.0f, 2.0f, 3.0f);
const Vec3 v3b(4.0f, 5.0f, 6.0f);
const Vec4 v4a(1.0f, 2.0f, 3.0f, 4.0f);
const Vec4 v4b(5.0f, 6.0f, 7.0f, 8.0f);
const float scalar = 2.0f;

TEST_CASE("Vec2 Operations", "[Vec2]")
{
    SECTION("Basic Functionality")
    {
        Vec2 v;
        REQUIRE(v.x() == 0.0f);
        REQUIRE(v.y() == 0.0f);

        v.setX(5.0f).setY(6.0f);
        REQUIRE(v.x() == 5.0f);
        REQUIRE(v.y() == 6.0f);
    }

    SECTION("Arithmetic Operations")
    {
        SECTION("Addition")
        {
            Vec2 result = v2a + v2b;
            REQUIRE(result == Vec2(4.0f, 6.0f));
        }

        SECTION("Compound Addition")
        {
            Vec2 v = v2a;
            v += v2b;
            REQUIRE(v == Vec2(4.0f, 6.0f));
        }

        SECTION("Subtraction")
        {
            Vec2 result = v2b - v2a;
            REQUIRE(result == Vec2(2.0f, 2.0f));
        }

        SECTION("Compound Subtraction")
        {
            Vec2 v = v2b;
            v -= v2a;
            REQUIRE(v == Vec2(2.0f, 2.0f));
        }

        SECTION("Scalar Multiplication")
        {
            Vec2 result1 = v2a * scalar;
            Vec2 result2 = scalar * v2a;
            REQUIRE(result1 == Vec2(2.0f, 4.0f));
            REQUIRE(result2 == Vec2(2.0f, 4.0f));
        }

        SECTION("Component-wise Multiplication")
        {
            Vec2 result = v2a * v2b;
            REQUIRE(result == Vec2(3.0f, 8.0f));
        }

        SECTION("Division")
        {
            Vec2 result = v2b / 2.0f;
            REQUIRE(result == Vec2(1.5f, 2.0f));
        }
    }

    SECTION("Vector Operations")
    {
        SECTION("Dot Product") { REQUIRE(fEqualE6(v2a.dot(v2b), (11.0f))); }

        SECTION("Cross Product") { REQUIRE(fEqualE6(v2a.cross(v2b), (-2.0f))); }

        SECTION("Length")
        {
            REQUIRE(fEqualE6(v2a.length(), std::sqrt(5.0f)));
            REQUIRE(fEqualE6(v2a.lengthSquared(), 5.0f));
        }

        SECTION("Normalization")
        {
            Vec2 norm = v2a.normalized();
            REQUIRE(fEqualE6(norm.length(), 1.0f));
            REQUIRE(norm == v2a / v2a.length());
        }

        SECTION("Special Cases")
        {
            Vec2 zero;
            REQUIRE(zero.normalized() == zero);
            REQUIRE(zero.length() == 0.0f);
        }
    }

    SECTION("Reverse")
    {
        Vec2 v = v2a;
        v.reverse();
        REQUIRE(v == Vec2(2.0f, 1.0f));
    }
}

TEST_CASE("Vec3 Operations", "[Vec3]")
{
    SECTION("Basic Functionality")
    {
        Vec3 v;
        REQUIRE(v.x() == 0.0f);
        REQUIRE(v.y() == 0.0f);
        REQUIRE(v.z() == 0.0f);
    }

    SECTION("Vector Operations")
    {
        SECTION("Cross Product")
        {
            Vec3 cross = v3a.cross(v3b);
            REQUIRE(cross == Vec3(-3.0f, 6.0f, -3.0f));
        }

        SECTION("Normalization")
        {
            Vec3 norm = v3a.normalized();
            REQUIRE(fEqualE6(norm.length(), 1.0f));
        }
    }

    SECTION("Reverse")
    {
        Vec3 v = v3a;
        v.reverse();
        REQUIRE(v == Vec3(3.0f, 2.0f, 1.0f));
    }
}

TEST_CASE("Vec4 Operations", "[Vec4]")
{
    SECTION("Homogeneous Coordinates")
    {
        SECTION("Cartesian Conversion")
        {
            Vec4 hom(2.0f, 4.0f, 6.0f, 2.0f);
            Vec4 cart = hom.toCartesian();
            REQUIRE(cart == Vec4(1.0f, 2.0f, 3.0f, 1.0f));

            Vec4 zeroW(1.0f, 2.0f, 3.0f, 0.0f);
            REQUIRE(zeroW.toCartesian() == zeroW);
        }
    }

    SECTION("Reverse")
    {
        Vec4 v = v4a;
        v.reverse();
        REQUIRE(v == Vec4(4.0f, 3.0f, 2.0f, 1.0f));
    }

    SECTION("Normalization")
    {
        Vec4 norm = v4a.normalized();
        REQUIRE(fEqualE6(norm.length(), 1.0f));
        REQUIRE(norm == v4a / v4a.length());
    }
}

TEST_CASE("Edge Cases", "[Vector]")
{
    SECTION("Zero Vectors")
    {
        Vec2 zero2 = Vec2::Zero;
        Vec3 zero3 = Vec3::Zero;
        Vec4 zero4 = Vec4::Zero;

        REQUIRE(zero2.length() == 0.0f);
        REQUIRE(zero3.length() == 0.0f);
        REQUIRE(zero4.length() == 0.0f);

        REQUIRE(zero2.normalized() == zero2);
        REQUIRE(zero3.normalized() == zero3);
        REQUIRE(zero4.normalized() == zero4);
    }
}
