#pragma once

#include <cstddef>
#include <span>
#include <vector>

class IccXyzNumber;

class IccXyzType
{
public:
	IccXyzType(std::span<const char> bytes);

	bool is_valid_signature() const;
	bool is_valid_size() const;

	std::size_t get_xyz_number_count() const;
	IccXyzNumber get_xyz_number(std::size_t index) const;

protected:
	std::vector<char> bytes;
};
