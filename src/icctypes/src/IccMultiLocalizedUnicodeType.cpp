#include "IccMultiLocalizedUnicodeType.h"

#include <array>

constexpr std::size_t HEADER_SIZE = 16;

bool IccMultiLocalizedUnicodeType::is_valid(std::span<const char> bytes)
{
	if (bytes.size() < HEADER_SIZE)
	{
		return false;
	}

	// Signature should be 'mluc'
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	return signature == std::array<char, 4>{ 'm', 'l', 'u', 'c' };
}
