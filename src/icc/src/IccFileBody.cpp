#include "IccFileBody.h"

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
