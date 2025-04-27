// test_euler.cpp

#include "pch.h"
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

        REQUIRE(rEqualE7(e.head(), head));
        REQUIRE(rEqualE7(e.pitch(), pitch));
        REQUIRE(rEqualE7(e.bank(), bank));
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

        REQUIRE(rEqualE7(e.pitch(), expectedPitch));
        REQUIRE(rEqualE7(e.head(), expectedHead));
        REQUIRE(rEqualE7(e.bank(), expectedBank));
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

        REQUIRE(rEqualE7(e.pitch(), expectedPitch));
        REQUIRE(rEqualE7(e.head(), expectedHead));
        REQUIRE(rEqualE7(e.bank(), expectedBank));
    }

    SECTION("Gimbal lock handling (pitch at HALF_PI)")
    {
        Radian head(0.0f);
        Radian pitch(HALF_PI);
        Radian bank(10.0f * fDegToRad);
        Euler e(head, pitch, bank);

        Radian expectedHead(wrapPi(Radian(0.0f + bank.valueRadians())));
        Radian expectedBank(0.0f);

        REQUIRE(rEqualE7(e.pitch(), pitch));
        REQUIRE(rEqualE7(e.head(), expectedHead));
        REQUIRE(rEqualE7(e.bank(), expectedBank));
    }
}
