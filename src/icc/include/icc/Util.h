#pragma once

#include <cstddef> 
#include <format>
#include <span>
#include <sstream>
#include <string>

namespace util
{
	bool is_printable_ascii(char input);

	template <std::size_t N>
	static std::string format_hex(std::span<const char, N> input)
	{
		std::stringstream stream;
		stream << "0x";
		for (const char this_char : input)
		{
			stream << std::format(" {:02X}", this_char);
		}
		return stream.str();
	}

	template <std::size_t N>
	static std::string format_hex_and_ascii(std::span<const char, N> input)
	{
		bool printable = true;
		for (std::size_t i = 0; i < input.size(); i++)
		{
			printable = printable && is_printable_ascii(input[i]);
		}

		std::string result = format_hex(std::span{ input });
		if (printable)
		{
			result = result + std::format(" ({})", std::string{ input.begin(), input.end() });
		}

		return result;
	}
}
