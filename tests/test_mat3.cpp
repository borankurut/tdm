// test_mat3.cpp

#include "pch.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Mat3 Constructors", "[Mat3]")
{
    SECTION("Array Constructor")
    {
        float data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Mat3 m(data);
        Mat3 expected(1, 2, 3, 4, 5, 6, 7, 8, 9);
        REQUIRE(m == expected);
    }

    SECTION("Explicit Value Constructor")
    {
        Mat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Mat3 expected(1, 2, 3, 4, 5, 6, 7, 8, 9);
        REQUIRE(m == expected);
    }
}

TEST_CASE("Mat3 Multiplication", "[Mat3]")
{
    Mat3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat3 I = Mat3::Identity;

    SECTION("Identity Matrix Multiplication")
    {
        REQUIRE((A * I) == A);
        REQUIRE((I * A) == A);
    }

    SECTION("Scalar Multiplication")
    {
        Mat3 B = 2.0f * A;
        Mat3 expected(2, 4, 6, 8, 10, 12, 14, 16, 18);
        REQUIRE(B == expected);
    }

    SECTION("Matrix Multiplication")
    {
        Mat3 B(9, 8, 7, 6, 5, 4, 3, 2, 1);
        Mat3 C = A * B;
        Mat3 expected(1 * 9 + 2 * 6 + 3 * 3, 1 * 8 + 2 * 5 + 3 * 2, 1 * 7 + 2 * 4 + 3 * 1, 4 * 9 + 5 * 6 + 6 * 3,
                      4 * 8 + 5 * 5 + 6 * 2, 4 * 7 + 5 * 4 + 6 * 1, 7 * 9 + 8 * 6 + 9 * 3, 7 * 8 + 8 * 5 + 9 * 2,
                      7 * 7 + 8 * 4 + 9 * 1);
        REQUIRE(C == expected);
    }
}

TEST_CASE("Mat3 Transpose", "[Mat3]")
{
    Mat3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat3 AT = A.transpose();
    Mat3 expected(1, 4, 7, 2, 5, 8, 3, 6, 9);
    REQUIRE(AT == expected);
}

TEST_CASE("Mat3 Determinant", "[Mat3]")
{
    {
        Mat3 A(1, 2, 3, 0, 0, 0, 7, 8, 9);
        REQUIRE(fEqualE6(A.determinant(), (0.0f)));
    }

    {
        Mat3 B(342.0f, -42.0f, 53.0f, 11.9f, -31.57f, 0.05f, 99.0f, 21.0f, -3.0f);
        // Expected value calculated externally.
        REQUIRE(fEqualE6(B.determinant(), (209216.90999f)));
    }
}

TEST_CASE("Mat3 Inverse", "[Mat3]")
{
    {
        Mat3 A(2, 3, 1, 4, 6, 5, 1, -2, 3);
        Mat3 A_inv = A.inverse();
        REQUIRE((A * A_inv) == Mat3::Identity);
    }

    {
        Mat3 Singular(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Mat3 S_inv = Singular.inverse();
        REQUIRE((Singular * S_inv) == Mat3::Zero);
    }
}

TEST_CASE("Mat3 Row and Column Operations", "[Mat3]")
{
    Mat3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);

    SECTION("Get Row")
    {
        REQUIRE(A.getRow(0) == Vec3(1, 2, 3));
        REQUIRE(A.getRow(1) == Vec3(4, 5, 6));
        REQUIRE(A.getRow(2) == Vec3(7, 8, 9));
    }

    SECTION("Get Column")
    {
        REQUIRE(A.getColumn(0) == Vec3(1, 4, 7));
        REQUIRE(A.getColumn(1) == Vec3(2, 5, 8));
        REQUIRE(A.getColumn(2) == Vec3(3, 6, 9));
    }

    SECTION("Set Row")
    {
        A.setRow(1, Vec3(10, 11, 12));
        REQUIRE(A.getRow(1) == Vec3(10, 11, 12));
    }

    SECTION("Set Column")
    {
        A.setColumn(2, Vec3(13, 14, 15));
        REQUIRE(A.getColumn(2) == Vec3(13, 14, 15));
    }
}

TEST_CASE("Mat3 Equality Operators", "[Mat3]")
{
    Mat3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat3 B(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat3 C(9, 8, 7, 6, 5, 4, 3, 2, 1);

    REQUIRE(A == B);
    REQUIRE(A != C);
}

TEST_CASE("Mat3 Orthogonal Features", "[Mat3]")
{
    SECTION("isOrthogonal")
    {
        REQUIRE(Mat3::Identity.isOrthogonal());

        Mat3 nonOrth(2, 0, 0, 0, 3, 0, 0, 0, 4);
        REQUIRE_FALSE(nonOrth.isOrthogonal());
    }

    SECTION("orthogonalize")
    {
        Mat3 M(1, 1, 0, 0, 1, 1, 1, 0, 1);
        M.orthogonalize();
        REQUIRE(M.isOrthogonal());
    }
}
