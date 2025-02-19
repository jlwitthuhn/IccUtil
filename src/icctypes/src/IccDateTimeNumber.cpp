#include "IccDateTimeNumber.h"

#include <cstring>
#include <format>

#include "core/Util.h"

IccDateTimeNumber::IccDateTimeNumber(const std::span<const char, 12> bytes)
{
	std::memcpy(data.data(), bytes.data(), bytes.size());

	for (std::size_t i = 0; i < data.size(); i++)
	{
		data[i] = util::swapEndianness(data[i]);
	}
}

std::string IccDateTimeNumber::display_formatted() const
{
	return std::format("{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}", get_year(), get_month(), get_day(), get_hours(), get_minutes(), get_seconds());
}
