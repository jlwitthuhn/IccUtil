#include "XyzFloatColor.h"

XyzFloatColor XyzFloatColor::operator*(const float other) const
{
	return XyzFloatColor{ x * other, y * other, z * other };
}

XyzFloatColor XyzFloatColor::operator+(const XyzFloatColor& other) const
{
	return XyzFloatColor{ x + other.x, y + other.y, z + other.z };
}
