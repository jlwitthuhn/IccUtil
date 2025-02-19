#include "IccProfile.h"

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

	return Result{ IccProfile{ header_result.get() } };
}
