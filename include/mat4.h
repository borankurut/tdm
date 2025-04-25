#pragma once

#include "mat3.h"
#include "vec3.h"
#include "vec4.h"
#include <iostream>

namespace tdm
{

class Mat4
{
public:
    Mat4() { /*empty*/ }

    explicit Mat4(const float arr[16]) { memcpy(m, arr, 16 * sizeof(float)); }

    Mat4(float m_1, float m_2, float m_3, float m_4, float m_5, float m_6, float m_7, float m_8, float m_9, float m_10,
         float m_11, float m_12, float m_13, float m_14, float m_15, float m_16)
        : m{m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8, m_9, m_10, m_11, m_12, m_13, m_14, m_15, m_16}
    { /*empty*/
    }

    Mat4& operator=(const Mat4& other)
    {
        memcpy(m, other.m, 16 * sizeof(float));
        return *this;
    }

    // +
    const Mat4& operator+() const { return *this; }
    Mat4 operator+(const Mat4& other) const
    {
        return Mat4(m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3], m[4] + other.m[4],
                    m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7], m[8] + other.m[8], m[9] + other.m[9],
                    m[10] + other.m[10], m[11] + other.m[11], m[12] + other.m[12], m[13] + other.m[13],
                    m[14] + other.m[14], m[15] + other.m[15]);
    }
    Mat4& operator+=(const Mat4& other) { return (*this = *this + other); }

    // -
    Mat4 operator-() const
    {
        return Mat4(-m[0], -m[1], -m[2], -m[3], -m[4], -m[5], -m[6], -m[7], -m[8], -m[9], -m[10], -m[11], -m[12],
                    -m[13], -m[14], -m[15]);
    }
    Mat4 operator-(const Mat4& other) const
    {
        return Mat4(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3], m[4] - other.m[4],
                    m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7], m[8] - other.m[8], m[9] - other.m[9],
                    m[10] - other.m[10], m[11] - other.m[11], m[12] - other.m[12], m[13] - other.m[13],
                    m[14] - other.m[14], m[15] - other.m[15]);
    }
    Mat4& operator-=(const Mat4& other) { return (*this = *this - other); }

    // *
    Mat4 operator*(float scalar) const;
    friend Mat4 operator*(float scalar, const Mat4& mat) { return mat * scalar; }
    Mat4 operator*(const Mat4& other) const;
    friend Vec4 operator*(const Vec4& vec, const Mat4& mat);

    Mat4& operator*=(const Mat4& other) { return (*this = *this * other); }
    Mat4& operator*=(float scalar) { return (*this = *this * scalar); }

    // /
    Mat4 operator/(float scalar) const;
    friend Mat4 operator/(float scalar, const Mat4& mat) { return mat / scalar; }
    Mat4& operator/=(float scalar) { return (*this = *this / scalar); }

    // comparators
    bool operator==(const Mat4& other) const;
    bool operator!=(const Mat4& other) const { return !(*this == other); }

    // indexing
    float& operator[](int ix)
    {
        assert(ix >= 0 && ix < 16);
        return m[ix];
    }
    const float& operator[](int ix) const
    {
        assert(ix >= 0 && ix < 16);
        return m[ix];
    }

    // output stream
    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat)
    {
        os << "[ " << mat.m[0] << ", " << mat.m[1] << ", " << mat.m[2] << ", " << mat.m[3] << "; " << mat.m[4] << ", "
           << mat.m[5] << ", " << mat.m[6] << ", " << mat.m[7] << "; " << mat.m[8] << ", " << mat.m[9] << ", "
           << mat.m[10] << ", " << mat.m[11] << "; " << mat.m[12] << ", " << mat.m[13] << ", " << mat.m[14] << ", "
           << mat.m[15] << "]";
        return os;
    }

    // matrix operations
    Mat4 transpose() const
    {
        return Mat4(m[0], m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10], m[14], m[3], m[7], m[11],
                    m[15]);
    }

    float determinant() const;

    Mat4 inverse() const;

    // getters
    Vec4 getRow(int ixRow) const
    {
        assert(ixRow < 4);
        int i = 4 * ixRow;
        return Vec4(m[i], m[i + 1], m[i + 2], m[i + 3]);
    }

    Vec4 getColumn(int ixColumn) const
    {
        assert(ixColumn < 4);
        return Vec4(m[ixColumn], m[ixColumn + 4], m[ixColumn + 8], m[ixColumn + 12]);
    }

    // settters
    void setRow(int ixRow, const Vec4& vec)
    {
        assert(ixRow < 4);
        int i = 4 * ixRow;
        m[i] = vec.entries[0];
        m[i + 1] = vec.entries[1];
        m[i + 2] = vec.entries[2];
        m[i + 3] = vec.entries[3];
    }

    void setColumn(int ixColumn, const Vec4& vec)
    {
        assert(ixColumn < 4);
        m[ixColumn] = vec.entries[0];
        m[ixColumn + 4] = vec.entries[1];
        m[ixColumn + 8] = vec.entries[2];
        m[ixColumn + 12] = vec.entries[3];
    }

    // 3D operations
    Mat3 getLinearTransformation() const { return Mat3{m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]}; }

    static Mat4 translationMatrix(const Vec3& translationVector)
    {
        Mat4 mTranslation = Mat4::Identity;
        mTranslation.setRow(3, Vec4(translationVector.x(), translationVector.y(), translationVector.z(), 1.0f));
        return mTranslation;
    }

    static Mat4 rotMatCardinalX(const Radian& r)
    {
        Mat4 m = Mat4::Identity;
        m.setLinearTransformation(Mat3::rotMatCardinalX(r));
        return m;
    }

    static Mat4 rotMatCardinalY(const Radian& r)
    {
        Mat4 m = Mat4::Identity;
        m.setLinearTransformation(Mat3::rotMatCardinalY(r));
        return m;
    }

    static Mat4 rotMatCardinalZ(const Radian& r)
    {
        Mat4 m = Mat4::Identity;
        m.setLinearTransformation(Mat3::rotMatCardinalZ(r));
        return m;
    }

    static Mat4 scaleCardinal(float k_x, float k_y, float k_z)
    {
        Mat4 m = Mat4::Identity;
        m.setLinearTransformation(Mat3::scaleCardinal(k_x, k_y, k_z));
        return m;
    }

    static Mat4 scaleArbitrary(const Vec3& vec, float k)
    {
        Mat4 m = Mat4::Identity;
        m.setLinearTransformation(Mat3::scaleArbitrary(vec, k));
        return m;
    }

    static Mat4 reflection(const Vec3& vec) { return scaleArbitrary(vec, -1.0f); }

    static Mat4& translate(Mat4& matrix, const Vec3& vector)
    {
        matrix *= translationMatrix(vector);
        return matrix;
    }

    Mat4 getAdj() const;

    // special matrices
    static const Mat4 Zero;
    static const Mat4 Identity;

private:
    float m[16];

    /*inputs are non removed rows and columns*/
    float minor(int r_0, int r_1, int r_2, int c_0, int c_1, int c_2) const;

    void setLinearTransformation(const Mat3& mLinearTransformation)
    {
        m[0] = mLinearTransformation[0];
        m[1] = mLinearTransformation[1];
        m[2] = mLinearTransformation[2];

        m[4] = mLinearTransformation[3];
        m[5] = mLinearTransformation[4];
        m[6] = mLinearTransformation[5];

        m[8] = mLinearTransformation[6];
        m[9] = mLinearTransformation[7];
        m[10] = mLinearTransformation[8];
    }
};

} // namespace tdm
