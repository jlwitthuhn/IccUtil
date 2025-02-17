#pragma once

#include <span>

#include "core/Result.h"

class IccFileHeader
{
public:
	static Result<IccFileHeader> from_bytes(std::span<const char, 128> bytes);
};
