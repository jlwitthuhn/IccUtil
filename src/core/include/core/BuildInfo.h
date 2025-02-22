#pragma once

#include <cstddef>
#include <optional>
#include <string>

namespace BuildInfo
{
	std::optional<std::string> git_hash();
	std::optional<std::string> git_short_hash(std::size_t n = 8);
}
