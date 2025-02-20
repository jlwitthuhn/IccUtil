#include "IccNumberConverter.h"

#include <cstdint>
#include <cstring>

double IccNumberConverter::from_s15fixed16number(const std::span<char, 4> bytes)
{
	std::uint16_t whole = 0;
	std::uint16_t frac = 0;
	std::memcpy(&whole, bytes.data() + 2, 2);
	std::memcpy(&frac, bytes.data(), 2);
	return static_cast<double>(whole) + static_cast<double>(frac) / (1 << 16);
}
