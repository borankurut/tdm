#include "euler.h"

namespace tdm
{

// this algorithm is from the 3D Math Primer book.
void Euler::makeCanonical()
{
    // First, wrap all angles into (-PI, PI]
    m_head = wrapPi(m_head);
    m_pitch = wrapPi(m_pitch);
    m_bank = wrapPi(m_bank);

    // Ensure pitch is in the canonical range [-HALF_PI, HALF_PI].
    // If pitch is out of that range, we flip the sign and adjust head and bank.
    if (m_pitch.valueRadians() > HALF_PI)
    {
        // Flip pitch: new_pitch = PI - pitch
        m_pitch = Radian(PI - m_pitch.valueRadians());
        // Adjust head and bank by 180 degrees
        m_head = wrapPi(Radian(m_head.valueRadians() + PI));
        m_bank = wrapPi(Radian(m_bank.valueRadians() + PI));
    }
    else if (m_pitch.valueRadians() < -HALF_PI)
    {
        // Flip pitch: new_pitch = -PI - pitch
        m_pitch = Radian(-PI - m_pitch.valueRadians());
        // Adjust head and bank by 180 degrees
        m_head = wrapPi(Radian(m_head.valueRadians() + PI));
        m_bank = wrapPi(Radian(m_bank.valueRadians() + PI));
    }

    // Handle gimbal lock: when pitch is nearly ±HALF_PI, bank is redundant.
    if (tdm::abs(tdm::abs(m_pitch.valueRadians()) - HALF_PI) < EPSILON_7)
    {
        // Absorb bank into head and zero out bank.
        m_head = wrapPi(Radian(m_head.valueRadians() + m_bank.valueRadians()));
        m_bank = Radian(0.0f);
    }
}

} // namespace tdm
