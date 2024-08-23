#include "Spectrum.h"

Spectrum::Spectrum()
{}

Spectrum::Spectrum(arma::Mat<double> data)
{
	intensities = arma::mean(data, 1);

	intensities.transform([](double val) { return (std::isfinite(val) ? val : double(0)); }); // Dealing with Nans and infs but probably gets the mean val wrong!
	//intensities.transform([](double val) { return (arma::is(val) ? double(0) : val); });
	variance = arma::var(data, 0, 1);

}

arma::vec* Spectrum::getIntensities()
{
	return &intensities;
}

Spectrum::~Spectrum()
{

}