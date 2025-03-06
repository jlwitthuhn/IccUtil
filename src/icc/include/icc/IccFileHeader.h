#pragma once

#include <array>
#include <cstdint>
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
	std::array<char, 12> date_time;
	std::array<char, 4> signature;
	std::array<char, 4> primary_platform;
	std::array<char, 4> profile_flags;
	std::array<char, 4> device_manufacturer;
	std::array<char, 4> device_model;
	std::array<char, 8> device_attributes;
	std::array<char, 4> rendering_intent;
	std::array<char, 12> illuminant_xyz;
	std::array<char, 4> profile_creator_signature;
	std::array<char, 16> profile_id;
	std::array<char, 28> unused;
};

class IccFileHeader
{
public:
	static Result<IccFileHeader> from_bytes(std::span<const char, 128> bytes);

	bool is_signature_valid() const;

	bool icc_v4() const;

	std::uint32_t get_profile_size() const { return header_raw.profile_size; }
	std::string get_preferred_cmm_type_display() const;
	std::string get_profile_version_display() const;
	std::string get_profile_device_class_display() const;
	std::string get_data_color_space_display() const;
	std::string get_pcs_display() const;
	std::string get_date_time_display() const;
	std::string get_signature_display() const;
	std::string get_primary_platform_display() const;
	std::string get_profile_flags_display() const;
	std::string get_device_manufacturer_display() const;
	std::string get_device_model_display() const;
	std::string get_device_attributes_display() const;
	std::string get_rendering_intent_display() const;
	std::string get_illuminant_xyz_display() const;
	std::string get_profile_creator_signature_display() const;
	std::string get_profile_id_display() const;

private:
	IccFileHeader(IccFileHeaderRaw header_raw) : header_raw{ header_raw } {}

	IccFileHeaderRaw header_raw;
};
