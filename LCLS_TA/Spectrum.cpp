#include "Spectrum.h"

Spectrum::Spectrum()
{}

Spectrum::Spectrum(int pixels)
{
	intensity.reserve(pixels);
	variance.reserve(pixels);
	number.reserve(pixels);

}
