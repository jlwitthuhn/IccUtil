#include "IccTextDescriptionType.h"

#include <array>
#include <cstdint>
#include <cstring>

#include "core/ExitAssert.h"
#include "core/Util.h"

namespace
{
	constexpr std::size_t ASCII_COUNT_INDEX = 8;
	constexpr std::size_t ASCII_DATA_INDEX = 12;
}

bool IccTextDescriptionType::is_valid(std::span<const char> bytes)
{
	// Minimal data is
	// 4 signature, 4 zeroes, 4 string size, 0 string,
	// 4 language, 4 unicode size, 0 unicode string, 2 scriptcode code, 1 scriptcode size, 67 data
	// = 90 bytes
	// Header is 8 bytes, plus a one byte null character is the smallest valid data
	if (bytes.size() < 90)
	{
		return false;
	}

	// Signature should be 'text'
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	return signature == std::array<char, 4>{ 'd', 'e', 's', 'c' };

	std::uint32_t ascii_count;
	std::memcpy(&ascii_count, bytes.data() + ASCII_COUNT_INDEX, 4);
	ascii_count = util::swapEndianness(ascii_count);

	// After the ascii data segment is unicode metadata
	const std::size_t unicode_lang_index = ASCII_DATA_INDEX + ascii_count;
	const std::size_t unicode_count_index = unicode_lang_index + 4;
	const std::size_t unicode_data_index = unicode_count_index + 4;

	if (unicode_count_index + 4 > bytes.size())
	{
		return false;
	}
	std::uint32_t unicode_count;
	std::memcpy(&unicode_count, bytes.data() + unicode_count_index, 4);
	unicode_count = util::swapEndianness(unicode_count);

	const std::size_t scriptcode_code_index = unicode_data_index + unicode_count * 2;
	const std::size_t mac_desc_count_index = scriptcode_code_index + 2;
	const std::size_t mac_desc_data_index = mac_desc_count_index + 1;

	std::uint8_t mac_desc_count;
	std::memcpy(&mac_desc_count, bytes.data() + mac_desc_count_index, 1);
	if (mac_desc_count > 67)
	{
		return false;
	}

	// Last block of data is always exactly 67 bytes
	if (mac_desc_data_index + 67 != bytes.size())
	{
		return false;
	}

	return true;
}

IccTextDescriptionType::IccTextDescriptionType(const std::span<const char> bytes_in) :
	bytes{ bytes_in.begin(), bytes_in.end() }
{
	EXIT_ASSERT(is_valid(bytes), "IccTextDescriptionType input bytes are not valid");

	std::memcpy(&ascii_count, bytes.data() + ASCII_COUNT_INDEX, 4);
	ascii_count = util::swapEndianness(ascii_count);
	ascii_data_span = std::span{ bytes }.subspan(ASCII_DATA_INDEX, ascii_count);

	const std::size_t unicode_lang_index = ASCII_DATA_INDEX + ascii_count;
	const std::size_t unicode_count_index = unicode_lang_index + 4;
	const std::size_t unicode_data_index = unicode_count_index + 4;

	std::memcpy(&unicode_lang, bytes.data() + unicode_lang_index, 4);
	unicode_lang = util::swapEndianness(unicode_lang);
	std::memcpy(&unicode_count, bytes.data() + unicode_count_index, 4);
	unicode_count = util::swapEndianness(unicode_count);
	unicode_data_span = std::span{ bytes }.subspan(unicode_data_index, unicode_count * 2);

	const std::size_t scriptcode_code_index = unicode_data_index + unicode_count * 2;
	const std::size_t mac_desc_count_index = scriptcode_code_index + 2;
	const std::size_t mac_desc_data_index = mac_desc_count_index + 1;

	std::memcpy(&script_code_code, bytes.data() + scriptcode_code_index, 2);
	script_code_code = util::swapEndianness(script_code_code);
	std::memcpy(&mac_desc_count, bytes.data() + mac_desc_count_index, 1);
	mac_desc_data_span = std::span{ bytes }.subspan(mac_desc_data_index, mac_desc_count);
}

std::string IccTextDescriptionType::get_ascii_string() const
{
	if (ascii_count == 0)
	{
		return "";
	}
	return std::string{ ascii_data_span.begin(), ascii_data_span.end() - 1 };
}

std::vector<char16_t> IccTextDescriptionType::get_unicode_string() const
{
	std::vector<char16_t> result;
	result.resize(unicode_count);
	EXIT_ASSERT(unicode_data_span.size() == unicode_count * 2, "Unicode string is incorrect size");
	std::memcpy(result.data(), unicode_data_span.data(), unicode_data_span.size());
	for (char16_t& this_char : result)
	{
		this_char = util::swapEndianness(this_char);
	}
	return result;
}

std::vector<char> IccTextDescriptionType::get_mac_desc_string() const
{
	const uint8_t count = get_mac_desc_count();
	EXIT_ASSERT(count == mac_desc_data_span.size(), "IccTextDescriptionType mac string has two different sizes");
	std::vector<char> result;
	result.resize(count);
	std::memcpy(result.data(), mac_desc_data_span.data(), mac_desc_data_span.size());
	return result;
}
