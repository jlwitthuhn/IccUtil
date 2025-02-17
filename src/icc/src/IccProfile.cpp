#include "IccProfile.h"

#include "core/Error.h"

Result<IccProfile> IccProfile::from_bytes(const std::span<const char> bytes)
{
	if (bytes.size() < 132)
	{
		return Result<IccProfile>{ Error{ "File must be at least 132 bytes (header + tag count)" } };
	}
	const Result<IccFileHeader> header = IccFileHeader::from_bytes(bytes.subspan<0, 128>());
	if (!header)
	{
		return Result<IccProfile>{ Error{ std::string{ "Failed to parse header: " } + header.error().message } };
	}

	return Result{ IccProfile{ header.get() } };
}
