#include "XyzFloatColor.h"

#include <cmath>

#include "XyChromaticity.h"

namespace
{
	double gaussian(const double x, const double mu, const double t1, const double t2)
	{
		const double t = x < mu ? t1 : t2;
		const double x_mu = x - mu;
		return exp(-1.0 * (t * t) * (x_mu * x_mu) / 2.0);
	}
}

XyzFloatColor::XyzFloatColor(const XyChromaticity& chroma) :
	x{ static_cast<float>(chroma.x) },
	y{ static_cast<float>(chroma.y) },
	z{ static_cast<float>(1 - chroma.x - chroma.y) }
{

}

XyzFloatColor XyzFloatColor::operator*(const float other) const
{
	return XyzFloatColor{ x * other, y * other, z * other };
}

XyzFloatColor XyzFloatColor::operator+(const XyzFloatColor& other) const
{
	return XyzFloatColor{ x + other.x, y + other.y, z + other.z };
}
