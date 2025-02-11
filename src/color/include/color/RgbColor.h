#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <type_traits>

template <typename T>
class RgbColor
{
private:
	static T clamp(T in, T min, T max)
	{
		return std::min(max, std::max(min, in));
	}

public:
	RgbColor(T r, T g, T b) : r{ r }, g{ g }, b{ b } {}

	uint8_t r_byte() const
	{
		return static_cast<uint8_t>(clamp(r, 0.0, 1.0) * UINT8_MAX);
	}
	uint8_t g_byte() const
	{
		return static_cast<uint8_t>(clamp(g, 0.0, 1.0) * UINT8_MAX);
	}
	uint8_t b_byte() const
	{
		return static_cast<uint8_t>(clamp(b, 0.0, 1.0) * UINT8_MAX);
	}

	T r;
	T g;
	T b;
};
