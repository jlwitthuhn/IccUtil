#include "BuildInfo.h"

#include <format>

std::string BuildInfo::build_date()
{
	std::string result{ __DATE__ };
	const size_t fix_index = result.find("  ");
	if (fix_index != std::string::npos)
	{
		result.at(fix_index + 1) = '0';
	}
	return result;
}

#if !defined(_MSC_FULL_VER) && !defined(__clang_version__) && !defined(__GNUC__)
[[deprecated]]
static std::string get_default_compiler_string()
{
	return "Unknown Compiler";
}
#endif

std::string BuildInfo::compiler_version()
{
#if defined(_MSC_FULL_VER)
	return std::format("MSVC {}", _MSC_FULL_VER);
#elif defined(__clang_version__) && defined(__apple_build_version__)
	return std::format("Apple Clang {}", __clang_version__);
#elif defined(__clang_version__)
	return std::format("Clang {}", __clang_version__);
#elif defined(__GNUC__)
	return std::format("GCC {}.{}.{}", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
	return get_default_compiler_string();
#endif
}

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
	(void)n;
	return std::nullopt;
#endif
}
