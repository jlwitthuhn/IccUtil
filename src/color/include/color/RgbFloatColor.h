#pragma once

#include <cstdint>

class RgbFloatColor
{
public:
	RgbFloatColor(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}

	RgbFloatColor scaled() const;

	uint8_t r_byte() const;
	uint8_t g_byte() const;
	uint8_t b_byte() const;

	float r;
	float g;
	float b;
};
