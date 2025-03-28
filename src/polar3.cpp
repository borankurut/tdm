#include "polar3.h"

namespace tdm
{

// this algorithm is from the 3D Math Primer book.
void Polar3::makeCanonical()
{
    float r = m_radius;
    float heading = m_heading.valueRadians();
    float pitch = m_pitch.valueRadians();

    // Check if we are exactly at the origin
    if (r == 0.0f)
    {
        // At the origin – slam angles to zero
        heading = pitch = 0.0f;
    }
    else
    {
        // Handle negative distance
        if (r < 0.0f)
        {
            r = -r;
            heading += PI;
            pitch = -pitch;
        }

        // Pitch out of range?
        if (abs(pitch) > HALF_PI)
        {
            // Offset by 90 degrees
            pitch += HALF_PI;
            // Wrap in range 0 ... TWOPI
            pitch -= floor(pitch / TWO_PI) * TWO_PI;
            // Out of range?
            if (pitch > PI)
            {
                // Flip heading
                heading += PI;
                // Undo offset and also set pitch = 180 - pitch
                pitch = 3.0f * PI / 2.0f - pitch; // p = 270 degrees - p
            }
            else
            {
                // Undo offset, shifting pitch in range -90 ... +90 degrees
                pitch -= HALF_PI;
            }
        }

        // Gimbal lock? Test using a relatively small tolerance
        // (close to the limits of single precision).
        if (abs(pitch) >= HALF_PI * 0.9999f)
        {
            heading = 0.0f;
        }
        else
        {
            // Wrap heading, avoiding math when possible to preserve precision
            if (abs(heading) > PI)
            {
                // Offset by PI
                heading += PI;
                // Wrap in range 0 ... TWOPI
                heading -= floor(heading / TWO_PI) * TWO_PI;
                // Undo offset, shifting angle back in range -PI ... PI
                heading -= PI;
            }
        }
    }
    m_radius = r;
    m_heading = Radian(heading);
    m_pitch = Radian(pitch);
}

} // namespace tdm
