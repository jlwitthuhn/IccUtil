#include "XyChromaticity.h"

#include "XyzFloatColor.h"

XyChromaticity::XyChromaticity(XyzFloatColor color)
{
	x = color.x / (color.x + color.y + color.z);
	y = color.y / (color.x + color.y + color.z);
}
