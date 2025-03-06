#include "IccFileBody.h"

#include <array>
#include <cstring>

#include "core/ExitAssert.h"
#include "core/Util.h"

std::uint32_t IccFileBody::get_tag_count() const
{
	EXIT_ASSERT(bytes.size() >= 4, "Tag header is too small to contain a size");
	std::uint32_t result = 0;
	std::memcpy(&result, bytes.data(), 4);
	result = util::swapEndianness(result);
	return result;
}

IccFileTagEntry IccFileBody::get_tag(const std::uint32_t index) const
{
	const std::size_t offset = 4 + index * 12;
	EXIT_ASSERT(offset + 12 < bytes.size(), "Attempted to index out-of-range tag");
	const std::span<const char> bytes_span{ bytes };
	const std::span<const char, 12> entry_span = bytes_span.subspan(offset, 12).subspan<0, 12>();
	return IccFileTagEntry{ entry_span };
}

std::optional<IccFileTagEntry> IccFileBody::get_tag(const std::string& signature) const
{
	for (std::uint32_t i = 0; i < get_tag_count(); i++)
	{
		const IccFileTagEntry this_entry = get_tag(i);
		const std::array<char, 4> signature_array = this_entry.get_signature();
		const std::string signature_str{ signature_array.begin(), signature_array.end() };
		if (signature_str == signature)
		{
			return this_entry;
		}
	}
	EXIT_ASSERT(false, "IccFileBody::get_tag called with tag that is not present");
}

std::span<const char> IccFileBody::get_tag_bytes(const std::uint32_t index) const
{
	const IccFileTagEntry tag_entry = get_tag(index);
	const std::uint32_t file_offset = tag_entry.get_offset();
	const std::uint32_t offset = get_local_offset(file_offset);
	const std::uint32_t length = tag_entry.get_size();
	EXIT_ASSERT(offset + length <= bytes.size(), "Tag data must be inside bounds of profile body");
	return std::span<const char>{ bytes }.subspan(offset, length);
}

std::span<const char> IccFileBody::get_tag_bytes(const std::string& tag_signature) const
{
	const std::optional<IccFileTagEntry> tag_entry = get_tag(tag_signature);
	if (!tag_entry)
	{
		return {};
	}
	const std::uint32_t file_offset = tag_entry->get_offset();
	const std::uint32_t offset = get_local_offset(file_offset);
	const std::uint32_t length = tag_entry->get_size();
	EXIT_ASSERT(offset + length <= bytes.size(), "Tag data must be inside bounds of profile body");
	return std::span<const char>{ bytes }.subspan(offset, length);
}

std::uint32_t IccFileBody::get_local_offset(std::uint32_t file_offset) const
{
	EXIT_ASSERT(file_offset > 127, "Tag data must be inside bounds of profile body");
	return file_offset - 128;
}
