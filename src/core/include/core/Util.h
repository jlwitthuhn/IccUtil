#pragma once

#include <cstddef>
#include <type_traits>

namespace util
{
	template <typename T>
	concept SwapEndiannessCompatible = std::is_trivially_copyable<T>::value;

	template <SwapEndiannessCompatible T>
	T swapEndianness(T input)
	{
		char* const in_ch = reinterpret_cast<char*>(&input);
		T output;
		char* const out_ch = reinterpret_cast<char*>(&output);

		const std::size_t t_size = sizeof(T);
		for (std::size_t i = 0; i < t_size; i++)
		{
			const std::size_t src = i;
			const std::size_t dst = t_size - 1 - i;
			out_ch[dst] = in_ch[src];
		}
		return output;
	}
}
