#include "vec3.h"

namespace tdm
{

Vec3 Vec3::Zero = Vec3(0.0f, 0.0f, 0.0f);

Vec3 Vec3::Right = Vec3(1.0f, 0.0f, 0.0f);
Vec3 Vec3::Left = Vec3(-1.0f, 0.0f, 0.0f);
Vec3 Vec3::Up = Vec3(0.0f, 1.0f, 0.0f);
Vec3 Vec3::Down = Vec3(0.0f, -1.0f, 0.0f);
Vec3 Vec3::Forward = Vec3(0.0f, 0.0f, 1.0f);
Vec3 Vec3::Backward = Vec3(0.0f, 0.0f, -1.0f);

} // namespace tdm
