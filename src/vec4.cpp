#include "pch.h"

namespace tdm
{

const Vec4 Vec4::Zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

const Vec4 Vec4::Right = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::Left = Vec4(-1.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::Up = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
const Vec4 Vec4::Down = Vec4(0.0f, -1.0f, 0.0f, 0.0f);
const Vec4 Vec4::Forward = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
const Vec4 Vec4::Backward = Vec4(0.0f, 0.0f, -1.0f, 0.0f);

} // namespace tdm
