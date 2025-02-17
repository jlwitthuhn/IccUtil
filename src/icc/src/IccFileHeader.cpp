#include "IccFileHeader.h"

Result<IccFileHeader> IccFileHeader::from_bytes(std::span<const char, 128> bytes)
{
	return Result<IccFileHeader>{ Error{ "Not implemented" } };
}
