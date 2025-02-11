#pragma once

class XyzFloatColor;

class XyChromaticity
{
public:
	XyChromaticity() = default;
	XyChromaticity(XyzFloatColor color);
	XyChromaticity(double x, double y) : x{ x }, y{ y } {}

	double x = 0.0;
	double y = 0.0;
};
