#include "IccNumberConverter.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <ranges>

#include "core/Util.h"

double IccNumberConverter::from_s15fixed16number(std::span<const char, 4> bytes)
{
	std::array<char, 4> bytes_var;
	std::ranges::copy(bytes, bytes_var.begin());
	bytes_var = util::swapEndianness(bytes_var);
	std::uint16_t whole = 0;
	std::uint16_t frac = 0;
	std::memcpy(&whole, bytes_var.data() + 2, 2);
	std::memcpy(&frac, bytes_var.data(), 2);
	return static_cast<double>(whole) + static_cast<double>(frac) / (1 << 16);
}
