#pragma once

#include <span>

#include "core/Result.h"

#include "IccFileHeader.h"

class IccProfile
{
public:
	static Result<IccProfile> from_bytes(std::span<const char> bytes);

private:
	IccProfile(const IccFileHeader& header) : header{ header } {}

	IccFileHeader header;
};
