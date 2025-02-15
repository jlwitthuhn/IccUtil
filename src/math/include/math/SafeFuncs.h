#pragma once

#include <cmath>
#include <type_traits>

namespace safemath
{
	template <typename T>
	concept SafeMathCompatible = std::is_floating_point<T>::value;

	template <SafeMathCompatible T>
	T sdiv(const T numerator, const T denominator)
	{
		return (denominator == 0) ? static_cast<T>(0) : numerator / denominator;
	}

	template <SafeMathCompatible T>
	T spow(const T base, const T power)
	{
		const T almost = std::pow(std::abs(base), power);
		return std::copysign(almost, base);
	}
}
