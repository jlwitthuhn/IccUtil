#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <span>
#include <string>

#include "core/Result.h"

struct IccFileHeaderRaw
{
	std::uint32_t profile_size;
	std::array<char, 4> preferred_cmm_type;
	std::array<char, 4> profile_version;
	std::array<char, 4> profile_device_class;
	std::array<char, 4> data_colour_space;
	std::array<char, 4> pcs;
	std::array<char, 104> unused;
};

static_assert(sizeof(IccFileHeaderRaw) == 128);

class IccFileHeader
{
public:
	static Result<IccFileHeader> from_bytes(std::span<const char, 128> bytes);

	std::uint32_t get_profile_size() const { return header_raw.profile_size; }
	std::string get_preferred_cmm_type_display() const;
	std::string get_profile_version_display() const;
	std::string get_profile_device_class_display() const;
	std::string get_data_color_space_display() const;
	std::string get_pcs_display() const;

private:
	IccFileHeader(IccFileHeaderRaw header_raw) : header_raw{ header_raw } {}

	IccFileHeaderRaw header_raw;
};
