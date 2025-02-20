#pragma once

#include <array>
#include <cstdint>
#include <span>

class IccFileTagEntry
{
public:
	IccFileTagEntry(std::span<const char, 12> bytes);

	std::array<char, 4> get_signature() const;
	std::uint32_t get_offset() const;
	std::uint32_t get_size() const;

private:
	std::array<char, 12> bytes;
};
