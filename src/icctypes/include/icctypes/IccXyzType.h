#pragma once

#include <cstddef>
#include <span>
#include <vector>

class IccXyzNumber;

class IccXyzType
{
public:
	static bool is_valid(std::span<const char> bytes);

	IccXyzType(std::span<const char> bytes);

	std::size_t get_xyz_number_count() const;
	IccXyzNumber get_xyz_number(std::size_t index) const;

protected:
	std::vector<char> bytes;
};
