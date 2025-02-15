#include "RgbFloatColor.h"

#include <algorithm>

static float clamp(float in, float min, float max)
{
	return std::min(max, std::max(min, in));
}

RgbFloatColor RgbFloatColor::scaled() const
{
	const float max = std::max(r, std::max(g, b));
	return RgbFloatColor{ r / max, g / max, b / max };
}

uint8_t RgbFloatColor::r_byte() const
{
	return static_cast<uint8_t>(clamp(r, 0.0, 1.0) * UINT8_MAX);
}
uint8_t RgbFloatColor::g_byte() const
{
	return static_cast<uint8_t>(clamp(g, 0.0, 1.0) * UINT8_MAX);
}
uint8_t RgbFloatColor::b_byte() const
{
	return static_cast<uint8_t>(clamp(b, 0.0, 1.0) * UINT8_MAX);
}
