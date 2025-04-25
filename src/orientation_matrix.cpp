#include "orientation_matrix.h"
#include "euler.h"
#include "quaternion.h"

namespace tdm
{

const OrientationMatrix OrientationMatrix::Identity =
    OrientationMatrix(Mat3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

OrientationMatrix::OrientationMatrix(const Euler& euler)
{
    Radian h = euler.head();
    Radian p = euler.pitch();
    Radian b = euler.bank();

    float ch = cos(h);
    float cp = cos(p);
    float cb = cos(b);

    float sh = sin(h);
    float sp = sin(p);
    float sb = sin(b);

    m_toUprightSpace = Mat3(

        // row 1:
        (ch * cb) + (sh * sp * sb),

        sb * cp,

        (-sh * cb) + (ch * sp * sb),

        // row 2:
        (-ch * sb) + (sh * sp * cb),

        cb * cp,

        (sb * sh) + (ch * sp * cb),

        // row 3:
        sh * cp,

        -sp,

        ch * cp

    );
}

OrientationMatrix::OrientationMatrix(const Quaternion& quaternion)
{
    float x2 = quaternion.x() * quaternion.x();
    float y2 = quaternion.y() * quaternion.y();
    float z2 = quaternion.z() * quaternion.z();

    float wx = quaternion.w() * quaternion.x();
    float wy = quaternion.w() * quaternion.y();
    float wz = quaternion.w() * quaternion.z();

    float xy = quaternion.x() * quaternion.y();
    float xz = quaternion.x() * quaternion.z();
    float yz = quaternion.y() * quaternion.z();

    m_toUprightSpace = Mat3(

        // row 1:
        1 - 2 * y2 - 2 * z2,

        2 * xy + 2 * wz,

        2 * xz - 2 * wy,

        // row 2:
        2 * xy - 2 * wz,

        1 - 2 * x2 - 2 * z2,

        2 * yz + 2 * wx,

        // row 3:
        2 * xz + 2 * wy,

        2 * yz - 2 * wx,

        1 - 2 * x2 - 2 * y2

    );
}

Euler OrientationMatrix::toEuler() const
{
    const Mat3& m = m_toUprightSpace;
    Radian head, pitch, bank;

    float sp = -m[7];
    if (sp <= -1.0f)
    {
        pitch = -HALF_PI;
    }
    else if (sp >= 1.0f)
    {
        pitch = HALF_PI;
    }
    else
    {
        pitch = asin(sp);
    }

    if (abs(sp) > 0.9999f)
    {
        bank = 0.0f;
        head = atan2(-m[2], m[0]);
    }
    else
    {
        head = atan2(m[6], m[8]);
        bank = atan2(m[1], m[4]);
    }

    return Euler(head, pitch, bank);
}

Quaternion OrientationMatrix::toQuaternion() const
{
    // Input matrix:
    const Mat3& m = m_toUprightSpace;

    // Output quaternion:
    float w, x, y, z;

    // Determine which of w, x, y, or z has the largest absolute value
    float fourWSquaredMinus1 = m[0] + m[4] + m[8];
    float fourXSquaredMinus1 = m[0] - m[4] - m[8];
    float fourYSquaredMinus1 = m[4] - m[0] - m[8];
    float fourZSquaredMinus1 = m[8] - m[0] - m[4];

    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;

    // Check which squared value is the largest
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    // Perform square root and division
    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
    float mult = 0.25f / biggestVal;

    // Apply table to compute quaternion values
    switch (biggestIndex)
    {
    case 0:
        w = biggestVal;
        x = (m[5] - m[7]) * mult;
        y = (m[6] - m[2]) * mult;
        z = (m[1] - m[3]) * mult;
        break;
    case 1:
        x = biggestVal;
        w = (m[5] - m[7]) * mult;
        y = (m[1] + m[3]) * mult;
        z = (m[6] + m[2]) * mult;
        break;
    case 2:
        y = biggestVal;
        w = (m[6] - m[2]) * mult;
        x = (m[1] + m[3]) * mult;
        z = (m[5] + m[7]) * mult;
        break;
    case 3:
        z = biggestVal;
        w = (m[1] - m[3]) * mult;
        x = (m[6] + m[2]) * mult;
        y = (m[5] + m[7]) * mult;
        break;
    }
    return Quaternion(w, x, y, z);
}

} // namespace tdm
