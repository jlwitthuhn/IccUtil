#pragma once

#include <span>

#include "core/Result.h"

class IccProfile
{
public:
	static Result<IccProfile> from_bytes(std::span<const char> bytes);
};
