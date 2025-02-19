#include "IccFileHeader.h"

#include <cstddef>
#include <cstring>
#include <format>
#include <sstream>

#include "core/Util.h"

static bool is_printable_ascii(const char input)
{
	return input >= 20 && input < 127;
}

template <std::size_t N>
static std::string format_hex(std::span<const char, N> input)
{
	std::stringstream stream;
	stream << "0x";
	for (const char this_char : input)
	{
		stream << std::format("{:02X}", this_char);
	}
	return stream.str();
}

template <std::size_t N>
static std::string format_hex_and_ascii(std::span<const char, N> input)
{
	bool printable = true;
	for (std::size_t i = 0; i < input.size(); i++)
	{
		printable = printable && is_printable_ascii(input[i]);
	}

	std::string result = format_hex(std::span{ input });
	if (printable)
	{
		result = result + std::format(" ({})", std::string{ input.begin(), input.end() });
	}

	return result;
}

Result<IccFileHeader> IccFileHeader::from_bytes(std::span<const char, 128> bytes)
{
	IccFileHeaderRaw header_raw;

	std::memcpy(&header_raw, bytes.data(), sizeof(IccFileHeaderRaw));

	header_raw.profile_size = util::swapEndianness(header_raw.profile_size);

	return Result<IccFileHeader>{ IccFileHeader{ header_raw } };
}

std::string IccFileHeader::get_preferred_cmm_type_display() const
{
	return format_hex_and_ascii(std::span{ header_raw.preferred_cmm_type });
}

std::string IccFileHeader::get_profile_version_display() const
{
	return format_hex(std::span{ header_raw.profile_version });
}

std::string IccFileHeader::get_profile_device_class_display() const
{
	return format_hex_and_ascii(std::span{ header_raw.profile_device_class });
}

std::string IccFileHeader::get_data_color_space_display() const
{
	return format_hex_and_ascii(std::span{ header_raw.data_colour_space });
}

std::string IccFileHeader::get_pcs_display() const
{
	return format_hex_and_ascii(std::span{ header_raw.pcs });
}
