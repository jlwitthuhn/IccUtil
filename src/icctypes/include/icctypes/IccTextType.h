#pragma once

#include <span>
#include <string>
#include <vector>

class IccTextType
{
public:
	static bool is_valid(std::span<const char> bytes);

	IccTextType(std::span<const char> bytes);

	std::string get_string() const;

protected:
	std::vector<char> bytes;
};
