#include "BuildInfo.h"

#include "ExitAssert.h"

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
	EXIT_ASSERT(n <= 40, "Short hash cannot be greater than 40 characters")
	return std::string{ GIT_HASH }.substr(0, n);
#else
	return std::nullopt;
#endif
}
