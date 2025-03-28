#pragma once
#include "common_math.h"

namespace tdm
{

class Euler
{
public:
    Euler(Radian head, Radian pitch, Radian bank) : m_head(head), m_pitch(pitch), m_bank(bank) { makeCanonical(); }

    const Radian& head() const { return m_head; }
    const Radian& pitch() const { return m_pitch; }
    const Radian& bank() const { return m_bank; }

    friend std::ostream& operator<<(std::ostream& os, const Euler& euler)
    {
        os << "[Head: " << euler.m_head << ", pitch: " << euler.m_pitch << ", bank: " << euler.m_bank << "]";
        return os;
    }

private:
    Radian m_head;
    Radian m_pitch;
    Radian m_bank;

    void makeCanonical();
};

} // namespace tdm
