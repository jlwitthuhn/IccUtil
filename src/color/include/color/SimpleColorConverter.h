#pragma once

#include "RgbColor.h"

class XyzFloatColor;

// This class does color conversions based on colour-science numbers
class SimpleColorConverter
{
public:
	static RgbColor<float> to_srgb(const XyzFloatColor& xyz);
};
