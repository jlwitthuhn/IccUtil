#include "IccFileTagEntry.h"

#include <cstring>

#include "core/Util.h"

IccFileTagEntry::IccFileTagEntry(const std::span<const char, 12> bytes)
{
	std::memcpy(this->bytes.data(), bytes.data() + 0, 12);
}

std::array<char, 4> IccFileTagEntry::get_signature() const
{
	std::array<char, 4> result;
	std::memcpy(result.data(), bytes.data(), 4);
	return result;
}


std::uint32_t IccFileTagEntry::get_size() const
{
	std::uint32_t result;
	std::memcpy(&result, this->bytes.data() + 8, 4);
	return util::swapEndianness(result);
}
