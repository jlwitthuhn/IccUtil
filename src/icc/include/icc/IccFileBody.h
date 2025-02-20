#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "IccFileTagEntry.h"

class IccFileBody
{
public:
	IccFileBody(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() } {}

	std::size_t size() const { return bytes.size(); }

	std::uint32_t get_tag_count() const;
	IccFileTagEntry get_tag(std::uint32_t index) const;

private:
	std::vector<char> bytes;
};
