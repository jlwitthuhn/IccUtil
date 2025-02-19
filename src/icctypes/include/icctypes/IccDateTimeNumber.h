#pragma once

#include <array>
#include <cstdint>
#include <span>
#include <string>

class IccDateTimeNumber
{
public:
	IccDateTimeNumber(std::span<const char, 12> bytes);

	std::uint16_t get_year() const { return data[0]; }
	std::uint16_t get_month() const { return data[1]; }
	std::uint16_t get_day() const { return data[2]; }
	std::uint16_t get_hours() const { return data[3]; }
	std::uint16_t get_minutes() const { return data[4]; }
	std::uint16_t get_seconds() const { return data[5]; }

	std::string display_formatted() const;

protected:
	std::array<std::uint16_t, 6> data;
};
