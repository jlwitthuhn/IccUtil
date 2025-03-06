#include "IccXyzNumber.h"

#include <cstring>

#include "IccNumberConverter.h"

IccXyzNumber::IccXyzNumber(std::span<const char, 12> xyz)
{
	std::memcpy(_x.data(), xyz.data() + 0, 4);
	std::memcpy(_y.data(), xyz.data() + 4, 4);
	std::memcpy(_z.data(), xyz.data() + 8, 4);
}

double IccXyzNumber::x() const
{
	return IccNumberConverter::from_s15fixed16number(_x);
}

double IccXyzNumber::y() const
{
	return IccNumberConverter::from_s15fixed16number(_y);
}

double IccXyzNumber::z() const
{
	return IccNumberConverter::from_s15fixed16number(_z);
}
