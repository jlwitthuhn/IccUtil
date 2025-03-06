#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

class IccMultiLocalizedUnicodeRecord
{
public:
	IccMultiLocalizedUnicodeRecord(const std::string& lang, const std::string& country, std::uint32_t str_length, std::uint32_t str_offset) :
		lang{ lang },
		country{ country },
		str_length{ str_length },
		str_offset{ str_offset }
		{}

	std::string lang;
	std::string country;
	std::uint32_t str_length;
	std::uint32_t str_offset;
};

class IccMultiLocalizedUnicodeType
{
public:

	static bool is_valid(std::span<const char> bytes);

	IccMultiLocalizedUnicodeType(std::span<const char> bytes);

	std::uint32_t record_count() const;
	IccMultiLocalizedUnicodeRecord get_record(std::uint32_t index) const;
	std::vector<char16_t> get_string(const IccMultiLocalizedUnicodeRecord& record) const;


private:
	std::vector<char> bytes;
};
