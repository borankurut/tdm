// test_mat2.cpp
// ########## TEST MAT2 ##########

#include "mat2.h"
#include <catch2/catch_all.hpp>

using namespace tdm;

TEST_CASE("Mat2 Constructors", "[Mat2]")
{
    SECTION("Array Constructor")
    {
        float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
        Mat2 m(data);
        REQUIRE(m[0] == 1.0f);
        REQUIRE(m[3] == 4.0f);
    }

    SECTION("Explicit Value Constructor")
    {
        Mat2 m(1, 2, 3, 4);
        REQUIRE(m[0] == 1);
        REQUIRE(m[3] == 4);
    }
}

TEST_CASE("Mat2 Multiplication", "[Mat2]")
{
    Mat2 A(1, 2, 3, 4);
    Mat2 I = Mat2::Identity;

    SECTION("Identity Matrix Multiplication")
    {
        REQUIRE(A * I == A);
        REQUIRE(I * A == A);
    }

    SECTION("Scalar Multiplication")
    {
        Mat2 B = 2.0f * A;
        REQUIRE(B[0] == 2);
        REQUIRE(B[3] == 8);
    }

    SECTION("Matrix Multiplication")
    {
        Mat2 B(4, 3, 2, 1);
        Mat2 C = A * B;
        REQUIRE(C[0] == (1 * 4 + 2 * 2));
        REQUIRE(C[3] == (3 * 3 + 4 * 1));
    }
}

TEST_CASE("Mat2 Transpose", "[Mat2]")
{
    Mat2 A(1, 2, 3, 4);
    Mat2 AT = A.transpose();
    REQUIRE(AT[0] == A[0]);
    REQUIRE(AT[1] == A[2]);
    REQUIRE(AT[2] == A[1]);
    REQUIRE(AT[3] == A[3]);
}

TEST_CASE("Mat2 Determinant", "[Mat2]")
{
    Mat2 A(1, 2, 3, 4);
    REQUIRE(fEqualE6(A.determinant(), -2.0f));
}

TEST_CASE("Mat2 Inverse", "[Mat2]")
{
    Mat2 A(4, 7, 2, 6);
    Mat2 A_inv = A.inverse();
    REQUIRE((A * A_inv) == Mat2::Identity);

    Mat2 Singular(1, 2, 2, 4);
    Mat2 S_inv = Singular.inverse();
    REQUIRE(Singular * S_inv == Mat2::Zero);
}

TEST_CASE("Mat2 Row and Column Operations", "[Mat2]")
{
    Mat2 A(1, 2, 3, 4);

    SECTION("Get Row")
    {
        REQUIRE(A.getRow(0) == Vec2(1, 2));
        REQUIRE(A.getRow(1) == Vec2(3, 4));
    }

    SECTION("Get Column")
    {
        REQUIRE(A.getColumn(0) == Vec2(1, 3));
        REQUIRE(A.getColumn(1) == Vec2(2, 4));
    }

    SECTION("Set Row")
    {
        A.setRow(1, Vec2(5, 6));
        REQUIRE(A.getRow(1) == Vec2(5, 6));
    }

    SECTION("Set Column")
    {
        A.setColumn(1, Vec2(7, 8));
        REQUIRE(A.getColumn(1) == Vec2(7, 8));
    }
}

TEST_CASE("Mat2 Equality Operators", "[Mat2]")
{
    Mat2 A(1, 2, 3, 4);
    Mat2 B(1, 2, 3, 4);
    Mat2 C(4, 3, 2, 1);

    REQUIRE(A == B);
    REQUIRE(A != C);
}
