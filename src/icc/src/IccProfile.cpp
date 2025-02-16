#include "IccProfile.h"

Result<IccProfile> IccProfile::from_bytes(const std::span<const char> bytes)
{
	return Result<IccProfile>{ Error{ 1, "Not implemented"} };
}
