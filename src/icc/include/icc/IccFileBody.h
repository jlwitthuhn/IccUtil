#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "IccFileTagEntry.h"

class IccFileBody
{
public:
	IccFileBody(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() } {}

	std::size_t size() const { return bytes.size(); }

	std::uint32_t get_tag_count() const;
	IccFileTagEntry get_tag(std::uint32_t index) const;
	std::optional<IccFileTagEntry> get_tag(const std::string& signature) const;

	std::span<const char> get_tag_bytes(std::uint32_t index) const;
	std::span<const char> get_tag_bytes(const std::string& tag_signature) const;

private:
	std::uint32_t get_local_offset(std::uint32_t file_offset) const;

	std::vector<char> bytes;
};
