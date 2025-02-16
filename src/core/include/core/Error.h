#pragma once

#include <string>

class Error
{
public:
	Error(int code, const std::string& message) : code{ code }, message{ message } {}

	int code = 0;
	std::string message;
};
