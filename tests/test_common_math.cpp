// test_common_math.cpp

#include "pch.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Equality Checks", "[Common]")
{
    SECTION("Equality Checks with Floats")
    {
        float base = 1.0f;

        REQUIRE(fEqualE3(base, base + EPSILON_3 * 0.9f));
        REQUIRE_FALSE(fEqualE3(base, base + EPSILON_3 * 1.1f));

        REQUIRE(fEqualE4(base, base + EPSILON_4 * 0.9f));
        REQUIRE_FALSE(fEqualE4(base, base + EPSILON_4 * 1.1f));

        REQUIRE(fEqualE5(base, base + EPSILON_5 * 0.9f));
        REQUIRE_FALSE(fEqualE5(base, base + EPSILON_5 * 1.1f));

        REQUIRE(fEqualE6(base, base + EPSILON_6 * 0.9f));
        REQUIRE_FALSE(fEqualE6(base, base + EPSILON_6 * 1.1f));

        /* REQUIRE(fEqualE7(base, base + EPSILON_7 * 0.9f)); */
        /* REQUIRE_FALSE(fEqualE7(base, base + EPSILON_7 * 1.1f)); */
    }

    SECTION("Equality Checks with Radians")
    {
        Radian base{1.0f};

        REQUIRE(rEqualE3(base, Radian{base.valueRadians() + EPSILON_3 * 0.9f}));
        REQUIRE_FALSE(rEqualE3(base, Radian{base.valueRadians() + EPSILON_3 * 1.1f}));

        REQUIRE(rEqualE4(base, Radian{base.valueRadians() + EPSILON_4 * 0.9f}));
        REQUIRE_FALSE(rEqualE4(base, Radian{base.valueRadians() + EPSILON_4 * 1.1f}));

        REQUIRE(rEqualE5(base, Radian{base.valueRadians() + EPSILON_5 * 0.9f}));
        REQUIRE_FALSE(rEqualE5(base, Radian{base.valueRadians() + EPSILON_5 * 1.1f}));

        REQUIRE(rEqualE6(base, Radian{base.valueRadians() + EPSILON_6 * 0.9f}));
        REQUIRE_FALSE(rEqualE6(base, Radian{base.valueRadians() + EPSILON_6 * 1.1f}));

        /* REQUIRE(rEqualE7(base, Radian{base.valueRadians() + EPSILON_7 * 0.9f})); */
        /* REQUIRE_FALSE(rEqualE7(base, Radian{base.valueRadians() + EPSILON_7 * 1.1f})); */
    }
}

TEST_CASE("Angle Conversion", "[Common]")
{
    SECTION("Radian to Degree Conversion")
    {
        Radian rad(PI);
        Degree deg(rad);
        REQUIRE(fEqualE6(deg.valueDegrees(), 180.0f));
    }

    SECTION("Degree to Radian Conversion")
    {
        Degree deg(180.0f);
        Radian rad(deg);
        REQUIRE(fEqualE6(rad.valueRadians(), PI));
    }
}

TEST_CASE("Assignment Operators", "[Common]")
{
    SECTION("Radian Assignment from Degree")
    {
        Degree d(90.0f);
        Radian r;
        r = d;

        REQUIRE(fEqualE6(r.valueRadians(), HALF_PI));
    }

    SECTION("Degree Assignment from Radian")
    {
        Radian r(HALF_PI);
        Degree d;
        d = r;
        REQUIRE(fEqualE6(d.valueDegrees(), 90.0f));
    }

    SECTION("Radian Assignment from Float")
    {
        Radian r;
        r = 2.5f;
        REQUIRE(fEqualE6(r.valueRadians(), 2.5f));
    }

    SECTION("Degree Assignment from Float")
    {
        Degree d;
        d = 45.0f;
        REQUIRE(fEqualE6(d.valueDegrees(), 45.0f));
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
        REQUIRE(fEqualE6(r3.valueRadians(), 3.0f));
        r3 = r1 + d;
        REQUIRE(fEqualE6(r3.valueRadians(), (2.0f + PI)));
    }

    SECTION("Subtraction")
    {
        Radian r3 = r1 - r2;
        REQUIRE(fEqualE6(r3.valueRadians(), 1.0f));
        r3 = r1 - d;
        REQUIRE(fEqualE6(r3.valueRadians(), (2.0f - PI)));
    }

    SECTION("Multiplication")
    {
        Radian r3 = r1 * 2.0f;
        REQUIRE(fEqualE6(r3.valueRadians(), 4.0f));
        r3 = r1 * r2;
        REQUIRE(fEqualE6(r3.valueRadians(), 2.0f));
        r3 = r1 * d; // 2.0f * PI
        REQUIRE(fEqualE6(r3.valueRadians(), (2.0f * PI)));
    }

    SECTION("Division")
    {
        Radian r3 = r1 / 2.0f;
        REQUIRE(fEqualE6(r3.valueRadians(), 1.0f));
        r3 = r1 / r2;
        REQUIRE(fEqualE6(r3.valueRadians(), 2.0f));
        r3 = r1 / d; // 2.0f / PI
        REQUIRE(fEqualE6(r3.valueRadians(), (2.0f / PI)));
    }

    SECTION("Compound Assignment")
    {
        r1 += r2;
        REQUIRE(fEqualE6(r1.valueRadians(), 3.0f));
        r1 -= r2;
        REQUIRE(fEqualE6(r1.valueRadians(), 2.0f));
        r1 *= 2.0f;
        REQUIRE(fEqualE6(r1.valueRadians(), 4.0f));
        r1 /= 2.0f;
        REQUIRE(fEqualE6(r1.valueRadians(), 2.0f));
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
        REQUIRE(fEqualE6(d3.valueDegrees(), 135.0f));
        d3 = d1 + r;
        REQUIRE(fEqualE6(d3.valueDegrees(), 180.0f));
    }

    SECTION("Subtraction")
    {
        Degree d3 = d1 - d2;
        REQUIRE(fEqualE6(d3.valueDegrees(), 45.0f));
        d3 = d1 - r;
        REQUIRE(fEqualE6(d3.valueDegrees(), 0.0f));
    }

    SECTION("Compound Assignment")
    {
        d1 += d2;
        REQUIRE(fEqualE6(d1.valueDegrees(), 135.0f));
        d1 -= d2;
        REQUIRE(fEqualE6(d1.valueDegrees(), 90.0f));
        d1 *= 2.0f;
        REQUIRE(fEqualE6(d1.valueDegrees(), 180.0f));
        d1 /= 2.0f;
        REQUIRE(fEqualE6(d1.valueDegrees(), 90.0f));
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
        REQUIRE(fEqualE6(sin(zero), 0.0f));
        REQUIRE(fEqualE6(cos(zero), 1.0f));

        Radian half_pi(HALF_PI);
        REQUIRE(fEqualE6(sin(half_pi), 1.0f));
        REQUIRE(fEqualE6(cos(half_pi), 0.0f));
    }

    SECTION("Arcsine and Arccosine")
    {
        Radian asin_pi_half = arcsin(1.0f);
        REQUIRE(fEqualE6(asin_pi_half.valueRadians(), HALF_PI));

        Radian acos_zero = arccos(0.0f);
        REQUIRE(fEqualE6(acos_zero.valueRadians(), HALF_PI));
    }

    SECTION("Arctangent")
    {
        Radian atan_zero = tdm::atan(0.0f);
        REQUIRE(fEqualE6(atan_zero.valueRadians(), 0.0f));

        Radian atan2_origin = tdm::atan2(0.0f, 0.0f);
        REQUIRE(fEqualE6(atan2_origin.valueRadians(), 0.0f));
    }
}

TEST_CASE("Helper Functions", "[Common]")
{
    SECTION("Swap")
    {
        float a = 1.0f, b = 2.0f;
        swap(a, b);
        REQUIRE(fEqualE6(a, 2.0f));
        REQUIRE(fEqualE6(b, 1.0f));
    }

    SECTION("Floor and Ceil")
    {
        REQUIRE(fEqualE6(tdm::floor(1.9f), 1.0f));
        REQUIRE(fEqualE6(tdm::ceil(1.1f), 2.0f));
    }

    SECTION("Square Root and Absolute")
    {
        REQUIRE(fEqualE6(tdm::sqrt(4.0f), 2.0f));
        REQUIRE(fEqualE6(tdm::abs(-5.0f), 5.0f));
        REQUIRE(fEqualE6(abs(Radian(-PI)), PI));
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
