#include "SimpleColorConverter.h"

#include "math/Matrix.h"

#include "XyzFloatColor.h"

RgbColor<float> SimpleColorConverter::to_srgb(const XyzFloatColor& xyz)
{
	static const Matrix<float, 3, 3> xyz_to_srgb{
		 3.2406f, -0.9689f,  0.0557f,
		-1.5372f,  1.8758f, -0.2040f,
		-0.4986f,  0.0415f,  1.0570f
	};
	Vector<float, 3> xyz_vec{ xyz.x, xyz.y, xyz.z };
	Vector<float, 3> result = xyz_to_srgb.mul_col_vector(xyz_vec);
	return RgbColor<float>{ result.x(), result.y(), result.z() };
}
