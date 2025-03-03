#include "IccXyzType.h"

#include <array>
#include <cstddef>
#include <cstring>

#include "core/ExitAssert.h"

#include "IccXyzNumber.h"

constexpr std::size_t HEADER_SIZE = 8;

bool IccXyzType::is_valid(const std::span<const char> bytes)
{
	// Header is 8 bytes
	if (bytes.size() < HEADER_SIZE)
	{
		return false;
	}

	// Total size should be 4 bytes for 'XYZ ', 4 bytes of zeros, 12*N bytes for N different XYZ colors
	const std::size_t array_size = bytes.size() - HEADER_SIZE;
	const bool valid_size = (array_size % 12) == 0;
	if (!valid_size)
	{
		return false;
	}

	// Signature should be 'XYZ '
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	return signature == std::array<char, 4>{ 'X', 'Y', 'Z', ' ' };
}

IccXyzType::IccXyzType(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() }
{
	EXIT_ASSERT(is_valid(bytes), "IccXyzType input bytes are not valid");
}

std::size_t IccXyzType::get_xyz_number_count() const
{
	const std::size_t array_size = bytes.size() - HEADER_SIZE;
	EXIT_ASSERT((array_size % 12) == 0, "IccXyzType array size must be a multiple of 12 bytes.");
	return array_size / 12;
}

IccXyzNumber IccXyzType::get_xyz_number(const std::size_t index) const
{
	const std::size_t offset = HEADER_SIZE + index * 12;
	EXIT_ASSERT(bytes.size() >= offset + 12, "Attempting to read beyond IccXyzNumber bounds");
	return IccXyzNumber{ std::span<const char>{ bytes }.subspan(offset).subspan<0, 12>() };
}
