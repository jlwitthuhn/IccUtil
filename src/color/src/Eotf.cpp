#include "Eotf.h"

#include "math/SafeFuncs.h"

float eotf::srgb_inverse(const float srgb_linear)
{
	if (srgb_linear <= 0.0031308f)
	{
		return 12.92f * srgb_linear;
	}
	else
	{
		return 1.055f * safemath::spow(srgb_linear, 1.0f / 2.4f) - 0.055f;
	}
}
