#include "IccSignatureType.h"

#include <cstring>

#include "core/ExitAssert.h"

bool IccSignatureType::is_valid(const std::span<const char> bytes)
{
	if (bytes.size() != 12)
	{
		return false;
	}

	// Signature should be 'sig '
	std::array<char, 4> signature;
	std::memcpy(signature.data(), bytes.data(), 4);
	if(signature != std::array<char, 4>{ 's', 'i', 'g', ' ' })
	{
		return false;
	}

	return true;
}

IccSignatureType::IccSignatureType(const std::span<const char> bytes)
{
	EXIT_ASSERT(is_valid(bytes), "IccSignatureType input bytes are not valid");
	std::memcpy(this->bytes.data(), bytes.data(), 12);
}

std::array<char, 4> IccSignatureType::get_signature() const
{
	std::array<char, 4> result;
	std::memcpy(result.data(), bytes.data() + 8, 4);
	return result;
}

std::string IccSignatureType::get_signature_str() const
{
	const std::array<char, 4> signature = get_signature();
	return std::string{ signature.data(), signature.size() };
}
