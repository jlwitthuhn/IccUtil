#include "IccTextType.h"

#include <array>
#include <cstddef>
#include <cstring>

#include "core/ExitAssert.h"

constexpr std::size_t HEADER_SIZE = 8;

bool IccTextType::is_valid(const std::span<const char> bytes)
{
	// Header is 8 bytes, plus a one byte null character is the smallest valid data
	if (bytes.size() < (HEADER_SIZE + 1))
	{
		return false;
	}

	// Last byte must be null
	if (bytes[bytes.size() - 1] != 0)
	{
		return false;
	}

	// Signature should be 'text'
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	return signature == std::array<char, 4>{ 't', 'e', 'x', 't' };
}

IccTextType::IccTextType(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() }
{
	EXIT_ASSERT(is_valid(bytes), "IccTextType input bytes are not valid");
}

std::string IccTextType::get_string() const
{
	return std::string{ bytes.data() + 8, bytes.size() - 9 }; // -9 because last character is null
}
