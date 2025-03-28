// test_polar3.cpp
#include "common_math.h"
#include "polar3.h"
#include "vec3.h"
#include <catch2/catch_all.hpp>
#include <cmath>

using namespace tdm;

TEST_CASE("Polar3 Basic Functionality", "[Polar3]")
{
    SECTION("Construct from radius, heading, and pitch")
    {
        float radius = 10.0f;
        Radian heading = Radian(PI / 4.0f);
        Radian pitch = Radian(PI / 6.0f);
        Polar3 p(radius, heading, pitch);

        REQUIRE(tdm::abs(p.r() - radius) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.h() - heading) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.p() - pitch) < tdm::EPSILON_6);
    }

    SECTION("Convert to Cartesian")
    {
        float radius = 5.0f;
        Radian heading = Radian(PI / 3.0f);
        Radian pitch = Radian(-PI / 8.0f);
        Polar3 p(radius, heading, pitch);
        Vec3 cart = p.toCartesian();

        float expectedX = radius * cos(pitch.valueRadians()) * sin(heading.valueRadians());
        float expectedY = -radius * sin(pitch.valueRadians());
        float expectedZ = radius * cos(pitch.valueRadians()) * cos(heading.valueRadians());

        REQUIRE(tdm::abs(cart.x() - expectedX) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(cart.y() - expectedY) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(cart.z() - expectedZ) < tdm::EPSILON_6);
    }

    SECTION("Construct from Cartesian")
    {
        float radius = 7.0f;
        Radian heading = Radian(PI / 4.0f);
        Radian pitch = Radian(PI / 8.0f);

        float x = radius * cos(pitch.valueRadians()) * sin(heading.valueRadians());
        float y = -radius * sin(pitch.valueRadians());
        float z = radius * cos(pitch.valueRadians()) * cos(heading.valueRadians());
        Vec3 cart(x, y, z);

        Polar3 p(cart);

        REQUIRE(tdm::abs(p.r() - radius) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.h() - heading) < tdm::EPSILON_6);
        REQUIRE(tdm::abs(p.p() - pitch) < tdm::EPSILON_6);
    }
}
