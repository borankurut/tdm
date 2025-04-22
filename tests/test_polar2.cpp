// test_polar2.cpp
#include "common_math.h"
#include "polar2.h"
#include "vec2.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Polar2 Basic Functionality", "[Polar2]")
{
    SECTION("Construct from radius and heading")
    {
        Radian angle = Radian(PI / 4.0f);
        float radius = 5.0f;
        Polar2 p(radius, angle);
        REQUIRE(fEqualE6(p.r(), radius));
        REQUIRE(rEqualE6(p.h(), angle));
    }

    SECTION("Convert to Cartesian")
    {
        Radian angle = Radian(PI / 3.0f);
        float radius = 10.0f;
        Polar2 p(radius, angle);
        Vec2 cart = p.toCartesian();

        float expectedX = radius * tdm::cos(angle);
        float expectedY = radius * tdm::sin(angle);
        REQUIRE(fEqualE6(cart.x(), expectedX));
        REQUIRE(fEqualE6(cart.y(), expectedY));
    }

    SECTION("Construct from Cartesian")
    {
        Vec2 cart(3.0f, 3.0f);
        Polar2 p(cart);

        float expectedRadius = tdm::sqrt(3.0f * 3.0f + 3.0f * 3.0f);
        Radian expectedAngle = Radian(tdm::atan2(3.0f, 3.0f));
        REQUIRE(fEqualE6(p.r(), expectedRadius));
        REQUIRE(rEqualE6(p.h(), expectedAngle));
    }
}
