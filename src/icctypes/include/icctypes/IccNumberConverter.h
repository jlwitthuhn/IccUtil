#pragma once

#include <span>

class IccNumberConverter
{
public:
	static double from_s15fixed16number(std::span<const char, 4> bytes);
};
