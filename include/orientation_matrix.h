#pragma once
#include "mat3.h"

namespace tdm
{

class OrientationMatrix
{
public:
    OrientationMatrix(const Vec3& pToUprightSpace, const Vec3& qToUprightSpace, const Vec3& rToUprightSpace)
    {
        m_toUprightSpace.setRow(0, pToUprightSpace);
        m_toUprightSpace.setRow(1, qToUprightSpace);
        m_toUprightSpace.setRow(2, rToUprightSpace);

        assert(m_toUprightSpace.isOrthogonal());
    }

    OrientationMatrix(const Mat3& toUprightSpace) : m_toUprightSpace(toUprightSpace)
    {
        assert(m_toUprightSpace.isOrthogonal());
    }

    void convertToUprightSpace(Vec3& vec) const { vec = vec * m_toUprightSpace; }
    void convertToObjectSpace(Vec3& vec) const { vec = vec * m_toUprightSpace.transpose(); }

    friend std::ostream& operator<<(std::ostream& os, const OrientationMatrix& orientationMatrix)
    {
        os << orientationMatrix.m_toUprightSpace;
        return os;
    }

    Mat3 getToUprightSpace() const { return m_toUprightSpace; }
    Mat3 getToObjectSpace() const { return m_toUprightSpace.transpose(); }

private:
    Mat3 m_toUprightSpace;
};

} // namespace tdm
