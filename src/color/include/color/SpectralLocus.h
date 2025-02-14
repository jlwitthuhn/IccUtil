#pragma once

#include <cstddef>
#include <vector>

#include "math/Vector.h"

#include "XyzFloatColor.h"

class SpectralLocus
{
public:
	SpectralLocus();

	XyzFloatColor color_from_wavelength(float wavelength) const;

	float get_hi_bound() const { return get_lo_bound() + samples.size() - 1; }
	float get_lo_bound() const { return static_cast<float>(samples_offset); }

private:
	XyzFloatColor interp_index(float index) const;

	std::size_t samples_offset = 0;
	float nm_between_samples = 0;
	std::vector<XyzFloatColor> samples;
};
