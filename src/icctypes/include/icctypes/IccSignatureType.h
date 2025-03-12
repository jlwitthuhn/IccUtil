#pragma once

#include <array>
#include <span>
#include <string>

class IccSignatureType
{
public:
	static bool is_valid(std::span<const char> bytes);

	IccSignatureType(std::span<const char> bytes);

	std::array<char, 4> get_signature() const;
	std::string get_signature_str() const;

private:
	std::array<char, 12> bytes;
};
