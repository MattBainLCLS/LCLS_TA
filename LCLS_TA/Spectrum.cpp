#include "Spectrum.h"

Spectrum::Spectrum()
{}

Spectrum::Spectrum(arma::Mat<double> data)
{
	intensities = arma::vec(data.n_rows, arma::fill::zeros);
	variance = intensities;

	arma::rowvec finiterow;

	for (int i = 0; i < data.n_rows; i++)
	{
		arma::rowvec myrow = data.row(i);
		arma::uvec indices = arma::find_finite(myrow);
		
		if (!indices.is_empty())
		{
			finiterow = myrow.cols(indices);
			intensities(i) = arma::mean(finiterow);
			variance(i) = arma::var(finiterow);
		}

	}

}

arma::vec* Spectrum::getIntensities()
{
	return &intensities;
}

Spectrum::~Spectrum()
{

}