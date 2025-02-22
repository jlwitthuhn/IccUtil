#include "BuildInfo.h"

std::optional<std::string> BuildInfo::git_hash()
{
#ifdef GIT_HASH
	return std::string{ GIT_HASH };
#else
	return std::nullopt;
#endif
}

std::optional<std::string> BuildInfo::git_short_hash(const std::size_t n)
{
#ifdef GIT_HASH
	const std::string full_hash{ GIT_HASH };
	if (n >= full_hash.size())
	{
		return full_hash;
	}
	else
	{
		return std::string{ GIT_HASH }.substr(0, n);
	}
#else
	return std::nullopt;
#endif
}
