#include "mat4.h"

namespace tdm
{

const Mat4 Mat4::Zero =
    Mat4{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

const Mat4 Mat4::Identity =
    Mat4{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

Mat4 Mat4::operator*(const Mat4& other) const
{
    return Mat4(m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12],
                m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13],
                m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14],
                m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15],

                m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12],
                m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13],
                m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14],
                m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15],

                m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12],
                m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13],
                m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14],
                m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15],

                m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12],
                m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13],
                m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14],
                m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15]);
}

Mat4 Mat4::operator*(float scalar) const
{
    return Mat4(m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar, m[4] * scalar, m[5] * scalar, m[6] * scalar,
                m[7] * scalar, m[8] * scalar, m[9] * scalar, m[10] * scalar, m[11] * scalar, m[12] * scalar,
                m[13] * scalar, m[14] * scalar, m[15] * scalar);
}

Vec4 operator*(const Vec4& vec, const Mat4& mat)
{
    return Vec4(vec.entries[0] * mat[0] + vec.entries[1] * mat[4] + vec.entries[2] * mat[8] + vec.entries[3] * mat[12],
                vec.entries[0] * mat[1] + vec.entries[1] * mat[5] + vec.entries[2] * mat[9] + vec.entries[3] * mat[13],
                vec.entries[0] * mat[2] + vec.entries[1] * mat[6] + vec.entries[2] * mat[10] + vec.entries[3] * mat[14],
                vec.entries[0] * mat[3] + vec.entries[1] * mat[7] + vec.entries[2] * mat[11] +
                    vec.entries[3] * mat[15]);
}

Mat4 Mat4::operator/(float scalar) const
{
    return Mat4(m[0] / scalar, m[1] / scalar, m[2] / scalar, m[3] / scalar, m[4] / scalar, m[5] / scalar, m[6] / scalar,
                m[7] / scalar, m[8] / scalar, m[9] / scalar, m[10] / scalar, m[11] / scalar, m[12] / scalar,
                m[13] / scalar, m[14] / scalar, m[15] / scalar);
}

bool Mat4::operator==(const Mat4& rhs) const
{
    return fEqualE6(m[0], rhs.m[0]) && fEqualE6(m[1], rhs.m[1]) && fEqualE6(m[2], rhs.m[2]) &&
           fEqualE6(m[3], rhs.m[3]) && fEqualE6(m[4], rhs.m[4]) && fEqualE6(m[5], rhs.m[5]) &&
           fEqualE6(m[6], rhs.m[6]) && fEqualE6(m[7], rhs.m[7]) && fEqualE6(m[8], rhs.m[8]) &&
           fEqualE6(m[9], rhs.m[9]) && fEqualE6(m[10], rhs.m[10]) && fEqualE6(m[11], rhs.m[11]) &&
           fEqualE6(m[12], rhs.m[12]) && fEqualE6(m[13], rhs.m[13]) && fEqualE6(m[14], rhs.m[14]) &&
           fEqualE6(m[15], rhs.m[15]);
}

float Mat4::minor(int r_0, int r_1, int r_2, int c_0, int c_1, int c_2) const
{
    float m0 = m[r_0 * 4 + c_0];
    float m1 = m[r_0 * 4 + c_1];
    float m2 = m[r_0 * 4 + c_2];

    float m3 = m[r_1 * 4 + c_0];
    float m4 = m[r_1 * 4 + c_1];
    float m5 = m[r_1 * 4 + c_2];

    float m6 = m[r_2 * 4 + c_0];
    float m7 = m[r_2 * 4 + c_1];
    float m8 = m[r_2 * 4 + c_2];

    return m0 * (m4 * m8 - m5 * m7) + m1 * (m5 * m6 - m3 * m8) + m2 * (m3 * m7 - m4 * m6);
}

float Mat4::determinant() const
{
    return m[0] * minor(1, 2, 3, 1, 2, 3) - m[1] * minor(1, 2, 3, 0, 2, 3) + m[2] * minor(1, 2, 3, 0, 1, 3) -
           m[3] * minor(1, 2, 3, 0, 1, 2);
}

Mat4 Mat4::inverse() const
{
    Mat4 mInv = getAdj();

    float det = m[0] * mInv[0] + m[1] * mInv[4] + m[2] * mInv[8] + m[3] * mInv[12];

    if (fEqualE6(det, 0.0f))
        return Mat4::Zero;

    float invDet = 1.0f / det;

    for (int i = 0; i < 16; ++i)
    {
        mInv[i] *= invDet;
    }

    return mInv;
}

Mat4 Mat4::getAdj() const
{
    // calculate adjoint
    // cofactors are set considering the transposed order so no need to transpose.
    Mat4 mAdj;

    mAdj[0] = minor(1, 2, 3, 1, 2, 3);
    mAdj[1] = -minor(0, 2, 3, 1, 2, 3);
    mAdj[2] = minor(0, 1, 3, 1, 2, 3);
    mAdj[3] = -minor(0, 1, 2, 1, 2, 3);

    mAdj[4] = -minor(1, 2, 3, 0, 2, 3);
    mAdj[5] = minor(0, 2, 3, 0, 2, 3);
    mAdj[6] = -minor(0, 1, 3, 0, 2, 3);
    mAdj[7] = minor(0, 1, 2, 0, 2, 3);

    mAdj[8] = minor(1, 2, 3, 0, 1, 3);
    mAdj[9] = -minor(0, 2, 3, 0, 1, 3);
    mAdj[10] = minor(0, 1, 3, 0, 1, 3);
    mAdj[11] = -minor(0, 1, 2, 0, 1, 3);

    mAdj[12] = -minor(1, 2, 3, 0, 1, 2);
    mAdj[13] = minor(0, 2, 3, 0, 1, 2);
    mAdj[14] = -minor(0, 1, 3, 0, 1, 2);
    mAdj[15] = minor(0, 1, 2, 0, 1, 2);

    return mAdj;
}

} // namespace tdm
