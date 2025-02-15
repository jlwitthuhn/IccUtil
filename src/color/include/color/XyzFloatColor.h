#pragma once

class XyzFloatColor
{
public:
	XyzFloatColor(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

	XyzFloatColor operator*(float other) const;
	XyzFloatColor operator+(const XyzFloatColor& other) const;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};
