// test_orientation.cpp

#include "pch.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Orientation Matrix", "[Orientation]")
{
    std::vector<Euler> eulers;
    std::vector<OrientationMatrix> orientationMatrices;

    Euler e0_0_0 = Euler(Degree(0), Degree(0), Degree(0));
    Euler e30_30_30 = Euler(Degree(30), Degree(30), Degree(30));
    Euler e60_m45_30 = Euler(Degree(60), Degree(-45), Degree(30));
    Euler e190_m50_0 = Euler(Degree(190), Degree(-50), Degree(0));
    Euler e90_135_m90 = Euler(Degree(90), Degree(135), Degree(-90));

    eulers.push_back(e0_0_0);
    eulers.push_back(e30_30_30);
    eulers.push_back(e60_m45_30);
    eulers.push_back(e190_m50_0);
    eulers.push_back(e90_135_m90);

    for (int i = 0; i < eulers.size(); ++i)
    {
        orientationMatrices.push_back(OrientationMatrix(eulers[i]));
    }

    SECTION("Constructors")
    {
        Vec3 p = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 q = Vec3(0.0f, 1.0f, 0.0f);
        Vec3 r = Vec3(0.0f, 0.0f, 1.0f);

        OrientationMatrix orientationMatrix = OrientationMatrix(p, q, r);
        REQUIRE(orientationMatrix.getToUprightSpace() == Mat3::Identity);
        REQUIRE(orientationMatrix.getToObjectSpace() == Mat3::Identity);

        REQUIRE(OrientationMatrix(Mat3::Identity).getToUprightSpace() == Mat3::Identity);
    }

    SECTION("Euler Conversions", "[Orientation]")
    {
        // yxz conversion because head, pitch, bank

        REQUIRE(orientationMatrices[0] == OrientationMatrix::Identity);

        for (int i = 0; i < orientationMatrices.size(); ++i)
        {
            CAPTURE(i);
            REQUIRE(orientationMatrices[i].toEuler() == eulers[i]);
        }
    }

    SECTION("Quaternion Conversions", "[Orientation]")
    {
        for (int i = 0; i < orientationMatrices.size(); ++i)
        {
            CAPTURE(i);
            REQUIRE(OrientationMatrix(orientationMatrices[i].toQuaternion()) == orientationMatrices[i]);
        }
        REQUIRE(OrientationMatrix(Quaternion::Identity) == OrientationMatrix::Identity);
    }

    SECTION("Quaternion and Euler Conversions", "[Orientation]")
    {
        for (int i = 0; i < eulers.size(); ++i)
        {
            CAPTURE(i);
            Quaternion q = eulerToQuaternion(eulers[i]);
            REQUIRE(eulers[i] == quaternionToEuler(q));
        }
    }
}
