#include "IccMultiLocalizedUnicodeType.h"

#include <array>
#include <cstring>

#include "core/ExitAssert.h"
#include "core/Util.h"

constexpr std::size_t HEADER_SIZE = 16;
constexpr std::size_t RECORD_SIZE = 12;

bool IccMultiLocalizedUnicodeType::is_valid(std::span<const char> bytes)
{
	if (bytes.size() < HEADER_SIZE)
	{
		return false;
	}

	// Signature should be 'mluc'
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	if (signature != std::array<char, 4>{ 'm', 'l', 'u', 'c' })
	{
		return false;
	}

	// Record size (offset 12) should be 12
	std::uint32_t record_size;
	std::memcpy(&record_size, bytes.data() + 12, 4);
	record_size = util::swapEndianness(record_size);
	if (record_size != RECORD_SIZE)
	{
		return false;
	}

	// Get the total number of records
	std::uint32_t record_count;
	std::memcpy(&record_count, bytes.data() + 8, 4);
	record_count = util::swapEndianness(record_count);

	// Total size should be at least (HEADER_SIZE + RECORD_SIZE * record_count)
	if (bytes.size() < HEADER_SIZE + RECORD_SIZE * static_cast<std::size_t>(record_count))
	{
		return false;
	}

	return true;
}

IccMultiLocalizedUnicodeType::IccMultiLocalizedUnicodeType(std::span<const char> bytes) : bytes{ bytes.begin(), bytes.end() }
{

}

std::uint32_t IccMultiLocalizedUnicodeType::record_count() const
{
	std::uint32_t record_count;
	std::memcpy(&record_count, bytes.data() + 8, 4);
	return util::swapEndianness(record_count);
}

IccMultiLocalizedUnicodeRecord IccMultiLocalizedUnicodeType::get_record(const std::uint32_t index) const
{
	EXIT_ASSERT(HEADER_SIZE + RECORD_SIZE * (index + 1) <= bytes.size(), "Index exceeds bounds of available data");
	const std::size_t start_index = HEADER_SIZE + RECORD_SIZE * static_cast<std::size_t>(index);
	const char* const record_start = bytes.data() + start_index;
	const std::string lang{ record_start, 2 };
	const std::string country{ record_start + 2, 2 };
	std::uint32_t length;
	std::memcpy(&length, record_start + 4, 4);
	std::uint32_t offset;
	std::memcpy(&offset, record_start + 8, 4);

	return IccMultiLocalizedUnicodeRecord{ lang, country, util::swapEndianness(length), util::swapEndianness(offset) };
}

std::vector<char16_t> IccMultiLocalizedUnicodeType::get_string(const IccMultiLocalizedUnicodeRecord& record) const
{
	const std::uint32_t length = record.str_length;
	EXIT_ASSERT(length % 2 == 0, "UTF-16 string must be a multiple of 2 bytes");
	const std::uint32_t offset = record.str_offset;
	EXIT_ASSERT(offset + length <= bytes.size(), "String exceeds bounds of available data");
	std::vector<char16_t> result;
	result.resize(length / 2);
	std::memcpy(result.data(), bytes.data() + offset, length);
	for (char16_t& this_codepoint : result)
	{
		this_codepoint = util::swapEndianness(this_codepoint);
	}
	return result;
}
