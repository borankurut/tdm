// test_euler.cpp
#include "common_math.h"
#include "euler.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Euler Canonicalization", "[Euler]")
{

    SECTION("Canonical angles remain unchanged")
    {
        Radian head(PI / 4.0f);
        Radian pitch(PI / 8.0f);
        Radian bank(PI / 6.0f);
        Euler e(head, pitch, bank);

        REQUIRE(tdm::abs(e.head().valueRadians() - head.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.pitch().valueRadians() - pitch.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.bank().valueRadians() - bank.valueRadians()) < EPSILON_6);
    }

    SECTION("Flip pitch when above HALF_PI")
    {
        Radian head(0.0f);
        Radian pitch(3.0f * PI / 4.0f);
        Radian bank(0.0f);
        Euler e(head, pitch, bank);

        Radian expectedPitch(PI / 4.0f);
        Radian expectedHead(wrapPi(Radian(0.0f + PI)));
        Radian expectedBank(wrapPi(Radian(0.0f + PI)));

        REQUIRE(tdm::abs(e.pitch().valueRadians() - expectedPitch.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.head().valueRadians() - expectedHead.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.bank().valueRadians() - expectedBank.valueRadians()) < EPSILON_6);
    }

    SECTION("Flip pitch when below -HALF_PI")
    {
        Radian head(0.0f);
        Radian pitch(-3.0f * PI / 4.0f);
        Radian bank(0.0f);
        Euler e(head, pitch, bank);

        Radian expectedPitch(-PI / 4.0f);
        Radian expectedHead(wrapPi(Radian(0.0f + PI)));
        Radian expectedBank(wrapPi(Radian(0.0f + PI)));

        REQUIRE(tdm::abs(e.pitch().valueRadians() - expectedPitch.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.head().valueRadians() - expectedHead.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.bank().valueRadians() - expectedBank.valueRadians()) < EPSILON_6);
    }

    SECTION("Gimbal lock handling (pitch at HALF_PI)")
    {
        Radian head(0.0f);
        Radian pitch(HALF_PI);
        Radian bank(10.0f * fDegToRad);
        Euler e(head, pitch, bank);

        Radian expectedHead(wrapPi(Radian(0.0f + bank.valueRadians())));
        Radian expectedBank(0.0f);

        REQUIRE(tdm::abs(e.head().valueRadians() - expectedHead.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.bank().valueRadians() - expectedBank.valueRadians()) < EPSILON_6);
        REQUIRE(tdm::abs(e.pitch().valueRadians() - HALF_PI) < EPSILON_6);
    }
}
