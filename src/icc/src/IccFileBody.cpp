#include "IccFileBody.h"

#include <cstring>

#include "core/Util.h"

std::uint32_t IccFileBody::get_tag_count() const
{
	std::uint32_t result = 0;
	std::memcpy(&result, bytes.data(), 4);
	result = util::swapEndianness(result);
	return result;
}

IccFileTagEntry IccFileBody::get_tag(const std::uint32_t index) const
{
	const std::size_t offset = 4 + index * 12;
	const std::span<const char> bytes_span{ bytes };
	const std::span<const char, 12> entry_span = bytes_span.subspan(offset, 12).subspan<0, 12>();
	return IccFileTagEntry{ entry_span };
}
