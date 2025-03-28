// test_common_math.cpp
#include "common_math.h"
#include <catch2/catch_all.hpp>

using namespace tdm;
using Catch::Approx;

TEST_CASE("Angle Conversion", "[Common]")
{
    SECTION("Radian to Degree Conversion")
    {
        Radian rad(PI);
        Degree deg(rad);
        REQUIRE(deg.valueDegrees() == Approx(180.0f));
    }

    SECTION("Degree to Radian Conversion")
    {
        Degree deg(180.0f);
        Radian rad(deg);
        REQUIRE(rad.valueRadians() == Approx(PI));
    }
}

TEST_CASE("Assignment Operators", "[Common]")
{
    SECTION("Radian Assignment from Degree")
    {
        Degree d(90.0f);
        Radian r;
        r = d;
        REQUIRE(r.valueRadians() == Approx(HALF_PI));
    }

    SECTION("Degree Assignment from Radian")
    {
        Radian r(HALF_PI);
        Degree d;
        d = r;
        REQUIRE(d.valueDegrees() == Approx(90.0f));
    }

    SECTION("Radian Assignment from Float")
    {
        Radian r;
        r = 2.5f;
        REQUIRE(r.valueRadians() == Approx(2.5f));
    }

    SECTION("Degree Assignment from Float")
    {
        Degree d;
        d = 45.0f;
        REQUIRE(d.valueDegrees() == Approx(45.0f));
    }
}

TEST_CASE("Radian Operators", "[Common]")
{
    Radian r1(2.0f);
    Radian r2(1.0f);
    Degree d(180.0f); // PI radians

    SECTION("Addition")
    {
        Radian r3 = r1 + r2;
        REQUIRE(r3.valueRadians() == Approx(3.0f));
        r3 = r1 + d;
        REQUIRE(r3.valueRadians() == Approx(2.0f + PI));
    }

    SECTION("Subtraction")
    {
        Radian r3 = r1 - r2;
        REQUIRE(r3.valueRadians() == Approx(1.0f));
        r3 = r1 - d;
        REQUIRE(r3.valueRadians() == Approx(2.0f - PI));
    }

    SECTION("Multiplication")
    {
        Radian r3 = r1 * 2.0f;
        REQUIRE(r3.valueRadians() == Approx(4.0f));
        r3 = r1 * r2;
        REQUIRE(r3.valueRadians() == Approx(2.0f));
        r3 = r1 * d; // 2.0f * PI
        REQUIRE(r3.valueRadians() == Approx(2.0f * PI));
    }

    SECTION("Division")
    {
        Radian r3 = r1 / 2.0f;
        REQUIRE(r3.valueRadians() == Approx(1.0f));
        r3 = r1 / r2;
        REQUIRE(r3.valueRadians() == Approx(2.0f));
        r3 = r1 / d; // 2.0f / PI
        REQUIRE(r3.valueRadians() == Approx(2.0f / PI));
    }

    SECTION("Compound Assignment")
    {
        r1 += r2;
        REQUIRE(r1.valueRadians() == Approx(3.0f));
        r1 -= r2;
        REQUIRE(r1.valueRadians() == Approx(2.0f));
        r1 *= 2.0f;
        REQUIRE(r1.valueRadians() == Approx(4.0f));
        r1 /= 2.0f;
        REQUIRE(r1.valueRadians() == Approx(2.0f));
    }
}

TEST_CASE("Degree Operators", "[Common]")
{
    Degree d1(90.0f);
    Degree d2(45.0f);
    Radian r(HALF_PI);

    SECTION("Addition")
    {
        Degree d3 = d1 + d2;
        REQUIRE(d3.valueDegrees() == Approx(135.0f));
        d3 = d1 + r;
        REQUIRE(d3.valueDegrees() == Approx(180.0f));
    }

    SECTION("Subtraction")
    {
        Degree d3 = d1 - d2;
        REQUIRE(d3.valueDegrees() == Approx(45.0f));
        d3 = d1 - r;
        REQUIRE(d3.valueDegrees() == Approx(0.0f));
    }

    SECTION("Compound Assignment")
    {
        d1 += d2;
        REQUIRE(d1.valueDegrees() == Approx(135.0f));
        d1 -= d2;
        REQUIRE(d1.valueDegrees() == Approx(90.0f));
        d1 *= 2.0f;
        REQUIRE(d1.valueDegrees() == Approx(180.0f));
        d1 /= 2.0f;
        REQUIRE(d1.valueDegrees() == Approx(90.0f));
    }
}

TEST_CASE("Comparison Operators", "[Common]")
{
    Radian r1(1.0f), r2(2.0f);
    Degree d1(10.0f), d2(20.0f);

    SECTION("Radian Comparisons")
    {
        REQUIRE(r1 < r2);
        REQUIRE(r2 > r1);
        REQUIRE(r1 <= r2);
        REQUIRE(r2 >= r1);
        REQUIRE(r1 != r2);
        REQUIRE(Radian(2.0f) == r2);
    }

    SECTION("Degree Comparisons")
    {
        REQUIRE(d1 < d2);
        REQUIRE(d2 > d1);
        REQUIRE(d1 <= d2);
        REQUIRE(d2 >= d1);
        REQUIRE(d1 != d2);
        REQUIRE(Degree(20.0f) == d2);
    }
}

TEST_CASE("Trigonometric Functions", "[Common]")
{
    SECTION("Sine and Cosine")
    {
        Radian zero(0.0f);
        REQUIRE(sin(zero) == Approx(0.0f));
        REQUIRE(cos(zero) == Approx(1.0f));

        Radian half_pi(HALF_PI);
        REQUIRE(sin(half_pi) == Approx(1.0f));
        REQUIRE(cos(half_pi) == Approx(0.0f).margin(EPSILON_6));
    }

    SECTION("Arcsine and Arccosine")
    {
        Radian asin_pi_half = arcsin(1.0f);
        REQUIRE(asin_pi_half.valueRadians() == Approx(HALF_PI));

        Radian acos_zero = arccos(0.0f);
        REQUIRE(acos_zero.valueRadians() == Approx(HALF_PI));
    }

    SECTION("Arctangent")
    {
        Radian atan_zero = tdm::atan(0.0f);
        REQUIRE(atan_zero.valueRadians() == Approx(0.0f));

        Radian atan2_origin = tdm::atan2(0.0f, 0.0f);
        REQUIRE(atan2_origin.valueRadians() == Approx(0.0f));
    }
}

TEST_CASE("Helper Functions", "[Common]")
{
    SECTION("Swap")
    {
        float a = 1.0f, b = 2.0f;
        swap(a, b);
        REQUIRE(a == Approx(2.0f));
        REQUIRE(b == Approx(1.0f));
    }

    SECTION("Floor and Ceil")
    {
        REQUIRE(tdm::floor(1.9f) == Approx(1.0f));
        REQUIRE(tdm::ceil(1.1f) == Approx(2.0f));
    }

    SECTION("Square Root and Absolute")
    {
        REQUIRE(tdm::sqrt(4.0f) == Approx(2.0f));
        REQUIRE(tdm::abs(-5.0f) == Approx(5.0f));
        REQUIRE(abs(Radian(-PI)) == Approx(PI));
    }
}

TEST_CASE("Edge Cases and Infinities", "[Common]")
{
    SECTION("Infinity Conversions")
    {
        Radian r_pos_inf(POS_INF);
        REQUIRE(r_pos_inf.valueRadians() == POS_INF);

        Degree d_neg_inf(NEG_INF);
        REQUIRE(d_neg_inf.valueDegrees() == NEG_INF);
    }

    SECTION("Operations with Infinity")
    {
        Radian r_inf(POS_INF);
        Radian r_finite(1.0f);
        REQUIRE((r_inf + r_finite).valueRadians() == POS_INF);
        REQUIRE((r_inf * 2.0f).valueRadians() == POS_INF);
    }
}
