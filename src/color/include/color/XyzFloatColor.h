#pragma once

class XyChromaticity;

class XyzFloatColor
{
public:
	static XyzFloatColor from_wavelength(double wavelength);

	XyzFloatColor(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
	XyzFloatColor(const XyChromaticity& chroma, float scale = 1.0f);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};
