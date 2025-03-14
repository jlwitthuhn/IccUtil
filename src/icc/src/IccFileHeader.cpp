#include "IccFileHeader.h"

#include <cstring>
#include <format>

#include "core/Util.h"
#include "icctypes/IccDateTimeNumber.h"
#include "icctypes/IccNumberConverter.h"

#include "Util.h"

Result<IccFileHeader> IccFileHeader::from_bytes(std::span<const char, 128> bytes)
{
	IccFileHeaderRaw header_raw;

	static_assert(sizeof(IccFileHeaderRaw) == 128);
	std::memcpy(&header_raw, bytes.data(), sizeof(IccFileHeaderRaw));

	header_raw.profile_size = util::swapEndianness(header_raw.profile_size);

	return Result<IccFileHeader>{ IccFileHeader{ header_raw } };
}

bool IccFileHeader::is_signature_valid() const
{
	return header_raw.signature == std::array<char, 4>{ 'a', 'c', 's', 'p' };
}

bool IccFileHeader::icc_v4() const
{
	const std::span<const char, 4> version_span = std::span{ header_raw.profile_version };
	return version_span[0] == 4;
}

std::string IccFileHeader::get_preferred_cmm_type_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.preferred_cmm_type });
}

std::string IccFileHeader::get_profile_version_display() const
{
	return util::format_hex(std::span{ header_raw.profile_version });
}

std::string IccFileHeader::get_profile_device_class_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.profile_device_class });
}

std::string IccFileHeader::get_data_color_space_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.data_colour_space });
}

std::string IccFileHeader::get_pcs_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.pcs });
}

std::string IccFileHeader::get_date_time_display() const
{
	const IccDateTimeNumber date_time{ header_raw.date_time };
	return date_time.display_formatted();
}

std::string IccFileHeader::get_signature_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.signature });
}

std::string IccFileHeader::get_primary_platform_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.primary_platform });
}

std::string IccFileHeader::get_profile_flags_display() const
{
	return util::format_hex(std::span{ header_raw.profile_flags });
}

std::string IccFileHeader::get_device_manufacturer_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.device_manufacturer });
}

std::string IccFileHeader::get_device_model_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.device_model });
}

std::string IccFileHeader::get_device_attributes_display() const
{
	return util::format_hex(std::span{ header_raw.device_attributes });
}

std::string IccFileHeader::get_rendering_intent_display() const
{
	std::uint32_t intent_int;
	std::memcpy(&intent_int, header_raw.rendering_intent.data(), header_raw.rendering_intent.size());
	intent_int = util::swapEndianness(intent_int);
	return std::to_string(intent_int);
}

std::string IccFileHeader::get_illuminant_xyz_display() const
{
	const char* const data_begin = reinterpret_cast<const char*>(&(header_raw.illuminant_xyz));
	std::array<char, 4> x_bytes;
	std::array<char, 4> y_bytes;
	std::array<char, 4> z_bytes;
	std::memcpy(&x_bytes, data_begin + 0, 4);
	std::memcpy(&y_bytes, data_begin + 4, 4);
	std::memcpy(&z_bytes, data_begin + 8, 4);

	const double x = IccNumberConverter::from_s15fixed16number(x_bytes);
	const double y = IccNumberConverter::from_s15fixed16number(y_bytes);
	const double z = IccNumberConverter::from_s15fixed16number(z_bytes);

	return std::format("{:0.4f}, {:0.4f}, {:0.4f}", x, y, z);
}

std::string IccFileHeader::get_profile_creator_signature_display() const
{
	return util::format_hex_and_ascii(std::span{ header_raw.profile_creator_signature });
}

std::string IccFileHeader::get_profile_id_display() const
{
	return util::format_hex(std::span{ header_raw.profile_id });
}
