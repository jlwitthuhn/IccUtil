#pragma once

class RgbFloatColor;
class XyChromaticity;
class XyyFloatColor;
class XyzFloatColor;

// This class does color conversions based on colour-science numbers
class ColorConverter
{
public:
	static RgbFloatColor to_srgb(const XyzFloatColor& xyz);
	static XyChromaticity to_xy(const XyzFloatColor& xyz);
	static XyyFloatColor to_xyy(const XyChromaticity& xy, float Y = 1.0f);
	static XyzFloatColor to_xyz(const XyyFloatColor& xy);
};
