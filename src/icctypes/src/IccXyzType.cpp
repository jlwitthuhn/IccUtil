#include "IccXyzType.h"

#include <array>
#include <cstring>

#include "core/ExitAssert.h"

#include "IccXyzNumber.h"

IccXyzType::IccXyzType(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() }
{

}

bool IccXyzType::is_valid_signature() const
{
	EXIT_ASSERT(bytes.size() >= 4, "Not enogh data loaded to check signature");
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	return signature == std::array<char, 4>{ 'X', 'Y', 'Z', ' ' };
}

bool IccXyzType::is_valid_size() const
{
	if (bytes.size() < 8)
	{
		return false;
	}

	// Total size should be 4 bytes for 'XYZ ', 4 bytes of zeros, 12*N bytes for N different XYZ colors
	const std::size_t array_size = bytes.size() - 8;
	return (array_size % 12) == 0;
}

std::size_t IccXyzType::get_xyz_number_count() const
{
	const std::size_t array_size = bytes.size() - 8;
	EXIT_ASSERT((array_size % 12) == 0, "IccXyzType array size must be a multiple of 12 bytes.");
	return array_size / 12;
}

IccXyzNumber IccXyzType::get_xyz_number(const std::size_t index) const
{
	const std::size_t offset = 8 + index * 12;
	EXIT_ASSERT(bytes.size() >= offset + 12, "Attempting to read beyond IccXyzNumber bounds");
	return IccXyzNumber{ std::span<const char>{ bytes }.subspan(offset).subspan<0, 12>() };
}
