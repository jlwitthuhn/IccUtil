#include "IccProfile.h"

#include <string>

#include "core/Error.h"

Result<IccProfile> IccProfile::from_bytes(const std::span<const char> bytes)
{
	if (bytes.size() < 132)
	{
		return Result<IccProfile>{ Error{ "File must be at least 132 bytes (header + tag count)" } };
	}
	const Result<IccFileHeader> header_result = IccFileHeader::from_bytes(bytes.subspan<0, 128>());
	if (!header_result)
	{
		return Result<IccProfile>{ Error{ std::string{ "Failed to parse header: " } + header_result.error().message } };
	}

	const IccFileHeader& header = header_result.get();
	if (!header.is_signature_valid())
	{
		return Result<IccProfile>{ Error{ "File does not have a valid ICC signature" } };
	}

	const IccFileBody body{ bytes.subspan(128) };
	if (body.size() < body.get_tag_count() * 12 + 4) // 12 bytes per tag plus 4 for the tag count
	{
		return Result<IccProfile>{ Error{ "Tag table is incomplete" } };
	}

	return Result{ IccProfile{ header, body } };
}

bool IccProfile::icc_v4() const
{
	return header.icc_v4();
}
