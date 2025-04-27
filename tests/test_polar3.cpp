// test_polar3.cpp

#include "pch.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Polar3 Basic Functionality", "[Polar3]")
{
    SECTION("Construct from radius, heading, and pitch")
    {
        float radius = 10.0f;
        Radian heading = Radian(PI / 4.0f);
        Radian pitch = Radian(PI / 6.0f);
        Polar3 p(radius, heading, pitch);

        REQUIRE(fEqualE6(p.r(), radius));
        REQUIRE(rEqualE6(p.h(), heading));
        REQUIRE(rEqualE6(p.p(), pitch));
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

        REQUIRE(fEqualE6(cart.x(), expectedX));
        REQUIRE(fEqualE6(cart.y(), expectedY));
        REQUIRE(fEqualE6(cart.z(), expectedZ));
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

        REQUIRE(fEqualE6(p.r(), radius));
        REQUIRE(rEqualE6(p.h(), heading));
        REQUIRE(rEqualE6(p.p(), pitch));
    }
}
