#include "ColorConverter.h"

#include "math/Matrix.h"
#include "math/SafeFuncs.h"

#include "Eotf.h"
#include "XyChromaticity.h"
#include "XyyFloatColor.h"
#include "XyzFloatColor.h"

RgbColor<float> ColorConverter::to_srgb(const XyzFloatColor& xyz)
{
	static const Matrix<float, 3, 3> xyz_to_srgb{
		 3.2406f, -0.9689f,  0.0557f,
		-1.5372f,  1.8758f, -0.2040f,
		-0.4986f,  0.0415f,  1.0570f
	};
	Vector<float, 3> xyz_vec{ xyz.x, xyz.y, xyz.z };
	Vector<float, 3> result = xyz_to_srgb.mul_col_vector(xyz_vec);
	return RgbColor<float>{
		eotf::srgb_inverse(result.x()),
		eotf::srgb_inverse(result.y()),
		eotf::srgb_inverse(result.z()),
	};
}

XyChromaticity ColorConverter::to_xy(const XyzFloatColor& xyz)
{
	const float x = xyz.x / (xyz.x + xyz.y + xyz.z);
	const float y = xyz.y / (xyz.x + xyz.y + xyz.z);
	return XyChromaticity{ x, y };
}

XyyFloatColor ColorConverter::to_xyy(const XyChromaticity& chroma, const float Y)
{
	return XyyFloatColor{ static_cast<float>(chroma.x), static_cast<float>(chroma.y), Y };
}

XyzFloatColor ColorConverter::to_xyz(const XyyFloatColor& xyy)
{
	const float Y_scale = safemath::sdiv(xyy.Y, xyy.y);
	const float x = xyy.x * Y_scale;
	const float y = xyy.Y;
	const float z = (1 - xyy.x - xyy.y) * Y_scale;
	return XyzFloatColor{ x, y, z };
}
