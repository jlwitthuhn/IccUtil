#pragma once

#include <utility>
#include <variant>

#include "Error.h"

template <typename T>
class Result
{
public:
	Result(T&& success) : data{ std::forward<T>(success) } {}
	Result(const T& success) : data{ success } {}
	Result(const Error& err) : data{ err } {}

	operator bool() const
	{
		return std::holds_alternative<T>(data);
	}

	T&& get()
	{
		return std::get<T>(data);
	}

	const T& get() const
	{
		return std::get<T>(data);
	}

	const Error& error() const
	{
		return std::get<Error>(data);
	}

private:
	std::variant<T, Error> data;
};
