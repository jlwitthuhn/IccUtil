#include "ExitAssert.h"

#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <mutex>
#include <optional>
#include <sstream>
#include <utility>

#include "BuildInfo.h"

static std::mutex mutex_callback;
static std::function<void(const std::string&)> assert_callback;

void ExitAssert::assert_failed(const char* file, int line, const char* msg)
{
	std::stringstream stream;

	stream << "Fatal error:" << "\n";
	stream << msg << "\n";
	if (const std::optional<std::string> short_hash = BuildInfo::git_short_hash())
	{
		stream << "Git: " << *short_hash << "\n";
	}

	const std::filesystem::path file_path{ file };
	stream << file_path.filename() << ", L" << std::to_string(line);

	std::cerr << stream.str() << std::endl; // NOLINT(performance-avoid-endl)

	const std::lock_guard<std::mutex> lock{ mutex_callback };
	if (assert_callback)
	{
		assert_callback(stream.str());
	}

	std::exit(1);
}

void ExitAssert::set_assert_callback(std::function<void(const std::string&)> callback)
{
	const std::lock_guard<std::mutex> lock{ mutex_callback };
	assert_callback = std::move(callback);
}
