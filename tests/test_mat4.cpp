// test_mat3.cpp
// ########## TEST MAT3 ##########

#include "common_math.h"
#include "mat4.h"
#include "vec3.h"
#include "vec4.h"
#include <catch2/catch_test_macros.hpp>

using namespace tdm;

TEST_CASE("Mat4 Constructors", "[Mat4]")
{
    SECTION("Array Constructor")
    {
        float data[16] = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                          9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
        Mat4 m(data);
        REQUIRE(tdm::abs(m[0] - 1.0f) < EPSILON_6);
        REQUIRE(tdm::abs(m[5] - 6.0f) < EPSILON_6);
        REQUIRE(tdm::abs(m[15] - 16.0f) < EPSILON_6);
    }

    SECTION("Value Constructor")
    {
        Mat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        REQUIRE(tdm::abs(m[0] - 1.0f) < EPSILON_6);
        REQUIRE(tdm::abs(m[7] - 8.0f) < EPSILON_6);
        REQUIRE(tdm::abs(m[15] - 16.0f) < EPSILON_6);
    }
}

TEST_CASE("Mat4 Basic Operations", "[Mat4]")
{
    Mat4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    SECTION("Scalar Multiplication")
    {
        Mat4 B = 2.0f * A;
        REQUIRE(tdm::abs(B[0] - 2.0f) < EPSILON_6);
        REQUIRE(tdm::abs(B[5] - 12.0f) < EPSILON_6);
        REQUIRE(tdm::abs(B[15] - 32.0f) < EPSILON_6);
    }

    SECTION("Matrix Multiplication")
    {
        Mat4 B = A * Mat4::Identity;
        REQUIRE(B == A);

        Mat4 C = A * A;
        REQUIRE(tdm::abs(C[0] - 90.0f) < EPSILON_6);
        REQUIRE(tdm::abs(C[1] - 100.0f) < EPSILON_6);
        REQUIRE(tdm::abs(C[15] - 600.0f) < EPSILON_6);
    }

    SECTION("Vector Multiplication")
    {
        Vec4 v(1, 2, 3, 4);
        Vec4 result = v * Mat4::Identity;
        REQUIRE(result == v);
    }
}

TEST_CASE("Mat4 Transpose", "[Mat4]")
{
    Mat4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    SECTION("Transpose Properties")
    {
        Mat4 AT = A.transpose();
        Mat4 ATT = AT.transpose();
        REQUIRE(ATT == A);
    }
}

TEST_CASE("Mat4 Determinant and Inverse", "[Mat4]")
{
    SECTION("Identity Matrix")
    {
        Mat4 I = Mat4::Identity;
        REQUIRE(tdm::abs(I.determinant() - 1.0f) < EPSILON_6);
        Mat4 I_inv = I.inverse();
        REQUIRE(I_inv == I);
    }

    SECTION("Invertible Matrix")
    {
        Mat4 A(4, 7, 2, 3, 0, 5, 0, 1, 0, 0, 3, 0, 0, 0, 0, 1);

        Mat4 A_inv = A.inverse();
        Mat4 product = A * A_inv;

        for (int i = 0; i < 16; i++)
        {
            float expected = (i % 5 == 0) ? 1.0f : 0.0f; // Diagonal elements
            REQUIRE(tdm::abs(product[i] - expected) < EPSILON_6);
        }
    }

    SECTION("Singular Matrix")
    {
        Mat4 S(1, 2, 3, 4, 2, 4, 6, 8, 3, 6, 9, 12, 4, 8, 12, 16);
        REQUIRE(tdm::abs(S.determinant()) < EPSILON_6);
        REQUIRE(S.inverse() == Mat4::Zero);
    }
}

TEST_CASE("Mat4 Special Functions", "[Mat4]")
{
    SECTION("Translation")
    {
        Vec3 translation(5, 6, 7);
        Mat4 T = Mat4::translationMatrix(translation);

        REQUIRE(tdm::abs(T[12] - 5.0f) < EPSILON_6);
        REQUIRE(tdm::abs(T[13] - 6.0f) < EPSILON_6);
        REQUIRE(tdm::abs(T[14] - 7.0f) < EPSILON_6);

        Mat4 R1 = Mat4::rotMatCardinalX(Degree(90.0f));
        Mat4 R2 = Mat4::rotMatCardinalY(Degree(90.0f));
        Mat4 R3 = Mat4::rotMatCardinalZ(Degree(90.0f));

        Mat4 R1n = Mat4::rotMatCardinalX(Degree(-90.0f));
        Mat4 R2n = Mat4::rotMatCardinalY(Degree(-90.0f));
        Mat4 R3n = Mat4::rotMatCardinalZ(Degree(-90.0f));

        REQUIRE(R1.inverse() == R1n);
        REQUIRE(R2.inverse() == R2n);
        REQUIRE(R3.inverse() == R3n);

        Vec4 p = Vec4(1.0f, 2.0f, -3.0f, 1.0f);
        REQUIRE(p * R1 * R2 * R3 * R3n * R2n * R1n == p);
    }
}

TEST_CASE("Mat4 Edge Cases", "[Mat4]")
{
    SECTION("Zero Matrix")
    {
        Mat4 Z = Mat4::Zero;
        REQUIRE(Z.determinant() < EPSILON_6);
        REQUIRE(Z.inverse() == Z);
    }

    SECTION("Near-Singular Matrix")
    {
        Mat4 A(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, EPSILON_6 / 2);
        REQUIRE(tdm::abs(A.determinant()) < EPSILON_6);
    }
}
