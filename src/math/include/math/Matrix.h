#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

#include "Vector.h"

template <typename T>
concept MatrixCompatible = std::is_arithmetic<T>::value;

template <MatrixCompatible T, std::size_t R, std::size_t C>
class Matrix
{
public:
	template <typename ... Args>
	Matrix(Args ... args) : val{ args... } {}

	std::size_t get_offset(std::size_t row, std::size_t col) const
	{
		return row + col * R;
	}

	std::size_t count_col() const
	{
		return C;
	}

	std::size_t count_row() const
	{
		return R;
	}

	T get(std::size_t row, std::size_t col) const
	{
		return val[get_offset(row, col)];
	}

	Vector<T, R> get_col(std::size_t col) const
	{
		Vector<T, R> result(static_cast<T>(0));
		for (std::size_t i = 0; i < R; i++)
		{
			result.val[i] = get(i, col);
		}
		return result;
	}

	Vector<T, C> get_row(std::size_t row) const
	{
		Vector<T, C> result(static_cast<T>(0));
		for (std::size_t i = 0; i < C; i++)
		{
			result.val[i] = get(row, i);
		}
		return result;
	}

	Vector<T, R> mul_col_vector(const Vector<T, R>& other) const
	{
		Vector<T, R> result(static_cast<T>(0));
		for (std::size_t i = 0; i < R; i++)
		{
			const Vector<T, C> row = get_row(i);
			result[i] = row.dot(other);
		}
		return result;
	}

private:
	std::array<T, R * C> val;
};
