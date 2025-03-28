// test_polar2.cpp
#include "common_math.h"
#include "polar2.h"
#include "vec2.h"
#include <catch2/catch_all.hpp>
#include <cmath>

using namespace tdm;

TEST_CASE("Polar2 Basic Functionality", "[Polar2]")
{
    SECTION("Construct from radius and heading")
    {
        Radian angle = Radian(PI / 4.0f);
        float radius = 5.0f;
        Polar2 p(radius, angle);
        REQUIRE(tdm::abs(p.r() - radius) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.h() - angle) < tdm::EPSILON_6);
    }

    SECTION("Convert to Cartesian")
    {
        Radian angle = Radian(PI / 3.0f);
        float radius = 10.0f;
        Polar2 p(radius, angle);
        Vec2 cart = p.toCartesian();

        float expectedX = radius * tdm::cos(angle);
        float expectedY = radius * tdm::sin(angle);
        REQUIRE(tdm::abs(cart.x() - expectedX) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(cart.y() - expectedY) < tdm::EPSILON_6);
    }

    SECTION("Construct from Cartesian")
    {
        Vec2 cart(3.0f, 3.0f);
        Polar2 p(cart);

        float expectedRadius = tdm::sqrt(3.0f * 3.0f + 3.0f * 3.0f);
        Radian expectedAngle = Radian(tdm::atan2(3.0f, 3.0f));
        REQUIRE(tdm::abs(p.r() - expectedRadius) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.h() - expectedAngle) < tdm::EPSILON_6);
    }
}
