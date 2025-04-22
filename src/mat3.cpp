#include "mat3.h"

namespace tdm
{

Mat3 Mat3::Zero = Mat3{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

Mat3 Mat3::Identity = Mat3{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

Mat3 Mat3::operator*(const Mat3& other) const
{
    return Mat3(m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6], // row 1, col 1
                m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7], // row 1, col 2
                m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8], // row 1, col 3

                m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6], // row 2, col 1
                m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7], // row 2, col 2
                m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8], // row 2, col 3

                m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6], // row 3, col 1
                m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7], // row 3, col 2
                m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8]  // row 3, col 3
    );
}

Mat3 Mat3::operator*(float scalar) const
{
    return Mat3(m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar, m[4] * scalar, m[5] * scalar, m[6] * scalar,
                m[7] * scalar, m[8] * scalar);
}

Vec3 operator*(const Vec3& vec, const Mat3& mat)
{
    return Vec3(vec.entries[0] * mat[0] + vec.entries[1] * mat[3] + vec.entries[2] * mat[6],
                vec.entries[0] * mat[1] + vec.entries[1] * mat[4] + vec.entries[2] * mat[7],
                vec.entries[0] * mat[2] + vec.entries[1] * mat[5] + vec.entries[2] * mat[8]);
}

Mat3 Mat3::operator/(float scalar) const
{
    return Mat3(m[0] / scalar, m[1] / scalar, m[2] / scalar, m[3] / scalar, m[4] / scalar, m[5] / scalar, m[6] / scalar,
                m[7] / scalar, m[8] / scalar);
}

bool Mat3::operator==(const Mat3& rhs) const
{
    return fEqualE6(m[0], rhs.m[0]) && fEqualE6(m[1], rhs.m[1]) && fEqualE6(m[2], rhs.m[2]) &&
           fEqualE6(m[3], rhs.m[3]) && fEqualE6(m[4], rhs.m[4]) && fEqualE6(m[5], rhs.m[5]) &&
           fEqualE6(m[6], rhs.m[6]) && fEqualE6(m[7], rhs.m[7]);
}

Mat3 Mat3::inverse() const
{
    Mat3 mInv;
    mInv[0] = (m[4] * m[8]) - (m[5] * m[7]);
    mInv[1] = (m[7] * m[2]) - (m[8] * m[1]);
    mInv[2] = (m[1] * m[5]) - (m[2] * m[4]);
    mInv[3] = (m[5] * m[6]) - (m[3] * m[8]);
    mInv[4] = (m[8] * m[0]) - (m[6] * m[2]);
    mInv[5] = (m[2] * m[3]) - (m[0] * m[5]);
    mInv[6] = (m[3] * m[7]) - (m[4] * m[6]);
    mInv[7] = (m[6] * m[1]) - (m[7] * m[0]);
    mInv[8] = (m[0] * m[4]) - (m[1] * m[3]);

    float det = m[0] * mInv[0] + m[1] * mInv[3] + m[2] * mInv[6];

    if (fEqualE6(det, 0.0f))
        return Mat3::Zero;

    float invDet = 1.0f / det;

    for (int i = 0; i < 9; ++i)
    {
        mInv[i] *= invDet;
    }

    return mInv;
}

bool Mat3::isOrthogonal() const
{
    Vec3 r0 = getRow(0);
    Vec3 r1 = getRow(1);
    Vec3 r2 = getRow(2);

    float r0r0 = r0.dot(r0);
    float r0r1 = r0.dot(r1);
    float r0r2 = r0.dot(r2);
    float r1r1 = r1.dot(r1);
    float r1r2 = r1.dot(r2);
    float r2r2 = r2.dot(r2);

    return fEqualE6(r0r0, 1.0f) && fEqualE6(r0r1, 0.0f) && fEqualE6(r0r2, 0.0f) && fEqualE6(r1r1, 1.0f) &&
           fEqualE6(r1r2, 0.0f) && fEqualE6(r2r2, 1.0f);
}

} // namespace tdm
