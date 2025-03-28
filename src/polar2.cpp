#include "polar2.h"

namespace tdm
{

// this algorithm is from the 3D Math Primer book.
void Polar2::makeCanonical()
{
    float r = m_radius;
    float heading = m_heading.valueRadians();

    // Check if we are exactly at the origin
    if (r == 0.0f)
    {
        // At the origin – slam angles to zero
        heading = 0.0f;
    }
    else
    {
        // Handle negative distance
        if (r < 0.0f)
        {
            r = -r;
            heading += PI;
        }

        // Theta out of range? Note that this if() check is not
        // strictly necessary, but we try to avoid doing floating
        // point operations if they aren't necessary. Why
        // incur floating point precision loss if we don't
        // need to?

        if (abs(heading) > PI)
        {

            // Offset by PI
            heading += PI;

            // Wrap in range 0 ... TWOPI
            heading -= floor(heading / TWO_PI) * TWO_PI;

            // Undo offset, shifting angle back in range −PI ... PI
            heading -= PI;
        }
    }
    m_radius = r;
    m_heading = Radian(heading);
}

} // namespace tdm
