#include "Spectrum.h"

Spectrum::Spectrum()
{}

Spectrum::Spectrum(arma::Mat<double> data)
{
	//intensities = arma::mean(data, 1);
	//variance = arma::var(data, 0, 1);

}

arma::vec* Spectrum::getIntensities()
{
	return &intensities;
}

Spectrum::~Spectrum()
{

}