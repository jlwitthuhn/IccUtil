#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

class IccTextDescriptionType
{
public:
	static bool is_valid(std::span<const char> bytes);

	IccTextDescriptionType(std::span<const char> bytes);

	std::uint32_t get_ascii_count() const { return ascii_count; }
	std::string get_ascii_string() const;
	std::uint32_t get_unicode_lang() const { return unicode_lang; }
	std::uint32_t get_unicode_count() const { return unicode_count; }
	std::vector<char16_t> get_unicode_string() const;
	std::uint16_t get_script_code_code() const { return script_code_code; }
	std::uint8_t get_mac_desc_count() const { return mac_desc_count; }
	std::vector<char> get_mac_desc_string() const;

protected:
	std::vector<char> bytes;
	std::uint32_t ascii_count = 0;
	std::span<const char> ascii_data_span;
	std::uint32_t unicode_lang = 0;
	std::uint32_t unicode_count = 0;
	std::span<const char> unicode_data_span;
	std::uint16_t script_code_code = 0;
	std::uint8_t mac_desc_count = 0;
	std::span<const char> mac_desc_data_span;
};
