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

XyzFloatColor::XyzFloatColor(const XyChromaticity& chroma, const float scale) :
	x{ static_cast<float>(chroma.x) * scale },
	y{ static_cast<float>(chroma.y) * scale },
	z{ static_cast<float>(1 - chroma.x - chroma.y) * scale }
{

}

/*
XyzFloatColor::XyzFloatColor(const XyChromaticity& chroma, const float Y) :
	x{ static_cast<float>(chroma.x / chroma.y  * Y) },
	y{ Y },
	z{ static_cast<float>((1 - chroma.x - chroma.y) / chroma.y * Y) }
{

}
*/

XyzFloatColor XyzFloatColor::from_wavelength(const double wavelength)
{
	const float x = static_cast<float>(
		1.056 * gaussian(wavelength, 599.8, 0.0264, 0.0323) +
		0.362 * gaussian(wavelength, 442.0, 0.0624, 0.0374) -
		0.065 * gaussian(wavelength, 501.1, 0.0490, 0.0382)
	);
	const float y = static_cast<float>(
		0.821 * gaussian(wavelength, 568.8, 0.0213, 0.0247) +
		0.286 * gaussian(wavelength, 530.9, 0.0613, 0.0322)
	);
	const float z = static_cast<float>(
		1.217 * gaussian(wavelength, 437.0, 0.0845, 0.0278) +
		0.681 * gaussian(wavelength, 459.0, 0.0385, 0.0725)
	);

	return XyzFloatColor{ x, y, z };
}
