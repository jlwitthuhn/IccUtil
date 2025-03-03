#pragma once

#include <span>
#include <vector>

class IccMultiLocalizedUnicodeType
{
public:

	static bool is_valid(std::span<const char> bytes);

	IccMultiLocalizedUnicodeType(std::span<const char> bytes);

private:
	std::vector<char> bytes;
};
