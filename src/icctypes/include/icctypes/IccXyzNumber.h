#pragma once

#include <array>
#include <span>

class IccXyzNumber
{
public:
	IccXyzNumber(std::span<const char, 12> xyz);

	double x() const;
	double y() const;
	double z() const;

protected:
	std::array<char, 4> _x;
	std::array<char, 4> _y;
	std::array<char, 4> _z;
};
