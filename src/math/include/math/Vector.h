#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

template <typename T>
concept VectorCompatible = std::is_arithmetic<T>::value;

template <VectorCompatible T, std::size_t N>
class Vector
{
public:
	template <typename ... Args>
	Vector(Args... args) : val{ args... } {}

	T& operator [](std::size_t index)
	{
		return val[index];
	}

	const T& operator [](std::size_t index) const
	{
		return val[index];
	}

	Vector<T, N> operator*(const float other) const
	{
		Vector<T, N> result{ *this };
		for (std::size_t i = 0; i < N; i++)
		{
			result[i] = static_cast<T>(result[i] * other);
		}
		return result;
	}

	T x() const requires (N >= 1)
	{
		return val[0];
	}
	T y() const requires (N >= 2)
	{
		return val[1];
	}
	T z() const requires (N >= 3)
	{
		return val[2];
	}

	T dot(const Vector<T, N>& other) const
	{
		T result = static_cast<T>(0);
		for (std::size_t i = 0; i < N; i++)
		{
			result += val[i] * other.val[i];
		}
		return result;
	}

	std::array<T, N> val;
};
