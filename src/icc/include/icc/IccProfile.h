#pragma once

#include <span>

#include "core/Result.h"

#include "IccFileBody.h"
#include "IccFileHeader.h"

class IccProfile
{
public:
	static Result<IccProfile> from_bytes(std::span<const char> bytes);

	const IccFileHeader& get_header() const { return header; }
	const IccFileBody& get_body() const { return body; }

private:
	IccProfile(const IccFileHeader& header, const IccFileBody& body) : header{ header }, body{ body } {}

	IccFileHeader header;
	IccFileBody body;
};
